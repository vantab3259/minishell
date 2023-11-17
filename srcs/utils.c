/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:45:34 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/07 13:52:37 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int		idx;

	idx = 0;
	if (!tab)
		return ;
	while (tab[idx] != NULL)
	{
		free(tab[idx]);
		idx++;
	}
	free (tab);
}

void	ctrlc(int sig)
{
	(void)sig;
	g_bal = 130;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sig_heredocs(int sig)
{
	int	fd;

	if (sig == SIGINT)
	{
		fd = open("/dev/null", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		ft_putstr_fd("\n", 1);
		g_bal = 257;
	}
}

void	check_builtin(t_data *data, char **arg, char **mini_env)
{
	int		error_value;
	t_node	*tmp;

	tmp = data->head;
	if (ft_strcmp(arg[0], "cd") == 0)
		error_value = ft_cd(data);
	else if (ft_strcmp(arg[0], "pwd") == 0)
		error_value = ft_pwd(data);
	else if (ft_strcmp(arg[0], "env") == 0)
		error_value = print_env(data, data->mini_env);
	else if (ft_strcmp(arg[0], "echo") == 0)
		error_value = ft_echo(data);
	else if (ft_strcmp(arg[0], "unset") == 0)
		error_value = ft_unset(data);
	else if (ft_strcmp(arg[0], "export") == 0)
		error_value = ft_export(data);
	else if (ft_strcmp(arg[0], "exit") == 0)
		error_value = ft_exit(data, 1);
	else
		return ;
	data->head = tmp;
	free_pipe(data);
	exit (error_value);
}
