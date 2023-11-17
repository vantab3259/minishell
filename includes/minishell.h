/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:11:39 by tbae              #+#    #+#             */
/*   Updated: 2023/11/10 12:03:35 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <features.h>
# include <sys/types.h>
# include <sys/stat.h>

extern int	g_bal;

typedef struct s_plit_data
{
	char const	*s;
	char		c;
	char		**str;
	int			word;
	int			i;
	int			y;
}	t_plit_data;

typedef struct s_parsing_data
{
	int		i;
	int		j;
	char	quote;
	int		c_pt;
	int		check;
}	t_sstate;

typedef struct s_node
{
	int				type;
	char			*content;
	struct s_node	*next;
}					t_node;

typedef struct s_env
{
	char			*content;
	char			*key;
	struct s_env	*next;
}					t_env;

typedef struct s_pipe
{
	char			**path;
	char			**cmd;
	pid_t			*pid;
	int				nbcmd;
	int				prev;
	int				fd[2];
	int				nbarg;
	int				infile;
	int				outfile;
}					t_pipe;

typedef struct s_data
{
	char			**mini_env;
	t_node			*head;
	t_node			*origin;
	t_pipe			pipe;
	t_env			*head_env;
}					t_data;

typedef struct s_main{
	t_node	*head;
	t_env	*head_env;
	char	*prompt;
}	t_main;

typedef struct s_expand
{
	int		single_quote;
	int		double_quote;
	int		k;
	int		x;
	int		i;
	int		j;
	int		len;
	bool	is_first;
	char	*key;
	t_env	*cell;
	char	**tab;
	char	*g_sr;
	char	*result;
}	t_expand;

int					tfb_malloc(const char *s, char c);
//unset_export_cd_exit
int					unset_export_cd_exit(t_data *data);
int					ft_unset(t_data *data);
int					ft_export(t_data *data);
int					ft_cd(t_data *data);
int					ft_exit(t_data *data, int t);

//builtin
void				handle_sig_heredocs(int sig);
void				ctrlc(int sig);
void				list_to_tab(t_data *data);
void				cd_list(t_data *data, char *path);

int					openfiles_builting(t_data *data);
//list
void				display_list(t_node *head);
void				free_list(t_node *head);
void				p_bk(t_node **head, int type, char *content);
void				push_front(t_node **head, int type, char *content);
void				push_midle(t_node **head, int type, char *content );
void				remove_list(t_node **head, t_node *node_to_remove);
//listenv
void				remove_list_env(t_env **head, t_env *node_to_remove);
void				display_list_env(t_env *head);
void				free_list_env(t_env *head);
void				push_back_env(t_env **head, char *key, char *content);
void				push_front_env(t_env **head, char *key, char *content);
t_env				*create_node_env(char *key, char *content);
bool				vraiparsing(t_data *data, char *str);
int					expand_pt1(t_node *current, t_env *env, t_expand *exp);
//parss

void				utils_pt2(t_node *cur, t_expand *exp);
void				init_expand(t_expand *exp);
int					expand_pt1b(t_node *current, t_env *env, t_expand *exp);
void				expand_pt2b(t_node *current, t_env *env, t_expand *exp);
void				remove_quote(t_node *head);
void				quote_verif(int *i, int *j, char **str, char *quote);
void				init_p_data(t_sstate *t_s);
void				end_pte(t_node **head, t_sstate *t_s, char *str);
void				parse_tab_elem(char *str, t_node **head, t_env *env);
bool				cote_pb(char *prompt);
//on check qu'il n'y est pas une cote seul
char				**ft_split_better(char const *s, char c);
//split aux espace en prenant en compte les quotes
t_node				*parse(char *prompt, t_node *head, t_env *env);
//d'abord un split aux espace puis a chaque string on parse
//aux separateur et on range dans la chaine
//prend un tab tmp de mes mot et sep et env,
//fait l'expand en fonction des condition
bool				verif_syntax_error(t_node *head);
void				expand(t_node *current, t_env *env);
//env
void				fsp_init(const char *s, char c, t_plit_data *data);
int					ft_countword_better(char *s, char c);
int					builtin_env(t_env **head_env, char **env);
t_env				*search_content(t_env *env, char *key);
int					print_env(t_data *data, char **mini_env);
char				**get_env(char **env, t_env **head_env);
char				*get_line(char **env, char *str);
int					ft_pipe(t_data *data);
void				check_builtin(t_data *data,
						char **arg, char **mini_env);
void				free_tab(char **tab);
void				ft_print_error(int fd, const char *format, ...);
int					ft_pwd(t_data *data);
int					ft_echo(t_data *data);
void				free_pipe(t_data *data);
void				free_here_doc(t_data *data);
int					here_doc_init(t_data *data, t_main *main);
void				redirection(t_data *data, int i, int *fd);
int					openfiles(t_data *data);
char				*strdup_like(char *s, int start, int end);
int					ft_isvalidforvariablename(char c, bool is_first);
void				check_file(t_data *data);
void				build_command(t_data *data);
char				*get_good_path(char *cmd, char **paths);
char				*joinslash(char *tab, char *path);
char				*get_line(char **env, char *str);

#endif
