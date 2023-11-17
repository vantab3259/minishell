/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:03:03 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/10 11:53:19 by mudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_white(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr("\t\n\r\v\f ", str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	init_main(t_main *main, t_data *data)
{
	main->head = NULL;
	main->head_env = NULL;
	main->prompt = NULL;
	ft_memset(data, 0, sizeof(*data));
}

int	cut_main(t_main *main)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc);
	main->prompt = readline("$> ");
	if (!main->prompt)
		main->prompt = "exit";
	if (!main->prompt[0] || is_white(main->prompt))
	{
		free(main->prompt);
		return (1);
	}
	add_history(main->prompt);
	return (0);
}

void	cut_main_two(t_data *data, t_main *main)
{
	signal(SIGINT, &ctrlc);
	data->head = main->head;
	if (unset_export_cd_exit(data) != 0)
		ft_pipe(data);
	free_list(data->origin);
	data->head = NULL;
	unlink("here_doc_tmp");
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_main	main;

	if (ac == 1)
	{
		init_main(&main, &data);
		data.mini_env = get_env(env, &main.head_env);
		data.head_env = main.head_env;
		while (1)
		{
			if (cut_main(&main))
				continue ;
			if (!vraiparsing(&data, main.prompt))
				continue ;
			main.head = data.head;
			if (here_doc_init(&data, &main) == 130)
			{
				free_list(data.origin);
				continue ;
			}
			cut_main_two(&data, &main);
		}
	}
}
