/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 03:13:15 by mudoh             #+#    #+#             */
/*   Updated: 2023/07/17 04:40:34 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		if (((unsigned char *)s1)[i] == '\0')
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
		n--;
	}
	return (0);
}
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	while (s[i])
	{
		i++;
	}
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i--;
	}
	return (0);
}




/* int	main(int ac, char **av, char **env)
{
	char *tab1[10] = {"echo", "hello", "je", "suis", "moha", NULL};
	// hello je suis moha\n
	char *tab2[10] = {"echo", "-n", "-", NULL};
	// hello
	char *tab3[10] = {"echo", "-nnnnnnn", "-nnnnnnna", "hello", NULL};
	// hello
	char *tab4[10] = {"echo", "-njaipasfaim", "hello", NULL};
	// -njaipasfaim hello\n
	char *tab5[10] = {"echo", "lol", "-nnnnnnn", "hello", NULL};
	// lol -nnnnnnn hello\n
	char *tab6[10] = {"echo", "-", NULL};
	// -\n
	char *tab7[10] = {"echo", "hello", "-n", "vraiment", NULL};
	// hello -n vraiment\n
	ft_echo(tab6, env);
} */