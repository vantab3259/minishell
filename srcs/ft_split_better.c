/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_better.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:00:27 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/05 03:42:20 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	check_quote(char *line)
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
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_countword_better(char *s, char c)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
		}
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

static char	*tab_filler_better(char const *s, char c)
{
	char	*str;
	int		i;
	char	quote;

	i = 0;
	str = malloc(sizeof(char) * (tfb_malloc(s, c) + 1));
	if (!str)
		return (NULL);
	while (s[i] && s[i] != c)
	{
		if (s[i] == 34 || s[i] == 39)
		{
			quote = s[i];
			str[i] = s[i];
			i++;
			while (s[i] && s[i] != quote)
			{
				str[i] = s[i];
				i++;
			}
		}
		str[i] = s[i];
		i++;
	}
	return (str[i] = '\0', str);
}

char	**ft_split_better(char const *s, char c)
{
	t_plit_data	data;

	if (!s)
		return (NULL);
	fsp_init(s, c, &data);
	if (!data.str)
		return (NULL);
	data.str[data.word] = NULL;
	while (data.s[data.i] != '\0')
	{
		if (((data.i == 0) || (data.s[data.i - 1] == data.c))
			&& (data.y < data.word) && (data.s[data.i] != data.c))
		{
			data.str[data.y] = tab_filler_better(&data.s[data.i], data.c);
			if (data.str[data.y])
				data.i += ft_strlen(data.str[data.y]);
			data.y++;
		}
		if (!data.s[data.i])
			break ;
		data.i++;
	}
	return (data.str);
}
