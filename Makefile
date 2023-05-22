
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: florianmastorakis <marvin@42.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 20:55:35 by florianma         #+#    #+#              #
#    Updated: 2021/09/15 11:22:13 by florianma        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c \
parsing/free_all.c \
parsing/ft_split_mini.c \
parsing/get_command.c \
parsing/get_option.c \
parsing/parser.c \
parsing/redirection_cmd_option.c \
parsing/redirection_error.c \
parsing/redirection_in.c \
parsing/redirection_out.c \
parsing/struct_management.c \
parsing/utils.c \
builtin/display_pwd.c \
builtin/exit.c \
builtin/export.c \
builtin/ft_env.c \
builtin/get_cd.c \
builtin/unset.c \
env/get_env.c \
env/get_path.c \
free/free_tab.c \
init/init.c \
pipes/errors_parse.c \
pipes/errors.c \
pipes/free.c \
pipes/here_doc_bonus.c \
pipes/init_bonus.c \
pipes/paths.c \
pipes/processes_bonus.c \
pipes/processes2_bonus.c \
pipes/utils.c \
pipes/utils2.c \
pipes/utils3.c \
utils/ft_putchar_fd.c \
utils/ft_putstr_fd.c \
utils/ft_split.c \
utils/ft_strchr.c \
utils/ft_strcmp.c \
utils/ft_strncmp.c \
utils/ft_strdup.c \
utils/ft_strcpy.c \
utils/ft_strjoin.c \
utils/ft_calloc.c \
utils/ft_strlen.c \
utils/ft_atoi.c \
utils/ft_isalpha.c \
utils/ft_putnbr_fd.c \
parsing/utils_env_redirection.c \
parsing/utils_env.c \
parsing/v_env_from_redirection.c \
parsing/env_traitement.c \
builtin/echo.c \
parsing/space_gestion.c \
signal/signal.c \
parsing/syntax_gest_help.c \
parsing/syntax_gestion.c \
builtin/get_cd2.c \
builtin/unset2.c \
pipes/processes_bonus2.c \
pipes/processes_execve_child.c \
pipes/processes_cmd.c \
pipes/errors_parse_utils.c \
builtin/export2.c \
builtin/export3.c \
main_2.c \
utils/is_builtin.c \
parsing/v_env_from_redirection2.c \
parsing/v_env_from_redirection3.c \
parsing/utils_env_redirection2.c \
parsing/space_gestion2.c \
parsing/space_gestion3.c \
parsing/get_option2.c \
parsing/get_option3.c \
parsing/utils_env2.c \
parsing/redirection_in2.c \
parsing/redirection_error2.c \
parsing/udr_redirection_out.c \
parsing/udr_redirection_out2.c \
parsing/udr_get_command.c \
parsing/udr_env_traitement.c \
builtin/echo2.c \
parsing/ft_split_mini2.c \
parsing/ft_split_mini3.c \

OBJS = ${SRCS:.c=.o}
DEPS = ${OBJS:.o=.d}

HEADER = minishell_execution.h

NAME = minishell

CC = clang 

CFLAGS = -Wall -Wextra -Werror -MMD -MP -ggdb3 #-fsanitize=address

RM = rm -f

all: ${NAME}

-include $(DEPS)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline -L .brew/opt/readline/lib -I .brew/opt/readline/include
	@echo "\033[33;32m=== Compilation Minishell \t\t\tOK! √\n\033[0m"

%.o : %.c
	$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} ${DEPS}

re: fclean all

.PHONY: all clean fclean re
