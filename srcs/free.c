/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:02:52 by tbae              #+#    #+#             */
/*   Updated: 2023/11/07 15:55:54 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipe(t_data *data)
{
	if (data->origin)
		free_list(data->origin);
	if (data->pipe.cmd)
		free(data->pipe.cmd);
	if (data->pipe.path)
		free_tab(data->pipe.path);
	if (data->head_env)
		free_list_env(data->head_env);
	if (data->mini_env)
		free_tab(data->mini_env);
	data->origin = NULL;
	data->pipe.cmd = NULL;
	data->pipe.path = NULL;
	data->head_env = NULL;
	data->mini_env = NULL;
}

void	free_here_doc(t_data *data)
{
	if (data->origin)
		free_list(data->origin);
	if (data->head_env)
		free_list_env(data->head_env);
	if (data->mini_env)
		free_tab(data->mini_env);
	data->origin = NULL;
	data->head_env = NULL;
	data->mini_env = NULL;
}
