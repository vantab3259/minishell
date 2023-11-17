/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbae <tbae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:52:19 by tbae              #+#    #+#             */
/*   Updated: 2023/11/04 18:12:06 by tbae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_pipe(t_data *data, int idx)
{
	if (idx == data->pipe.nbcmd - 1)
		write(2, ft_itoa(errno), ft_strlen(ft_itoa(errno)));
	else
		ft_print_error(2, "%s\n", strerror(errno));
}

int	ft_printstr(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return (write(2, "(null)", 6));
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}

void	ft_print_error(int fd, const char *format, ...)
{
	va_list	arg_lst;
	char	str[2];
	int		idx;

	idx = 0;
	va_start(arg_lst, format);
	while (format[idx])
	{
		if (format[idx] != '%')
		{
			str[0] = format[idx];
			str[1] = '\0';
			write (fd, str, 1);
		}
		else if (format[idx] == '%')
		{
			ft_printstr(va_arg(arg_lst, char *), fd);
			idx++;
		}
		idx++;
	}
	va_end(arg_lst);
	return ;
}
