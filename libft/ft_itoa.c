/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:56:11 by mudoh             #+#    #+#             */
/*   Updated: 2022/12/07 15:17:16 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	len10(long n)
{
	long	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_str(long n, int len)
{
	int		stop;
	char	*s;

	stop = 0;
	s = ft_calloc(sizeof(char), len10(n) + 1);
	if (!s)
		return (NULL);
	if (n < 0)
	{
		stop++;
		n *= -1;
		s[0] = '-';
	}
	s[len] = '\0';
	while (len-- > stop)
	{
		s[len] = (n % 10) + '0';
		n = n / 10;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;
	long	nb;

	nb = (long)n;
	if (nb == 0)
	{
		s = malloc(2);
		s[0] = '0';
		s[1] = '\0';
		return (s);
	}
	len = len10(nb);
	s = ft_str(nb, len);
	return (s);
}
