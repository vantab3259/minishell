/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 04:25:39 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/10 00:52:49 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env(t_data *data, char **mini_env)
{
	int		idx_str;
	t_node	*tmp;

	idx_str = 0;
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
	while (mini_env[idx_str])
	{
		printf("%s\n", mini_env[idx_str]);
		idx_str++;
	}
	return (0);
}
