/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:51:16 by tbae              #+#    #+#             */
/*   Updated: 2023/11/10 11:11:24 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset_tab(t_data *data, t_env *tmp_env)
{
	char	*key;

	while (data->head && data->head->type != 5)
	{
		if (data->head->type != 0)
			data->head = data->head->next->next;
		else
		{
			key = ft_strdup(data->head->content);
			while (data->head_env
				&& ft_strcmp(key, data->head_env->key) != 0)
				data->head_env = data->head_env->next;
			if (data->head_env == NULL)
				return (free(key), data->head_env = tmp_env, 0);
			else
				remove_list_env(&tmp_env, data->head_env);
			free(key);
			data->head_env = tmp_env;
			data->head = data->head->next;
		}
	}
	return (1);
}

int	ft_unset(t_data *data)
{
	t_env	*tmp_env;

	tmp_env = data->head_env;
	if (data->head->next == NULL)
		return (0);
	data->head = data->head->next;
	ft_unset_tab(data, tmp_env);
	list_to_tab(data);
	return (0);
}
