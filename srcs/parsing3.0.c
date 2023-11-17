/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 10:46:19 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/05 10:53:55 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	cote_pb(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
			{
				i++;
			}
			if (!line[i])
				return (free(line), false);
		}
		i++;
	}
	return (true);
}

int	check_after_sep(char *str)
{
	int		i;
	int		j;
	char	**sepa;

	sepa = (char *[]){"<<", ">>", "<", ">", "|", NULL};
	j = 0;
	i = ft_strlen(str);
	while (!ft_strncmp(str + i, sepa[j], ft_strlen(sepa[j]))
		&& i != 0)
	{
		while (sepa[j] != NULL)
		{
			if (!ft_strncmp(str + i, sepa[j], ft_strlen(sepa[j]))
				|| i == 0)
				return (i);
			j++;
		}
		i--;
	}
	return (i);
}

void	quote_verif(int *i, int *j, char **str, char *quote)
{
	if (*(*str + *i) == 34 || *(*str + *i) == 39)
	{
		*quote = *(*str + *i);
		(*i)++;
		while (*(*str + *i) && *(*str + *i) != *quote)
			(*i)++;
	}
	*j = 0;
}

void	init_p_data(t_sstate *t_s)
{
	t_s->i = -1;
	t_s->j = 0;
	t_s->quote = '\0';
	t_s->c_pt = 0;
	t_s->check = 0;
}

void	end_pte(t_node **head, t_sstate *t_s, char *str)
{
	t_s->i = ft_strlen(str);
	if (str[t_s->i - 1] != '<'
		&& str[t_s->i - 1] != '>' && str[t_s->i - 1] != '|')
		p_bk(head, 0, ft_substr(str, t_s->c_pt, t_s->i - t_s->c_pt));
}
