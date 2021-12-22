# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 20:34:02 by cjang             #+#    #+#              #
#    Updated: 2021/12/18 15:41:49 by cjang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
PTHREAD = -lpthread
NAME = philo

SRCS =	philo.c \
		utils.c \
		time_func.c \
		init_func.c \
		philo_func.c \
		usleep_func.c \
		malloc_func.c \
		print_func.c \
		free_func.c \
		pthread_func.c \
		mutex_func.c \
		eat_algorithm.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(PTHREAD)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
