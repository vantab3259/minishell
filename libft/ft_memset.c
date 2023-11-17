/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:58:45 by mudoh             #+#    #+#             */
/*   Updated: 2022/12/07 14:43:21 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*strtmp;
	int				i;

	strtmp = (unsigned char *) str;
	i = 0;
	while (n > 0)
	{
		strtmp[i] = c;
		i++;
		n--;
	}
	return (strtmp);
}
