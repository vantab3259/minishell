/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 04:01:34 by mudoh             #+#    #+#             */
/*   Updated: 2023/07/17 22:10:38 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

int		ft_cd(char **arg, char **env)
{
	printf("%s\n", arg[1]);
	if(arg[1] && arg[2])
		return(printf("bash: cd: too many arguments\n"), 1);
	if(!arg[1])
	{
		if(chdir(getenv("HOME")) == -1)
			return(printf("bash: cd: HOME not found\n"), 1);
		return (0);
	}
	if(chdir(arg[1]) == -1)
		return(printf("bash: cd: %s: No such file or directory\n", arg[1]), 1);
	return (0);
}


int		ft_pwd(char **arg, char **env)
{
	char	buffer[PATH_MAX];
	(void)env;
	(void)arg;

	if (getcwd(buffer, sizeof(buffer)) == NULL)
		return (printf("Cannot get current working directory path\n"), 1);
	printf("%s\n", buffer);
	return (0);
}

int	verifn(char **arg)
{
	int	i;
	int	j;
	int	n;

	j = 0;
	i = 1;
	n = 0;
	while (arg[i])
	{
		j = 0;
		if (arg[i][j] != '-' && j == 0)
			return (n);
		if(arg[i][j] == '-' && !arg[i][j + 1])
			return(n);
		while (arg[i][++j]) // nnn
		{
			if (arg[i][j] != 'n')
			{
				return (n);
			}
		}
		n++;
		i++;
	}
	return (n);
}
int	ft_echo(char **arg, char **env)
{
	int	i;
	int	n;

	n = verifn(arg);
	i = 1;
	while (arg[i + n])
	{
		printf("%s", arg[i + n]);
		if (arg[++i + n])
			printf(" ");
	}
	if (!n)
		printf("\n");
	return (0);
}

typedef int (*func)(char **, char **);

int	exec_builtin(char **arg, char **env)
{
	static char *tab[4] = {"echo", "cd", "pwd", NULL};
	static func builtin[4] = {&ft_echo, &ft_cd, &ft_pwd, NULL};
	
	int i = 0;
	while (i < 4)
	{
		//printf("%i strcmp de %s %s\n", !ft_strcmp(tab[i], arg[0]), tab[i], arg[0]);
		if (!ft_strcmp(tab[i], arg[0]))
			return (builtin[i](arg, env), 1);
		i++;
	}
	return (0);
}