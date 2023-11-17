/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:38:51 by mudoh             #+#    #+#             */
/*   Updated: 2023/10/26 02:20:36 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h> // Pour LONG_LONG_MIN et LONG_LONG_MAX
#include <errno.h>  // Pour errno
#include <stdlib.h> // Pour strtol
#include <errno.h>
#include <stdbool.h>

int	ft_atoi(const char	*nptr)
{
	int	i;
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = (num * 10) + (nptr[i] - '0');
		i++;
	}
	return (num * sign);
}

long long	ft_atoll(const char *nptr)
{
	int			i;
	int			sign;
	long long	num;

	sign = 1;
	num = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (num > (9223372036854775807 - (nptr[i] - '0')) / 10 && sign == 1)
			return (errno = ERANGE, 9223372036854775807);
		if (num > (9223372036854775807 - (nptr[i] - '0')) / 10 && sign != 1)
			return (errno = ERANGE, -9223372036854775807);
		num = (num * 10) + (nptr[i] - '0');
		i++;
	}
	return (num * sign);
}

bool	ft_atoll_verif(const char *nptr)
{
	int	i;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			return (true);
		i++;
	}
	return (false);
}
