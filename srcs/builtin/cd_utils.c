/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:02:17 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/10 12:06:24 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_list_two(t_data *data, char *path, t_env	*tmp)
{
	while (data->head_env
		&& ft_strncmp(data->head_env->key, "PWD", 4) != 0)
		data->head_env = data->head_env->next;
	if (!data->head_env)
	{
		data->head_env = tmp;
		push_back_env(&data->head_env, ft_strdup("PWD"), ft_strdup(path));
	}
	else
	{
		free (data->head_env->content);
		data->head_env->content = ft_strdup(path);
		data->head_env = tmp;
	}
}

void	cd_list(t_data *data, char *path)
{
	int		idx;
	t_env	*tmp;

	idx = 0;
	tmp = data->head_env;
	cd_list_two(data, path, tmp);
	while (data->mini_env[idx]
		&& ft_strncmp(data->mini_env[idx], "OLDPWD=", 7) != 0)
		idx++;
	while (data->head_env
		&& ft_strncmp(data->head_env->key, "OLDPWD", 7) != 0)
		data->head_env = data->head_env->next;
	if (!data->head_env)
	{
		data->head_env = tmp;
		push_back_env(&data->head_env,
			ft_strdup("OLDPWD"), ft_strdup(data->mini_env[idx] + 7));
		return ;
	}
	free (data->head_env->content);
	data->head_env->content = ft_strdup(data->mini_env[idx] + 7);
	data->head_env = tmp;
	return ;
}
