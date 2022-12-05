# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 14:02:01 by jmatheis          #+#    #+#              #
#    Updated: 2022/12/05 21:26:45 by jmatheis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := philo

CC          := cc
CFLAGS      := -Wall -Wextra -Werror

SRCS        := main.c \
				utils.c \
				action.c \
				init.c
OBJS        := $(SRCS:%.c=%.o)

# **************************************************************************** #
#   RULES                                                                      #
# **************************************************************************** #

.PHONY: all clean fclean re

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c %.d
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS) 

fclean: clean
	$(RM) $(NAME)

re: fclean all
