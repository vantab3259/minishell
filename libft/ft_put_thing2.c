/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_thing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 22:51:30 by mudoh             #+#    #+#             */
/*   Updated: 2023/10/22 04:52:56 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strrlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_printchar(int c)
{
	return (write(2, &c, 1));
}

int	ft_printptr(size_t n)
{
	char	*base;
	int		r;

	base = "0123456789abcdef";
	r = 0;
	if (n >= 16)
	{
		r = r + ft_printptr(n / 16);
		r = r + ft_printptr(n % 16);
	}
	if (n <= 15)
	{
		ft_printchar(base[n]);
		r++;
	}
	return (r);
}

int	ft_ptr(size_t n)
{
	if (n == 0)
		return (write(2, "(nil)", 5));
	write (2, "0x", 2);
	return (ft_printptr(n) + 2);
}
