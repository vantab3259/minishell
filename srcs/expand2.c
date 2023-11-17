/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:20:17 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/10 12:22:34 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_expand(t_expand *exp)
{
	exp->is_first = true;
	exp->tab = NULL;
	exp->key = NULL;
	exp->tab = NULL;
	exp->result = NULL;
	exp->g_sr = NULL;
	exp->single_quote = 0;
	exp->double_quote = 0;
	exp->i = 0;
	exp->j = 0;
	exp->len = 0;
	exp->tab = NULL;
	exp->k = 0;
	exp->g_sr = ft_itoa(g_bal);
}

void	utils_pt2(t_node *cur, t_expand *exp)
{
	exp->result[exp->x] = cur->content[exp->i];
	exp->i++;
	exp->x++;
}

int	expand_pt1(t_node *cur, t_env *env, t_expand *exp)
{
	if (cur->content[exp->i] == '"' && exp->single_quote == 0)
		exp->double_quote = !exp->double_quote;
	if (cur->content[exp->i] == '\'' && exp->double_quote == 0)
		exp->single_quote = !exp->single_quote;
	if (cur->content[exp->i] == '$'
		&& cur->content[exp->i + 1] && (cur->content[exp->i + 1] != '"'
			|| (cur->content[exp->i + 2] && cur->content[exp->i + 2] == '"'))
		&& cur->content[exp->i + 1] != '$' && (exp->double_quote == 1
			|| exp->single_quote == 0) && cur->content[exp->i + 1] != ' ')
	{
		if (!expand_pt1b(cur, env, exp))
			return (0);
	}
	else
	{
		exp->len++;
		exp->i++;
	}
	return (1);
}
