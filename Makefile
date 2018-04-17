# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zweng <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 18:11:43 by zweng             #+#    #+#              #
#    Updated: 2018/04/17 19:07:40 by zweng            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

# ----- part to change -----
NAME = tiny_server
NAME1 = client

LIB_PATH = libft

LIB = $(LIB_PATH)/libft.a

HEADER_PATH = .

HEADER = tiny_server.h 

SRC_PATH = .

SRC_NAME = main.c open_listenfd.c 
SRC_NAME1 = client.c open_clientfd.c 

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_NAME1 = $(SRC_NAME1:.c=.o)

CPPFLAGS = -I$(HEADER_PATH) -I$(LIB_PATH)/includes

LDFLAGS = -L$(LIB_PATH)

LDLIBS = -lft

CFLAGS =  -Wall -Wextra -Werror

# ----- part automatic -----
SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

SRCS1 = $(addprefix $(SRC_PATH)/,$(SRC_NAME1))
OBJS1 = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME1))
# ----- Colors -----
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
CYAN:="\033[1;35m"
PURPLE:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"
#  # ==================

# ----- part rules -----
all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(OBJS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o $@
	@printf $(GREEN)"$(NAME) Finish linking\n"$(EOC)

$(NAME1): $(LIB) $(OBJS1)
	@$(CC) $(OBJS1) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o $@
	@printf $(GREEN)"$(NAME1) Finish linking\n"$(EOC)

$(LIB):
	@make -C $(LIB_PATH) fclean && make -C $(LIB_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER) | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null

clean:
	@rm -f $(OBJS)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@printf $(GREEN)"$(NAME) clean\n"$(EOC)
	@make -C $(LIB_PATH) clean

fclean: clean
	@/bin/rm -f $(NAME)
	@printf $(GREEN)"$(NAME) fclean\n"$(EOC)
	@/bin/rm -f $(LIB)
	@printf $(GREEN)"$(LIB) fclean\n"$(EOC)

re: fclean all

norme:
	@norminette $(SRC_NAME)
	@norminette $(HEADER_PATH)/*.h

.PHONY: clean fclean all
