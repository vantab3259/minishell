/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:57:31 by tbae              #+#    #+#             */
/*   Updated: 2023/11/10 11:51:45 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_line_here_doc(t_data *data)
{
	char	*line;
	char	*str_begin;
	char	*str_error;
	int		fd;

	str_begin = "minishell : avertissement :";
	str_error = "« here-doc » délimité par la fin du fichier";
	fd = open("here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_printf(" %s\n", strerror(errno)),
			close(fd), free_here_doc(data), exit (errno), 0);
	while (1)
	{
		line = readline("> ");
		if (g_bal == 257)
			return (g_bal = 130,
				free (line), free_here_doc(data), close(fd), 0);
		if (line == NULL)
			return (close(fd), ft_printf(" %s %s (au lieu de « %s »)\n",
					str_begin, str_error, data->head->content), free (line), 0);
		if (!ft_strcmp (line, data->head->content))
			return (free (line), free_here_doc(data), close(fd));
		ft_print_error(fd, "%s\n", line);
		free (line);
	}
}

void	here_doc_wait(t_data *data, pid_t pid)
{
	int		wstatus;
	int		wpid;

	while (true)
	{
		wpid = wait(&wstatus);
		if (wpid == -1)
			break ;
		if (wpid == pid)
		{
			if (WIFEXITED(wstatus))
				g_bal = WEXITSTATUS(wstatus);
			else
				g_bal = 128 + WTERMSIG(wstatus);
		}
	}
}

int	here_or_no(t_data *data, t_main *main)
{
	t_node	*tmp;

	tmp = data->head;
	while (data->head)
	{
		if (data->head->type == 1)
		{
			data->head = tmp;
			return (1);
		}
		data->head = data->head->next;
	}
	data->head = tmp;
	return (0);
}

void	heredoc_fork(t_data *data, t_main *main, int fd)
{
	signal(SIGINT, &handle_sig_heredocs);
	fd = get_line_here_doc(data);
	free_here_doc(data);
	if (g_bal == 130)
		exit(130);
	exit(0);
}

int	here_doc_init(t_data *data, t_main *main)
{
	pid_t	pid;
	int		tmp;
	int		fd;
	char	*line;
	int		retour;

	if (!here_or_no(data, main))
		return (0);
	free(main->prompt);
	while (data->head && data->head->content)
	{
		if (data->head->type == 1)
		{
			g_bal = 0;
			data->head = data->head->next;
			pid = fork();
			if (pid == 0)
				heredoc_fork(data, main, fd);
		}
		here_doc_wait(data, pid);
		data->head = data->head->next;
	}
	return (g_bal);
}
