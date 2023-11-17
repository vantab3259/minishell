/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 21:02:48 by mudoh             #+#    #+#             */
/*   Updated: 2022/12/07 13:48:34 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void	*s, size_t	n)
{
	unsigned char	*strtmp;

	strtmp = (unsigned char *)s;
	while (n > 0)
	{
		*strtmp = '\0';
		strtmp++;
		n--;
	}
}
