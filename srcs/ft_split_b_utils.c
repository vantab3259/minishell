/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_b_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:42:01 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/07 16:04:02 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	fsp_init(const char *s, char c, t_plit_data *data)
{
	data->s = s;
	data->c = c;
	data->word = 0;
	data->i = 0;
	data->y = 0;
	data->word = ft_countword_better((char *)s, c);
	data->str = malloc(sizeof(char *) * (data->word + 1));
	if (!data->str)
		return ;
}

int	tfb_malloc(const char *s, char c)
{
	int		y;
	char	r;

	y = 0;
	while (s[y] && s[y] != c)
	{
		if (s[y] == 34 || s[y] == 39)
		{
			r = s[y++];
			while (s[y] && s[y] != r)
				y++;
		}
		y++;
	}
	return (y);
}
