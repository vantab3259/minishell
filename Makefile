# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mudoh <mudoh@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 16:03:04 by tbae              #+#    #+#              #
#    Updated: 2023/11/10 12:03:56 by mudoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

LIBFT			=	libft.a

DIR_SRCS		=	srcs

DIR_OBJS		=	objs

SRCS_NAMES		=	main.c\
					utils.c\
					parsing.c\
					parsing2.0.c\
					parsing3.0.c\
					ft_split_better.c\
					ft_split_b_utils.c\
					list_utils.c\
					list_utils_next.c\
					list_utils2.c\
					env.c\
					builtin/cd.c\
					builtin/cd_utils.c\
					builtin/echo.c\
					builtin/env.c\
					builtin/exit.c\
					builtin/export.c\
					builtin/pwd.c\
					builtin/unset.c\
					pipe/pipe.c\
					pipe/pipe_utils.c\
					error.c\
					vraiparsing.c \
					free.c\
					unset_export_cd_exit.c\
					redirection.c\
					here_doc.c\
					expand.c\
					expand3.c\
					expand2.c\



OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

INC				=	-Iincludes -Ilibft

LIB				=	-lreadline -lm -Llibft -lft

CC				=	cc

CDFLAGS 		= -MMD -MP

CFLAGS			=	-g3 -Wall -Werror -Wextra -

MAKEFLAGS		=	--no-print-directory

all:	${NAME}

$(NAME): $(DIR_OBJS) $(OBJS)
	make -C libft
	$(CC) -g3 ${INC} $(OBJS) $(LIB) -o $(NAME)
	@echo "\033[31;5mminishell\033[0m"

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) -g3 $(CDFLAGS) $(INC) -c $< -o $@

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)
	mkdir -p $(DIR_OBJS)/builtin
	mkdir -p $(DIR_OBJS)/pipe

clean:
	make clean -C libft
	rm -rf ${DIR_OBJS}

fclean:	clean
	make fclean -C libft
	rm -rf ${LIBFT}
	rm -rf ${NAME}

leaks: ${NAME}
	clear && valgrind --suppressions=minishell.suppr -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell

leask: $(NAME)
	clear && valgrind --suppressions=minishell.suppr -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell


env: $(NAME)
	env -i ./minishell

stop:
	rm -rf ${NAME}

re:	fclean all

-include $(DEPS)

.PHONY:	all clean fclean re bonus leaks stop
# .SILENT:
