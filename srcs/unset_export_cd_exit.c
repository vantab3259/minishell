/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_export_cd_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:45:34 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/10 12:19:17 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	openfiles_builting(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		openfiles(data);
		if (data->origin)
			free_list(data->origin);
		if (data->head_env)
			free_list_env(data->head_env);
		if (data->mini_env)
			free_tab(data->mini_env);
		exit (EXIT_SUCCESS);
	}
	wait (NULL);
	return (0);
}

int	unset_export_cd_exit(t_data *data)
{
	t_node	*tmp;

	tmp = data->head;
	while (data->head)
	{
		if (data->head->type == 5)
			return (data->head = tmp, -1);
		data->head = data->head->next;
	}
	data->head = tmp;
	if (ft_strcmp(data->head->content, "exit") == 0)
		g_bal = ft_exit(data, 0);
	if (ft_strcmp(data->head->content, "cd") == 0)
		g_bal = ft_cd(data);
	else if (ft_strcmp(data->head->content, "unset") == 0)
		g_bal = ft_unset(data);
	else if (ft_strcmp(data->head->content, "export") == 0)
		g_bal = ft_export (data);
	else
		return (data->head = tmp, -1);
	openfiles_builting(data);
	data->head = tmp;
	return (0);
}
