/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:57:46 by mudoh             #+#    #+#             */
/*   Updated: 2023/07/17 23:13:58 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**getpath(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			return (ft_split(env[i] + 5, ':'));
		}
		i++;
	}
	return (NULL);
}

void	initstruct(t_data *data, char *str, char **env)
{
	data->nbcmd = ft_countword(str, '|');
	data->env = env;
	data->prev = -1;
	data->pid = malloc(sizeof(int) * data->nbcmd);
	data->input_f = -1;
	data->output_f = -1;
	if (!data->pid)
		exit(1);
}


void	redirection(t_data *data, int i)
{
	if (i != data->nbcmd - 1)
	{
		dup2(data->fd[1], STDOUT_FILENO);
	}
	if (i != 0)
	{
		dup2(data->prev, STDIN_FILENO);
		close(data->prev);
	}
	close(data->fd[1]);
	close(data->fd[0]);
	// openfiles()
}

void	freetab(char **tab)
{
	for (int i = 0; tab[i]; i++)
		free(tab[i]);
	free(tab);
}

char	*joinslash(char *tab, char *path)
{
	char	*tmp;
	int		i;
	int		j;
	int		n;
	int		m;

	i = ft_strlen(path);
	j = ft_strlen(tab);
	n = 0;
	m = 0;
	tmp = malloc(sizeof(char) * (i + j + 2));
	while (path[n])
	{
		tmp[n] = path[n];
		n++;
	}
	tmp[n] = '/';
	n++;
	while (tab[m])
	{
		tmp[n] = tab[m];
		n++;
		m++;
	}
	tmp[n] = '\0';
	return (tmp);
}

char	*get_good_path(char *cmd, char **paths)
{
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = joinslash(cmd, paths[i]);
		if (!access(tmp, F_OK | X_OK))
		{
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

int	openfiles(t_info *info, t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (info->files[i])
	{
		if (info->tp_f[i] == 1)
			fd = open(info->files[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (info->tp_f[i] == 2)
			fd = open(info->files[i], O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (info->tp_f[i] == 3)
			fd = open(info->files[i], O_RDONLY, 0666);
		if (fd == -1)
		{
			// free, message, exit(1);
		}
		if (info->tp_f[i] == 1 || info->tp_f[i] == 2)
			dup2(fd, STDOUT_FILENO);
		if (info->tp_f[i] == 3)
			dup2(fd, STDIN_FILENO);
		close(fd);
		i++;
	}
	return (0);
}

void	ft_pipex(t_data *data, char **first_tab)
{
	int		i;
	t_info	info;

	
	i = 0;
	/* if (data->nbcmd == 1 && commandisbuiltin(first_tab[i]))
	{
		// openfiles
		exec_builtin(info.arg, data->env);
	} */
	while (i < data->nbcmd)
	{
		pipe(data->fd);
		data->pid[i] = fork();
		if (data->pid[i] == 0)
		{
			free(data->pid);
			info = parse(first_tab[i]);
			freetab(first_tab);
			redirection(data, i);
			openfiles(&info, data);
			if (!ft_strchr(info.command, '/'))
			{
				data->path = getpath(data->env);
				info.command = get_good_path(info.command, data->path);
			}
			
			execve(info.command, info.arg, data->env);
			fprintf(stderr, "COMMAND NOT FOUND\n");
			exit(127);
		}
		else if (data->pid > 0)
		{
			//printf("%i | %i | %i\n", data->prev, data->fd[0], data->fd[1]);
			close(data->fd[1]);
			if (data->prev != -1)
				close(data->prev);
			data->prev = data->fd[0];
		}
		i++;
	}
	i = 0;
	while (i < data->nbcmd)
		waitpid(data->pid[i++], 0, 0);
	close(data->fd[0]);
	if (data->input_f != -1)
	{
		close(data->input_f);
	}
	if (data->output_f != -1)
	{
		close(data->output_f);
	}
}
static void ctrlc(int sig){
	if(sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	static t_data data = {0};
	if (ac != 2)
		av[1] = "$>";
	char *str;
	char **first_tab;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc);
	while (1)
	{
		str = readline(av[1]);
		if (!str)
			exit(1);
		if (!*str)
		{
			free(str);
			continue ;
		}
		add_history(str);
		first_tab = ft_split(str, '|'); // {ls -R > out}{cat}
		initstruct(&data, str, env);
		free(str);
		ft_pipex(&data, first_tab);
		freetab(first_tab);
		free(data.pid);
	}
}
