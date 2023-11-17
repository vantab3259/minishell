/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:45:33 by tbae              #+#    #+#             */
/*   Updated: 2023/11/08 10:36:44 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_pipe(t_data *data)
{
	long long	i;

	if ((data->head->next == NULL || data->head->next->type != 0))
	{
		printf("exit\n");
		return (0);
	}
	else if (data->head->next->next == NULL)
	{
		if (ft_atoll_verif(data->head->next->content))
		{
			write(STDERR_FILENO, "bash: exit: numeric argument required\n", 38);
			return (2);
		}
		i = ft_atoll(data->head->next->content);
		printf ("exit\n");
		return ((int)(i % 256));
	}
	else
	{
		write(STDERR_FILENO, "bash: exit: too many argumentss\n", 32);
		return (2);
	}
}

int	ft_exit(t_data *data, int t)
{
	long long	i;

	if (t == 1)
		return (ft_exit_pipe(data));
	free_list_env(data->head_env);
	free_tab(data->mini_env);
	if (data->head->next == NULL)
		return (printf("exit\n"), free_list(data->origin), exit(g_bal), 0);
	else if (data->head->next->next == NULL)
	{
		if (ft_atoll_verif(data->head->next->content))
		{
			free_list(data->origin);
			printf("exit\n");
			write(STDERR_FILENO, "bash: exit: numeric argument required\n", 38);
			exit(2);
		}
		i = ft_atoll(data->head->next->content);
		free_list(data->origin);
		printf("exit\n");
		exit((int)(i % 256));
	}
	printf ("exit\n");
	write (STDERR_FILENO, "bash: exit: too many arguments\n", 31);
	return (free_list(data->origin), exit(1), 1);
}
