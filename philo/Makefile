# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmatheis <jmatheis@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 14:02:01 by jmatheis          #+#    #+#              #
#    Updated: 2022/11/29 10:44:24 by jmatheis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := philo

CC          := cc
CFLAGS      := -Wall -Wextra -Werror

SRCS        := main.c \
				utils.c
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
