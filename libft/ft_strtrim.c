/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:30:20 by mudoh             #+#    #+#             */
/*   Updated: 2022/12/07 14:48:18 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	j;	
	char	*s2;

	if (!set || !s1)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	j = ft_strlen(s1) - 1;
	while (s1[j] && ft_strchr(set, s1[j]))
		j--;
	s2 = ft_substr((char *)s1, 0, j + 1);
	return (s2);
}
