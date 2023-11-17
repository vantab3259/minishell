/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:55:24 by tbae              #+#    #+#             */
/*   Updated: 2023/11/09 21:12:36 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verifn(t_data *data)
{
	t_node	*tmp;
	int		i;
	int		j;
	int		n;

	n = 0;
	data->head = data->head->next;
	tmp = data->head;
	while (tmp->next)
	{
		j = 0;
		if (tmp->content[j] != '-' && j == 0)
			return (n);
		if (tmp->content[j] == '-' && !tmp->content[j + 1])
			return (n);
		while (tmp->content[++j])
		{
			if (tmp->content[j] != 'n')
				return (n);
		}
		n++;
		tmp = tmp->next;
	}
	return (n);
}

int	skip_nodes(t_data *data, int m)
{
	int	n;

	n = m;
	while (n > 0)
	{
		data->head = data->head->next;
		n--;
	}
	return (n);
}

void	print_words(t_data *data)
{
	bool	is_first;

	is_first = true;
	while (data->head && data->head->type != 5)
	{
		if (data->head->type > 0 && data->head->type < 5)
		{
			data->head = data->head->next;
			data->head = data->head->next;
		}
		else
		{
			if (!is_first)
				printf(" ");
			is_first = false;
			printf("%s", data->head->content);
			data->head = data->head->next;
		}
	}
}

int	ft_echo(t_data *data)
{
	int		m;
	t_node	*tmp;

	tmp = data->head;
	while (data->head && data->head->type != 5)
		data->head = data->head->next;
	if (data->head)
		data->head = data->head->next;
	while (data->head && data->head->content && data->head->type != 5)
	{
		if (data->head->type == 3)
			return (data->head = tmp, 1);
		data->head = data->head->next;
	}
	data->head = tmp;
	if (data->head->next == NULL)
		return (printf("\n"));
	m = verifn(data);
	skip_nodes(data, m);
	print_words(data);
	if (!m)
		printf("\n");
	return (0);
}
