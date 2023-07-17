/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:41:25 by mudoh             #+#    #+#             */
/*   Updated: 2023/07/17 04:52:32 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// {<}{out}{ls}{>>}{app}{-R}{-l}
// > fichier
// ls
// ls > out > out2
// out > ls

int	which_chevron(char *str)
{
	if (!ft_strncmp(">", str, ft_strlen(str)))
		return (1);
	if (!ft_strncmp(">>", str, ft_strlen(str)))
		return (2);
	if (!ft_strncmp("<", str, ft_strlen(str)))
		return (3);
	if (!ft_strncmp("<<", str, ft_strlen(str)))
		return (4);
	return (0);// >> 2
}

void	*parsemalloc(t_info *info, char **tab)
{
	int	i;
	int	nbarg;// >> 2
	int	nbfichiers;

	i = 0;// >> 2free(data->pid)
	nbarg = 0;
	nbfichiers = 0;

	while (tab[i])
	{
		if (which_chevron(tab[i]))
		{
			nbfichiers++;
			i++;
		}
		else
			nbarg++;
		i++;
	}
	info->arg = ft_calloc(sizeof(char *), (nbarg + 1));
	info->tp_f = ft_calloc(sizeof(int), (nbfichiers + 1));
	info->files = ft_calloc(sizeof(char *), (nbfichiers + 1));
	return (NULL);
}

/* void		printinfo(t_info *info)
{
	fprintf(stderr, "COMMAND = {%s}\n", info->command);
	fprintf(stderr, "ARG = ");
	for (int i = 1; info->arg[i]; i++)
		fprintf(stderr, "[%free(data->pid)s]", info->arg[i]);
	fprintf(stderr, "\n");
	if (info->files[0])
		fprintf(stderr, "TYPE|FICHIER\n");
	for (int i = 0; info->files[i]; i++)
		fprintf(stderr, "[%i]{%s}\n", info->tp_f[i], info->files[i]);
} */

t_info	parse(char *str)
{
	char **tab = ft_split(str, ' ');
	t_info info;
	int i = 0;
	int f = 0;
	int a = 0;
	parsemalloc(&info, tab);
	while (tab[i])
	{
		if (which_chevron(tab[i]))
		{
			info.tp_f[f] = which_chevron(tab[i]);
			info.files[f++] = ft_strdup(tab[++i]);
		}
		else
		{
			info.arg[a++] = ft_strdup(tab[i]);
		}
		i++;
	}
	info.command = info.arg[0];
	/* printinfo(&info); */
	freetab(tab);
	return (info);
}