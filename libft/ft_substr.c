/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:06:52 by mudoh             #+#    #+#             */
/*   Updated: 2023/10/29 20:20:44 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	smax(char const *s, size_t len, unsigned int start)
{
	size_t	i;

	i = 0;
	while (i < len && s[start])
	{
		start++;
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	j;

	j = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		str = malloc(1);
		if (!str)
			return (NULL);
		*str = '\0';
		return (str);
	}
	else
		str = malloc(sizeof(char) * (smax(s, len, start) + 1));
	if (!str)
		return (NULL);
	while (s[start] && j < len)
		str[j++] = s[start++];
	str[j] = 0;
	return (str);
}
