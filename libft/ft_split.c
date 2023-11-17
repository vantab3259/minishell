/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:25:45 by mudoh             #+#    #+#             */
/*   Updated: 2022/12/07 14:44:20 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countword(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

static char	*tab_filler(char const *s, char c)
{
	char	*str;
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (s[y] && s[y] != c)
		y++;
	str = malloc(sizeof(char) * (y + 1));
	if (!str)
		return (NULL);
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		word;
	int		y;

	i = 0;
	y = 0;
	if (!s)
		return (NULL);
	word = ft_countword((char *)s, c);
	str = malloc(sizeof(char *) * (word + 1));
	if (!str)
		return (NULL);
	str[word] = NULL;
	while (s[i])
	{
		if (((i == 0) || (s[i - 1] == c)) && (y < word) && (s[i] != c))
		{
			str[y] = tab_filler(&s[i], c);
			y++;
		}
		i++;
	}
	return (str);
}
