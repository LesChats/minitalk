# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/15 00:28:20 by abaudot           #+#    #+#              #
#    Updated: 2021/07/16 18:51:33 by aime             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server
OBJS_DIR = obj

PRECOMPILE = mkdir -p $(dir $(OBJS_DIR)/$*)

SRC_CLIENT = src/client.c\
			 src/strlib.c
OBJ_C = $(patsubst src/%.c, $(OBJS_DIR)/%.o, $(SRC_CLIENT))

SRC_SERVER = src/server.c
OBJ_S = $(patsubst src/%.c, $(OBJS_DIR)/%.o, $(SRC_SERVER))

INC = -I includes

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# ----- Colors -----
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
CYAN:="\033[1;35m"
PURPLE:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"
BLUE:="\033[34;1m"
# ==================

# ------ Debugger ----
ifeq ($(DEBUG), 1)
	CFLAGS	+=	-g
endif
# ====================

# ----- Fsanitize -----
ifeq ($(SANITIZE), 1)
	CFLAGS	+=	-fsanitize=leak -g
endif
# ==========================


all: $(NAME_SERVER) $(NAME_CLIENT)

$(OBJS_DIR)/%.o: src/%.c
	@$(PRECOMPILE)
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@echo $(BLUE) "Created:" $(@:%=%) $(EOC)

$(NAME_SERVER): $(OBJ_S)
	@$(CC) -o $@ $^ $(CFLAGS)
	@echo $(GREEN)"*** server is ready ! ***\n"$(EOC)

$(NAME_CLIENT): $(OBJ_C)
	@$(CC) -o $@ $^ $(CFLAGS)
	@echo $(GREEN)"*** client is ready ! ***\n"$(EOC)

clean:
	@rm -rf $(OBJS_DIR)
fclean: clean
	@rm -f $(NAME_SERVER)
	@echo $(RED)"server removed"$(EOC)
	@rm -f $(NAME_CLIENT)
	@echo $(RED)"client removed"$(EOC)

bonus : all

re: fclean
	@make all

.PHONY: all clean fclean re
