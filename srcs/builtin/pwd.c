/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:54:46 by tbae              #+#    #+#             */
/*   Updated: 2023/11/08 10:15:41 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		printf("minishell: %s: %s\n",
			data->head->content,
			strerror(errno));
		return (1);
	}
	if (printf("%s\n", cwd) < 0)
	{
		printf("minishell: %s: write error: %s\n",
			data->head->content,
			strerror(errno));
		free(cwd);
		return (1);
	}
	free(cwd);
	return (0);
}
/*
char	*get_pwd(char **mini_env)
{
	int		idx = 0;
	char	*pwd;

	while (mini_env[idx] && ft_strncmp(mini_env[idx], "PWD", 3) != 0)
		idx++;
	if (mini_env[idx] == NULL)
		return (NULL);
	pwd = ft_strdup (mini_env[idx] + 4);
	return (pwd);
}
*/
