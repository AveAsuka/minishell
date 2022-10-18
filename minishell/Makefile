# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbrianna <lbrianna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 12:03:01 by lbrianna          #+#    #+#              #
#    Updated: 2022/09/24 18:41:20 by lbrianna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Арина
SRCS = srcs/main.c srcs/free.c srcs/handler.c srcs/minishell.c \
	srcs/parser/parser.c srcs/parser/parser2.c srcs/parser/pars_utils.c \
	srcs/parser/envp.c srcs/parser/envp_list.c srcs/parser/create_command.c \
	srcs/parser/build_cmd.c srcs/parser/make_redirect.c srcs/parser/make_cmd_path.c \
	srcs/parser/make_pipe_arg.c srcs/parser/redir_utils.c \
	srcs/check_all_quotes.c srcs/check_command.c srcs/parser/syntax_utils.c srcs/check_utils.c\

# Егор
FILES			=	executer/executor.c \
					executer/ft_libft_lst_mod.c \
		 			executer/builtins/builtins_echo.c executer/builtins/builtins_pwd.c executer/builtins/builtins_env.c \
		 			executer/builtins/builtins_export.c executer/builtins/builtins_export_alph.c executer/builtins/builtins_export_new.c \
		 			executer/builtins/builtins_unset.c \
					executer/builtins/builtins_cd.c \
					executer/builtins/builtins_exit.c \
					executer/env_operations.c \
					executer/execve_action.c \
					executer/redirect.c \
					executer/pipe_action.c \
					executer/utils.c \
					executer/delete_utils.c \
					executer/error_and_free.c \
					executer/norme.c \
					executer/builtins/builtins_utils.c \
					executer/utils_2.c \
					executer/pipe_utils.c \

OBJS = $(SRCS:%.c=%.o) $(FILES:%.c=%.o)

INCLUDES = includes/
HEADER = minishell.h
CC = gcc 
CFLAGS = -Wall -Wextra -Werror -g
# 1) -fsanitize=address		// Arina
# 2) -fsanitize=thread -g 	// philo - don't work
RM = rm -f

LIB = libft/libft.a

RDLN = -lreadline -L/Users/lbrianna/.brew/Cellar/readline/8.1.2/lib -I/Users/lbrianna/.brew/Cellar/readline/8.1.2/include/readline\

all:  libft $(NAME)

%.o: %.c $(INCLUDES)$(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

$(NAME): $(OBJS) $(LIB)
	$(CC) -g $(CFLAGS) $(RDLN) $(OBJS) $(LIB) -o $(NAME)
libft:
	@make -C libft/
clean:
	@make -C libft/ clean
	$(RM) $(OBJS)

fclean: clean
	@make -C libft/ fclean
	$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean re libft