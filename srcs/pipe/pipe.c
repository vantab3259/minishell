/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:31:10 by tbae              #+#    #+#             */
/*   Updated: 2023/11/09 14:01:37 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_bal;

void	pipe_setup(t_data *data, int *fd, int idx)
{
	t_node	*tmp;
	char	*path;

	tmp = data->head;
	redirection(data, idx, fd);
	openfiles(data);
	if (data->pipe.nbarg == 0)
		return (free_pipe(data), exit (g_bal));
	data->head = tmp;
	build_command(data);
	if (!data->pipe.cmd[0])
		exit (0);
	data->head = tmp;
	path = get_line(data->mini_env, "PATH");
	if (path)
	{
		data->pipe.path = ft_split(path, ':');
		if (data->pipe.path == NULL)
			exit(EXIT_FAILURE);
	}
	else
		data->pipe.path = NULL;
	data->head = tmp;
}

void	pipe_exec(t_data *data)
{
	char		*good_path;
	struct stat	buf;

	check_builtin(data, data->pipe.cmd, data->mini_env);
	if (g_bal >= 256)
		return (free_pipe(data), exit (g_bal - 256));
	if (ft_strchr(data->pipe.cmd[0], '/'))
	{
		check_file(data);
		stat(data->head->content, &buf);
		if (S_ISDIR(buf.st_mode))
			return (free_pipe(data),
				ft_printf(" %s\n", strerror(21)), exit(126));
		execve(data->pipe.cmd[0], data->pipe.cmd, data->mini_env);
	}
	else
	{
		good_path = get_good_path(data->pipe.cmd[0], data->pipe.path);
		if (!good_path)
			return (ft_printf("bash: %s: command not found\n",
					data->pipe.cmd[0]), free_pipe(data), exit(127));
		else
			execve(good_path, data->pipe.cmd, data->mini_env);
	}
	return (ft_printf("%s\n", strerror(errno)), free_pipe(data), exit(errno));
}

void	pipe_prep(t_data *data, int *idx, int *fd)
{
	*idx = *idx + 1;
	if (*idx < data->pipe.nbcmd)
	{
		while (data->head->type != 5)
			data->head = data->head->next;
		data->head = data->head->next;
	}
	close(fd[1]);
	if (data->pipe.prev != -1)
		close(data->pipe.prev);
	data->pipe.prev = fd[0];
}

void	pipe_fork(t_data *data, pid_t *pid, t_node *tmp)
{
	int		fd[2];
	int		idx;

	idx = 0;
	while (data->head)
	{
		if (data->head->type == 5)
			data->pipe.nbcmd++;
		data->head = data->head->next;
	}
	data->pipe.nbcmd++;
	data->head = tmp;
	while (idx < data->pipe.nbcmd)
	{
		pipe(fd);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		*pid = fork();
		if (*pid == 0)
			return (pipe_setup(data, fd, idx), pipe_exec(data));
		else
			pipe_prep(data, &idx, fd);
	}
	close(fd[0]);
}

int	ft_pipe(t_data *data)
{
	int		wstatus;
	int		wpid;
	pid_t	pid;
	t_node	*tmp;

	tmp = data->head;
	data->pipe.nbcmd = 0;
	data->pipe.prev = -1;
	pipe_fork(data, &pid, tmp);
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
	return (g_bal);
}
