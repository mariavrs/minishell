# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 18:28:32 by ede-smet          #+#    #+#              #
#    Updated: 2023/04/02 22:49:43 by ede-smet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src
OBJ_DIR = obj
DEPS_DIR = include
BUILT_DIR = builtins/
UTILS_DIR = utils/

SRC_LIST = minishell.c syntax_check.c pipe_list_parse_and_run.c pipe_run_left_right.c \
	parser_utils.c spl_cmd_parse.c ft_get_next_word.c spl_cmd_exec.c \
	spl_cmd_redir.c spl_cmd_local_var.c env_declare_get_full_var.c \
	env_declare_put_var.c param_expansion.c param_expansion_utils.c signal.c \
	spl_cmd_redir_hdoc.c signal_hdoc.c \
	$(BUILT_DIR)ft_echo.c $(BUILT_DIR)ft_cd.c $(BUILT_DIR)ft_pwd.c $(BUILT_DIR)ft_export.c \
	$(BUILT_DIR)ft_unset.c $(BUILT_DIR)env/ft_env.c $(BUILT_DIR)env/env_func.c $(BUILT_DIR)env/env_utils.c $(BUILT_DIR)ft_exit.c \
	$(UTILS_DIR)ft_ll_atoi.c $(UTILS_DIR)ft_free.c $(UTILS_DIR)ft_malloc.c $(UTILS_DIR)mini_error.c $(BUILT_DIR)ft_cd_utils.c
DEPS_LIST = mini_fun.h mini_struct.h

SRC = $(addprefix $(SRC_DIR)/, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_LIST:.c=.o))
DEPS = $(addprefix $(DEPS_DIR)/, $(DEPS_LIST))

LFT = lib/libft

CC = cc -g3
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L$(LFT) -lft -lreadline #-fsanitize=leak

NOCOLOR	= \033[0m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
PURPLE	= \033[1;35m
CYAN	= \033[1;36m

all: lib $(OBJ_DIR) $(NAME)

lib:
	@echo "$(YELLOW)lib compilation$(NOCOLOR)"
	@make --no-print-directory -C $(LFT)

$(OBJ_DIR):
	@echo "$(YELLOW)$(NAME) compilation$(NOCOLOR)"
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(BUILT_DIR) $(OBJ_DIR)/$(BUILT_DIR)/env $(OBJ_DIR)/$(UTILS_DIR)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled$(NOCOLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@$(CC) $(CFLAGS) -I$(LFT) -c -o $@ $<

lib_clean:
	@make --no-print-directory clean -C $(LFT)
	@echo "$(RED)Libft objects deleted$(NOCOLOR)"

clean: lib_clean
	@rm -rf $(OBJ_DIR)
	@rm -f *.out *.gch	
	@rm -f *.o
	@echo "$(RED)$(NAME) objects deleted$(NOCOLOR)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LFT)/libft.a
	@echo "$(RED)Executable deleted$(NOCOLOR)"

re: fclean all

mfclean:
	@rm -rf $(OBJ_DIR)
	@rm -f *.out *.o *.gch
	@echo "$(RED)$(NAME) objects deleted$(NOCOLOR)"
	@rm -f $(NAME)
	@echo "$(RED)Executable deleted$(NOCOLOR)"

mre: mfclean $(OBJ_DIR) $(NAME)

.PHONY: all lib clean fclean re mfclean mre
