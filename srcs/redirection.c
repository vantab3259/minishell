/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:31:10 by tbae              #+#    #+#             */
/*   Updated: 2023/11/09 14:10:28 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	outfile(t_data *data)
{
	int	fd;

	if (!data->head->next)
		return (ft_printf("bash: : No such file or directory\n"), exit (1));
	if (data->head->type == 2)
	{
		data->head = data->head->next;
		fd = open(data->head->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (ft_printf(" %s\n", strerror(errno)),
				free_here_doc(data), exit (1));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (data->head->type == 4)
	{
		data->head = data->head->next;
		fd = open(data->head->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (ft_printf(" %s\n", strerror(errno)),
				free_here_doc(data), exit (1));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	infile(t_data *data)
{
	int	fd;

	if (data->head->type == 1)
	{
		data->head = data->head->next;
		fd = open("here_doc_tmp", O_RDONLY, 0644);
		if (fd < 0)
			return (ft_printf(" %s\n", strerror(errno)),
				free_here_doc(data), exit (1));
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (data->head->type == 3)
	{
		data->head = data->head->next;
		fd = open(data->head->content, O_RDONLY, 0644);
		if (fd < 0)
			return (ft_printf(" %s\n", strerror(errno)),
				free_here_doc(data), exit (1));
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return ;
}

int	openfiles(t_data *data)
{
	int		i;
	int		fd;
	pid_t	pid;

	data->pipe.nbarg = 0;
	while (data->head && data->head->content && data->head->type != 5)
	{
		if (data->head->type == 3 || data->head->type == 1)
			infile(data);
		else if (data->head->type == 4 || data->head->type == 2)
			outfile(data);
		else
			data->pipe.nbarg++;
		data->head = data->head->next;
	}
	return (0);
}

void	redirection(t_data *data, int i, int *fd)
{
	if (i != data->pipe.nbcmd - 1)
		dup2(fd[1], STDOUT_FILENO);
	if (i != 0)
	{
		dup2(data->pipe.prev, STDIN_FILENO);
		close(data->pipe.prev);
	}
	close(fd[1]);
	close(fd[0]);
}
