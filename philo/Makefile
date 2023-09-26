# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 14:02:01 by jmatheis          #+#    #+#              #
#    Updated: 2023/09/26 02:22:36 by jmatheis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := philo

CC          := cc
CFLAGS      := -Wall -Wextra -Werror #-fsanitize=address -g

SRCS        := main.c \
				parsing_and_init.c \
				utils.c \
				routine.c \
				control_thread.c \
				error_and_free.c

M_SRCS		:= $(addprefix ./sources/, $(SRCS))
OBJS        := $(M_SRCS:%.c=%.o)

# **************************************************************************** #
#   RULES                                                                      #
# **************************************************************************** #

.PHONY: all clean fclean re

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -lpthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS) 

fclean: clean
	$(RM) $(NAME)

re: fclean all
