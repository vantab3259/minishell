/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:30:46 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/10 01:01:43 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	verif_all_syntax2(t_node **head)
{
	if ((*head)->type != 0 && (*head)->type != 5
		&& (*head)->next->type != 0)
	{
		if ((*head)->next->type == 5)
		{
			ft_printf("bash: syntax error near unexpected token `|'\n");
			return (true);
		}
		else
		{
			ft_printf("bash: syntax error near unexpected `newline'\n");
			return (true);
		}
	}
	return (false);
}

bool	verif_all_syntax(t_node **head)
{
	while (*head != NULL)
	{
		if ((*head)->next)
		{
			if (verif_all_syntax2(head))
				return (true);
		}
		else
		{
			if ((*head)->type != 0)
			{
				if ((*head)->type == 5)
				{
					ft_printf("bash: syntax error near unexpected token `|'\n");
				}
				else
				{
					ft_printf("bash: syntax error near unexpected `newline'\n");
				}
				return (true);
			}
		}
		*head = (*head)->next;
	}
	return (false);
}

bool	verif_syntax_error(t_node *head)
{
	if (!head)
		return (false);
	if ((head->type != 0 && !head->next))
	{
		if (head->type == 5)
		{
			ft_printf("bash: syntax error near unexpected token `|'\n");
			return (true);
		}
		else
		{
			ft_printf("bash: syntax error near unexpected `newline'\n");
			return (true);
		}
	}
	if (verif_all_syntax(&head))
		return (true);
	if (head && head->type != 0)
		return (true);
	return (false);
}

t_node	*parse(char *str, t_node *head, t_env *env)
{
	char	**tab;
	int		i;
	t_node	*current;
	t_node	*tmp;

	tab = ft_split_better(str, ' ');
	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
	{
		parse_tab_elem(tab[i], &head, env);
		i++;
	}
	current = head;
	while (current)
	{
		expand(current, env);
		remove_quote(current);
		tmp = current->next;
		if (current && !current->content)
			remove_list(&head, current);
		current = tmp;
	}
	return (free_tab(tab), head);
}
