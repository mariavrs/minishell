# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ede-smet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 18:28:32 by ede-smet          #+#    #+#              #
#    Updated: 2023/01/18 00:30:47 by ede-smet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src
OBJ_DIR = obj
DEPS_DIR = include

SRC_LIST = minishell.c
DEPS_LIST = header.h

SRC = $(addprefix $(SRC_DIR)/, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_LIST:.c=.o))
DEPS = $(addprefix $(DEPS_DIR)/, $(DEPS_LIST))

LFT = lib/libft

CC = cc -g3
CFLAGS = -Wall -Wextra -Werror -fsanitize=leak
LFLAGS = -L$(LFT) -lft -fsanitize=leak
NOCOLOR    = \033[0m
RED     = \033[1;31m
GREEN     = \033[1;32m
YELLOW    = \033[1;33m
BLUE    = \033[1;34m

all: lib $(OBJ_DIR) $(NAME)

lib:
	@echo "$(YELLOW)lib compilation$(NOCOLOR)"
	@make --no-print-directory -C $(LFT)

$(OBJ_DIR):
	@echo "$(YELLOW)$(NAME) compilation$(NOCOLOR)"
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled$(NOCOLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@$(CC) $(CFLAGS) -I$(LFT) -c -o $@ $<

lib_clean:
	@make --no-print-directory clean -C $(LFT)
	@echo "$(BLUE)Libft objects deleted$(NOCOLOR)"

clean: lib_clean
	@rm -rf $(OBJ_DIR)
	@rm -f .out.gch	
	@rm -f *.o
	@echo "$(BLUE)$(NAME) objects deleted$(NOCOLOR)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LFT)/libft.a
	@echo "$(BLUE)Executable deleted$(NOCOLOR)"

re: fclean all

mfclean:
	@rm -rf $(OBJ_DIR)
	@rm -f .out.gch
	@rm -f *.o
	@echo "$(BLUE)$(NAME) objects deleted$(NOCOLOR)"
	@rm -f $(NAME)
	@echo "$(BLUE)Executable deleted$(NOCOLOR)"

mre: mfclean $(OBJ_DIR) $(NAME)

.PHONY: all lib clean fclean re mfclean mre
