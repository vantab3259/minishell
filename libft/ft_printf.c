/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:39:54 by mudoh             #+#    #+#             */
/*   Updated: 2023/10/22 05:04:57 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstrornull(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(2, "(null)", 6));
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_find_arg(char c, va_list arg_lst)
{
	if (c == 'c')
		return (ft_printchar(va_arg(arg_lst, int)));
	if (c == 's')
		return (ft_printstrornull(va_arg(arg_lst, char *)));
	if (c == 'd' || c == 'i')
		return (ft_printnbr(va_arg(arg_lst, int)));
	if (c == 'p')
		return (ft_ptr(va_arg(arg_lst, size_t)));
	if (c == 'u')
		return (ft_printunbr(va_arg(arg_lst, unsigned int)));
	if (c == 'x')
		return (ft_hexaprint(va_arg(arg_lst, unsigned int)));
	if (c == 'X')
		return (ft_hexaprint_m(va_arg(arg_lst, unsigned int)));
	if (c == '%')
		return (write(2, "%%", 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg_lst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	va_start(arg_lst, format);
	while (format[i])
	{
		if (format[i] != '%')
		{
			ft_printchar(format[i]);
			j++;
		}
		else if (format[i] == '%')
		{
			j = j + ft_find_arg(format[i + 1], arg_lst);
			i++;
		}
		i++;
	}
	va_end(arg_lst);
	return (j);
}

/*
int	main(void)
{
	int i;
	int	j;
	char *str;
	
	str = "qwerty";
	
	j = ft_printf("ft_printf ->bonjour%c je suis %s %% %p", ',', "Mona", str);
	printf(" : ");
	i = printf("   printf ->bonjour%c je suis %s %% %p", ',', "Mona", str);
	printf("\n");
	printf("%d : %d", j, i);
	return (0);
}
*/