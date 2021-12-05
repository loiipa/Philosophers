# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjang <cjang@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 20:34:02 by cjang             #+#    #+#              #
#    Updated: 2021/12/05 17:04:02 by cjang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS =
PTHREAD = -lpthread
NAME = philo

all: $(NAME)
SRCS = philo.c utils.c time_func.c init_func.c philo_func.c monitor_func.c
OBJS = $(SRCS:.c=.o)

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
