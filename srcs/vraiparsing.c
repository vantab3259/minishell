/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vraiparsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:35:21 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/07 16:47:33 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	vraiparsing(t_data *data, char *prompt)
{
	if (!cote_pb(prompt))
	{
		printf("error syntaxe single cote ou dcote\n");
		return (false);
	}
	data->head = parse(prompt, data->head, data->head_env);
	if (!data->head)
		return (false);
	data->origin = data->head;
	if (verif_syntax_error(data->head))
	{
		free_list(data->origin);
		data->head = NULL;
		data->origin = NULL;
		return (false);
	}
	return (true);
}
