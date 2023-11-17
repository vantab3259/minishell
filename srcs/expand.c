/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 04:25:39 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/10 12:21:29 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_pt1b(t_node *current, t_env *env, t_expand *exp)
{
	exp->j = exp->i + 1;
	if (!current->content[exp->j])
		return (free(exp->g_sr), 0);
	if (current->content[exp->j] == '?')
	{
		exp->len += ft_strlen(exp->g_sr);
		exp->j++;
		exp->i = exp->j;
		return (1);
	}
	exp->is_first = true;
	while (current->content[exp->j]
		&& ft_isvalidforvariablename(current->content[exp->j], exp->is_first))
	{
		exp->j++;
		exp->is_first = false;
	}
	exp->key = strdup_like(current->content, exp->i + 1, exp->j);
	exp->cell = search_content(env, exp->key);
	if (exp->key)
		free(exp->key);
	if (exp->cell)
		exp->len += ft_strlen(exp->cell->content);
	exp->i = exp->j;
	return (1);
}

void	expand_pt2b(t_node *current, t_env *env, t_expand *exp)
{
	exp->is_first = true;
	while (current->content[exp->j]
		&& ft_isvalidforvariablename(current->content[exp->j], exp->is_first))
	{
		exp->j++;
		exp->is_first = false;
	}
	exp->key = strdup_like(current->content, exp->i + 1, exp->j);
	exp->cell = search_content(env, exp->key);
	free(exp->key);
	if (exp->cell)
	{
		exp->k = 0;
		while (exp->cell->content[exp->k])
		{
			exp->result[exp->x] = exp->cell->content[exp->k];
			exp->x++;
			exp->k++;
		}
	}
	exp->i = exp->j;
}

int	expand_pt2(t_node *cur, t_env *env, t_expand *exp)
{
	if (cur->content[exp->i] == '"' && exp->single_quote == 0)
		exp->double_quote = !exp->double_quote;
	if (cur->content[exp->i] == '\'' && exp->double_quote == 0)
		exp->single_quote = !exp->single_quote;
	if (cur->content[exp->i] == '$' && cur->content[exp->i + 1]
		&& (cur->content[exp->i + 1] != '"'
			|| (cur->content[exp->i + 2] && cur->content[exp->i + 2] == '"'))
		&& cur->content[exp->i + 1] != '$' && (exp->double_quote == 1
			|| exp->single_quote == 0) && cur->content[exp->i + 1] != ' ')
	{
		exp->j = exp->i + 1;
		if (cur->content[exp->j] == '?')
		{
			ft_strlcpy(exp->result + exp->x, exp->g_sr,
				ft_strlen(exp->g_sr) + 1);
			return (exp->x += ft_strlen(exp->g_sr), exp->j++, exp->i = exp->j);
		}
		expand_pt2b(cur, env, exp);
	}
	else
		utils_pt2(cur, exp);
	return (0);
}

void	expandpt3(t_node *current, t_env *env, t_expand *exp)
{
	if (!exp->tab)
	{
		free(exp->g_sr);
		free(current->content);
		current->content = NULL;
	}
	else
	{
		free(current->content);
		current->content = ft_strdup(exp->tab[0]);
		while (exp->tab[exp->i])
		{
			if (exp->tab[exp->i])
				push_midle(&current, 0, ft_strdup(exp->tab[exp->i]));
			exp->i++;
		}
		free(exp->g_sr);
		free_tab(exp->tab);
	}
}

void	expand(t_node *current, t_env *env)
{
	t_expand	exp;

	init_expand(&exp);
	while (current->content[exp.i])
	{
		if (!expand_pt1(current, env, &exp))
			return ;
	}
	exp.x = 0;
	exp.i = 0;
	exp.result = malloc(sizeof(char) * (exp.len + 1));
	if (!exp.result)
		return ;
	while (current->content[exp.i])
	{
		expand_pt2(current, env, &exp);
	}
	exp.i = 1;
	exp.result[exp.x] = '\0';
	if (exp.result[0] != '\0')
		exp.tab = ft_split_better(exp.result, ' ');
	free(exp.result);
	expandpt3(current, env, &exp);
}
