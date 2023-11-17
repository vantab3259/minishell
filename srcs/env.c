/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:34:02 by tbae              #+#    #+#             */
/*   Updated: 2023/11/10 12:14:46 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fullfill_empty_env(char **mini_env, char *buffer, int idx)
{
	if (ft_strlcpy(mini_env[0], "PWD=", 5) == 0)
		return ;
	if (ft_strlcpy(mini_env[0] + 4, buffer, idx + 1) == 0)
		return ;
	mini_env[1] = malloc (8 * sizeof(char *));
	if (!mini_env[1])
		return ;
	if (ft_strlcpy(mini_env[1], "SHLVL=1", 8) == 0)
		return ;
	mini_env[2] = malloc (15 * sizeof(char *));
	if (!mini_env[2])
		return ;
	if (ft_strlcpy(mini_env[2], "_=/usr/bin/env", 15) == 0)
		return ;
}

char	**build_empty_env(t_env **head_env)
{
	char	**mini_env;
	char	*buffer;
	int		idx;

	mini_env = malloc (200 * sizeof(char **));
	if (mini_env == NULL)
		return (NULL);
	buffer = malloc (4096 * sizeof(char *));
	if (getcwd(buffer, 4096) == NULL)
		return (printf("Cannot get current working directory path\n"), NULL);
	while (buffer[idx])
		idx++;
	mini_env[0] = malloc ((idx + 5) * sizeof(char *));
	if (!mini_env[0])
		return (NULL);
	fullfill_empty_env(mini_env, buffer, idx);
	free (buffer);
	builtin_env(head_env, mini_env);
	return (mini_env);
}

int	builtin_env(t_env **head_env, char **env)
{
	char	*key;
	char	*content;
	int		i;
	int		j;

	if (!env)
		return (false);
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				key = ft_substr(env[i], 0, j);
				content = ft_strdup(env[i] + j + 1);
				push_back_env(head_env, key, content);
				break ;
			}
			j++;
		}
		i++;
	}
	return (1);
}

char	**get_env(char **env, t_env **head_env)
{
	int		nb_str;
	int		idx_str;
	char	**mini_env;

	nb_str = 0;
	idx_str = 0;
	mini_env = NULL;
	if (env[0] == NULL)
		return (build_empty_env(head_env));
	while (env[nb_str])
		nb_str ++;
	mini_env = ft_calloc(sizeof(char *), nb_str + 2);
	while (idx_str < nb_str)
	{
		mini_env[idx_str] = ft_strdup(env[idx_str]);
		if (mini_env[idx_str] == NULL)
			return (free_tab(mini_env), NULL);
		idx_str++;
	}
	if (!builtin_env(head_env, mini_env))
		return (NULL);
	return (mini_env);
}
