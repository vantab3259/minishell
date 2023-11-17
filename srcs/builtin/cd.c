/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:49:04 by tbae              #+#    #+#             */
/*   Updated: 2023/11/10 12:17:05 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_home(t_data *data)
{
	t_env	*tmp_env;

	tmp_env = data->head_env;
	while (data->head_env && ft_strcmp(data->head_env->key, "HOME"))
		data->head_env = data->head_env->next;
	if (!data->head_env)
		return (data->head_env = tmp_env,
			ft_printf("minishelll: cd: HOME not set\n"), 1);
	if (chdir(data->head_env->content) == -1)
		return (data->head_env = tmp_env,
			ft_printf("minishelll: cd: %s: %s\n",
				data->head_env->content, strerror(errno), 2));
	data->head_env = tmp_env;
	return (0);
}

int	cd_else(t_data *data)
{
	struct stat	buf;

	data->head = data->head->next;
	if (data->head->next)
		return (ft_printf("minishell: cd: too many arguments\n"), 1);
	if (access(data->head->content, F_OK) == -1)
		return (ft_printf(" %s\n", strerror(2)), 1);
	stat(data->head->content, &buf);
	if (!S_ISDIR(buf.st_mode))
		return (ft_printf(" Not a directory\n"), 1);
	if (chdir(data->head->content) == -1)
		return (ft_printf("minishelll: cd: %s: %s\n",
				data->head->content, strerror(errno), 2));
	return (0);
}

void	cd_tab(t_data *data, char *path)
{
	int		idx;
	t_env	*tmp;

	idx = 0;
	tmp = data->head_env;
	while (data->mini_env[idx]
		&& ft_strncmp(data->mini_env[idx], "PWD=", 4) != 0)
		idx++;
	free (data->mini_env[idx]);
	data->mini_env[idx] = ft_strjoin("PWD=", path);
	idx = 0;
	while (data->head_env
		&& ft_strncmp(data->head_env->key, "PWD", 4) != 0)
		data->head_env = data->head_env->next;
	while (data->mini_env[idx]
		&& ft_strncmp(data->mini_env[idx], "OLDPWD=", 7) != 0)
		idx++;
	if (data->mini_env[idx])
		free (data->mini_env[idx]);
	if (data->head_env)
		data->mini_env[idx] = ft_strjoin("OLDPWD=", data->head_env->content);
	data->head_env = tmp;
	return ;
}

int	ft_cd(t_data *data)
{
	char		*path;
	int			error;
	t_node		*tmp;

	tmp = data->head;
	if (!data->head->next)
	{
		error = cd_home(data);
		if (error != 0)
			return (error);
	}
	else
	{
		error = cd_else(data);
		if (error != 0)
			return (error);
	}
	path = getcwd(NULL, 0);
	if (path == NULL)
		return (printf("minishell: %s: %s\n", data->head->content,
				strerror(errno)), 1);
	cd_tab(data, path);
	cd_list(data, path);
	free (path);
	return (data->head = tmp, 0);
}
