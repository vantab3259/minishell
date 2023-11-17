/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:49:05 by mudoh             #+#    #+#             */
/*   Updated: 2023/10/22 05:04:19 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbr(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		write(2, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		n = (n * (-1));
		ft_printchar('-');
		i++;
	}
	if (n >= 10)
	{
		i = i + ft_printnbr(n / 10);
		i = i + ft_printnbr(n % 10);
	}
	else
	{
		ft_printchar(n + 48);
		i++;
	}
	return (i);
}

int	ft_printunbr(unsigned int n)
{
	int	r;

	r = 0;
	if (n > 9)
	{
		r = r + ft_printunbr(n / 10);
		r = r + ft_printunbr(n % 10);
	}
	if (n <= 9)
	{
		ft_printchar(n + 48);
		r++;
	}
	return (r);
}

int	ft_hexaprint(unsigned int n)
{
	char	*base;
	int		r;

	base = "0123456789abcdef";
	r = 0;
	if (n >= 16)
	{
		r = r + ft_hexaprint(n / 16);
		r = r + ft_hexaprint(n % 16);
	}
	if (n <= 15)
	{
		ft_printchar(base[n]);
		r++;
	}
	return (r);
}

int	ft_hexaprint_m(unsigned int n)
{
	char	*base;
	int		r;

	base = "0123456789ABCDEF";
	r = 0;
	if (n >= 16)
	{
		r = r + ft_hexaprint_m(n / 16);
		r = r + ft_hexaprint_m(n % 16);
	}
	if (n <= 15)
	{
		ft_printchar(base[n]);
		r++;
	}
	return (r);
}
