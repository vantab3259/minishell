/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:31:10 by tbae              #+#    #+#             */
/*   Updated: 2023/11/09 11:56:51 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(char **env, char *str)
{
	const size_t	len = ft_strlen(str);
	int				i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*joinslash(char *tab, char *path)
{
	char	*tmp;
	int		i;
	int		n;
	int		m;

	i = ft_strlen(path);
	n = 0;
	m = 0;
	tmp = malloc(sizeof(char) * (i + ft_strlen(tab) + 2));
	if (!tmp)
		return (NULL);
	while (path[n])
	{
		tmp[n] = path[n];
		n++;
	}
	tmp[n] = '/';
	n++;
	while (tab[m])
	{
		tmp[n] = tab[m];
		n++;
		m++;
	}
	return (tmp[n] = '\0', tmp);
}

char	*get_good_path(char *cmd, char **paths)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!cmd || !cmd[0] || !paths)
		return (NULL);
	while (paths[i])
	{
		tmp = joinslash(cmd, paths[i]);
		if (!access(tmp, F_OK | X_OK))
		{
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

void	build_command(t_data *data)
{
	int	idx;

	idx = 0;
	data->pipe.cmd = malloc (sizeof(char *) * (data->pipe.nbarg + 1));
	while (data->head && data->head->content && data->head->type != 5)
	{
		if (data->head->type > 0 && data->head->type < 5)
			data->head = data->head->next;
		else
		{
			data->pipe.cmd[idx] = data->head->content;
			idx++;
		}
		if (data->head)
			data->head = data->head->next;
	}
	data->pipe.cmd[idx] = NULL;
	return ;
}

void	check_file(t_data *data)
{
	struct stat	*buf;

	if (access(data->pipe.cmd[0], F_OK) == -1)
		return (free_pipe(data),
			ft_printf(" %s\n", strerror(2)), exit(127));
	if (access(data->pipe.cmd[0], X_OK) == -1)
		return (free_pipe(data),
			ft_printf(" %s\n", strerror(13)), exit(126));
}
