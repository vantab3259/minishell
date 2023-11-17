/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 12:53:48 by tbae              #+#    #+#             */
/*   Updated: 2023/02/02 14:38:13 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_dub(char *str)
{
	char	*cpy;
	size_t	i;
	size_t	size;

	i = 0;
	if (!str)
	{
		str = malloc (1);
		*str = '\0';
	}
	size = ft_strlen(str);
	cpy = malloc(size + 1);
	if (!cpy)
		return (NULL);
	while (i < size)
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*gnl_join(char *str1, char *str2, int nb_read)
{
	char	*str_f;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str_f = malloc(ft_strlen(str1) + nb_read + 1);
	while (str1[i])
	{
		str_f[i] = str1[i];
		i++;
	}
	while ((int)j < nb_read)
	{
		str_f[i] = str2[j];
		i++;
		j++;
	}
	str_f[i] = '\0';
	return (str_f);
}

char	*gnl_trim(char *str)
{
	char	*tmp;
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	size = ft_strlen(str);
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	if (size == i)
		return (NULL);
	tmp = malloc(size - i + 1);
	while (str[i])
	{
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}
