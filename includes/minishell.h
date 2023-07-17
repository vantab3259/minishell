/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:44:09 by mudoh             #+#    #+#             */
/*   Updated: 2023/07/17 23:12:21 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>

typedef struct t_data
{
	char	**path;
	char	**env;
	int		*pid;
	int		fd[2];
	int		nbcmd;
	int		prev;
	int		input_f;
	int		output_f;

}			t_data;

typedef struct t_info
{
	char	**arg;
	char	*command;
	char	**files;
	int		*tp_f;
}			t_info;

int			ft_countword(char *s, char c);
t_info	parse(char *str);
void	freetab(char **tab);
int	ft_pwd(char **arg, char **env);
int	ft_cd(char **arg, char **env);
int	exec_builtin(char **arg, char **env);
int	ft_echo(char **arg, char **env);

// input {ls>a<<b>c<d>>e}
// output {ls > a << b > c < d >> e}


#endif