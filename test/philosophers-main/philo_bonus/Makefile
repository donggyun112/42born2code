# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seongmpa <seongmpa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 11:58:49 by seongmpa          #+#    #+#              #
#    Updated: 2023/04/02 12:03:56 by seongmpa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
LIB = libphilo_bonus.a
LIBNAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = -rcs
RM = rm
RMFLAGS = -f

SRCS = ./src/action_bonus.c			\
		./src/init_bonus.c			\
		./src/philo_bonus.c			\
		./src/philo_utils_bonus.c		\
		./src/philo_utils2_bonus.c	\
		./src/make_str_bonus.c		\
		./src/ft_split_bonus.c

INC = ./includes
OBJS = $(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^ -I $(INC)

$(LIB) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(NAME) : $(LIB)
	$(CC) $(CFLAGS) -l$(LIBNAME) -L. -o $@

clean:
	$(RM) $(RMFLAGS) $(OBJS)

fclean: clean
	$(RM) $(RMFLAGS) $(LIB) $(NAME)

re: fclean all

.PHONY: all clean fclean re
