# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaudot <abaudot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/15 00:28:20 by abaudot           #+#    #+#              #
#    Updated: 2021/07/25 13:39:10 by abaudot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_B = client_bonus
NAME_SERVER_B = server_bonus


OBJS_DIR = obj

PRECOMPILE = mkdir -p $(dir $(OBJS_DIR)/$*)

SRC_CLIENT = src/client.c\
			 src/strlib.c

SRC_CLIENT_BONUS =	src/client_bonus.c\
			 		src/strlib.c

OBJ_C = $(patsubst src/%.c, $(OBJS_DIR)/%.o, $(SRC_CLIENT))
OBJ_CB = $(patsubst src/%.c, $(OBJS_DIR)/%.o, $(SRC_CLIENT_BONUS))

SRC_SERVER = src/server.c
SRC_SERVER_BONUS = src/server_bonus.c

OBJ_S = $(patsubst src/%.c, $(OBJS_DIR)/%.o, $(SRC_SERVER))
OBJ_SB = $(patsubst src/%.c, $(OBJS_DIR)/%.o, $(SRC_SERVER_BONUS))

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

bonus : $(NAME_CLIENT_B) $(NAME_SERVER_B)

$(NAME_SERVER_B): $(OBJ_SB)
	@$(CC) -o server $^ $(CFLAGS)
	@echo $(GREEN)"*** server is ready ! ***\n"$(EOC)
$(NAME_CLIENT_B): $(OBJ_CB)
	@$(CC) -o client $^ $(CFLAGS)
	@echo $(GREEN)"*** server is ready ! ***\n"$(EOC)

re: fclean
	@make all

.PHONY: all clean fclean re
