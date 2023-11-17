/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:50:23 by tbae              #+#    #+#             */
/*   Updated: 2023/11/10 12:15:05 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_in(t_data *data, t_env *tmp_env, char *key, char *content)
{
	int		entry_len;
	char	*entry;
	int		i;

	i = 0;
	while (data->head_env != NULL)
	{
		key = data->head_env->key;
		content = data->head_env->content;
		entry_len = ft_strlen(key) + ft_strlen(content) + 2;
		entry = malloc(entry_len);
		if (!entry)
			return ;
		ft_strlcpy(entry, key, entry_len);
		ft_strlcat(entry, "=", entry_len);
		ft_strlcat(entry, content, entry_len);
		data->mini_env[i] = entry;
		i++;
		data->head_env = data->head_env->next;
	}
	data->head_env = tmp_env;
}

void	list_to_tab(t_data *data)
{
	t_env	*tmp_env;
	int		sizeenv;
	char	*key;
	char	*content;

	sizeenv = 0;
	tmp_env = data->head_env;
	while (data->head_env)
	{
		data->head_env = data->head_env->next;
		sizeenv++;
	}
	data->head_env = tmp_env;
	free_tab(data->mini_env);
	data->mini_env = ft_calloc(sizeenv + 2, sizeof(char **));
	copy_in(data, tmp_env, key, content);
}

int	expi(t_data *data, t_env *tmp_env, char **key, char **content)
{
	int	idx_content;

	idx_content = 0;
	while (data->head->content[idx_content]
		&& data->head->content[idx_content] != '=')
		idx_content++;
	if (!data->head->content[idx_content])
		return (1);
	*key = ft_substr(data->head->content, 0, idx_content);
	*content = ft_strdup(data->head->content + idx_content + 1);
	while (data->head_env && ft_strcmp(*key, data->head_env->key) != 0)
		data->head_env = data->head_env->next;
	if (data->head_env == NULL)
	{
		data->head_env = tmp_env;
		push_back_env(&data->head_env, ft_strdup(*key), *content);
		tmp_env = data->head_env;
	}
	else
	{
		free(data->head_env->content);
		data->head_env->content = *content;
		data->head_env = tmp_env;
	}
	return (free (*key), 0);
}

int	verif_exportable(t_data *data, t_env *tmp_env, char **key, char **content)
{
	int	i;

	i = 0;
	if (data->head->content)
	{
		if (!isalpha(data->head->content[i]) && data->head->content[i] != '_')
			return (ft_printf(" not a valid identifier\n"), 1);
		i++;
		while (data->head->content[i] && data->head->content[i] != '=')
		{
			if (!isalnum(data->head->content[i]))
				return (ft_printf(" not a valid identifier\n"), 1);
			i++;
		}
	}
	expi(data, tmp_env, key, content);
	return (0);
}

int	ft_export(t_data *data)
{
	t_env	*tmp_env;
	char	*key;
	char	*content;
	int		error;

	key = NULL;
	error = 0;
	tmp_env = data->head_env;
	if (data->head->next == NULL)
		return (0);
	data->head = data->head->next;
	while (data->head && data->head->type != 5 && error != 1)
	{
		if (data->head->type != 0)
			data->head = data->head->next;
		else
			error = verif_exportable(data, tmp_env, &key, &content);
		data->head = data->head->next;
	}
	data->head_env = tmp_env;
	list_to_tab(data);
	return (error);
}
