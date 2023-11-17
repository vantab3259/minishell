/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:41:03 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/06 19:18:52 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_word_expand(t_node **head)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	if ((*head)->content[0] != '$')
		word = 1;
	while ((*head)->content[i])
	{
		if (i > 0 && (*head)->content[i - 1] == '$' && ((*head)->content[i] < 0
				|| (*head)->content[i] > 9))
		{
			word++;
		}
		i++;
	}
	return (word);
}

t_env	*search_content(t_env *env, char *key)
{
	if (key == NULL)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}

char	*strdup_like(char *s, int start, int end)
{
	char	*copy;
	int		i;

	i = 0;
	if (end <= start)
		return (NULL);
	copy = malloc(sizeof(char) * (end - start + 1));
	if (!copy)
		return (NULL);
	while (s && s[start] && start < end)
	{
		copy[i] = s[start];
		i++;
		start++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*get_name_var(char *s, int start)
{
	int	end;

	end = start;
	while (s && s[end] != '\0' && s[end] != ' ' && s[end] != '\t'
		&& s[end] != '$')
	{
		end++;
	}
	return (strdup_like(s, start, end));
}

int	ft_isvalidforvariablename(char c, bool is_first)
{
	return (ft_isalpha(c) || c == '_' || (!is_first && ft_isdigit(c)));
}
