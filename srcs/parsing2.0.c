/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 10:47:12 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/10 12:14:53 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_tab_elem(char *str, t_node **head, t_env *env)
{
	t_sstate	t_s;
	char		**sepa;

	sepa = (char *[]){"<<", ">>", "<", ">", "|", NULL};
	init_p_data(&t_s);
	while (str[++t_s.i] != '\0')
	{
		quote_verif(&(t_s.i), &(t_s.j), &(str), &(t_s.quote));
		while (sepa[t_s.j] != NULL)
		{
			if (!ft_strncmp(str + t_s.i, sepa[t_s.j], ft_strlen(sepa[t_s.j])))
			{
				if (t_s.i != 0)
					p_bk(head, 0, ft_substr(str, t_s.c_pt, t_s.i - t_s.c_pt));
				p_bk(head, t_s.j + 1, ft_strdup(sepa[t_s.j]));
				t_s.c_pt = t_s.i + ft_strlen(sepa[t_s.j]);
				t_s.i += ft_strlen(sepa[t_s.j]) - 1;
				break ;
			}
			t_s.j++;
		}
		if (!str[t_s.i])
			break ;
	}
	end_pte(head, &t_s, str);
}

int	remove_quote_calcul(t_node *current)
{
	t_sstate	q_c;

	init_p_data(&q_c);
	q_c.i = 0;
	while (current->content[q_c.i])
	{
		if (current->content[q_c.i] == 34 || current->content[q_c.i] == 39)
		{
			q_c.c_pt = current->content[q_c.i++];
			while (current->content[q_c.i]
				&& current->content[q_c.i] != q_c.c_pt)
			{
				q_c.i++;
				q_c.j++;
			}
			q_c.i++;
		}
		else
		{
			q_c.j++;
			q_c.i++;
		}
	}
	return (q_c.j);
}

void	action_quote(t_node *current, int *i, int *x, char **result)
{
	int	quote;

	while (current->content[*i])
	{
		if (current->content[*i] == 34 || current->content[*i] == 39)
		{
			quote = current->content[(*i)++];
			while (current->content[*i] && current->content[*i] != quote)
			{
				(*result)[*x] = current->content[*i];
				(*i)++;
				(*x)++;
			}
			(*i)++;
		}
		else
		{
			(*result)[*x] = current->content[*i];
			(*x)++;
			(*i)++;
		}
	}
}

void	remove_quote(t_node *head)
{
	t_node	*current;
	int		i;
	int		len;
	int		x;
	char	*result;

	if (!head->content)
		return ;
	x = 0;
	current = head;
	i = 0;
	len = remove_quote_calcul(current);
	result = ft_calloc(len + 2, sizeof(char));
	action_quote(current, &i, &x, &result);
	free(current->content);
	current->content = result;
}
