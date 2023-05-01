# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seongmpa <seongmpa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 15:58:55 by seongmpa          #+#    #+#              #
#    Updated: 2023/05/01 23:22:12 by dongkseo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
LIB = libphilo.a
LIBNAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3
AR = ar
ARFLAGS = -rcs
RM = rm
RMFLAGS = -f
SRCS = ./src/philo.c		\
		./src/action.c		\
		./src/init.c		\
		./src/utils.c		\
		./src/make_str.c	\
		./src/ft_split.c
INC = ./includes
OBJS = $(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^ -I $(INC)

$(LIB) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(NAME) : $(LIB)
	$(CC) $(CFLAGS) -l$(LIBNAME) -L. -o $@

bonus:
	make WITH_BONUS=1 all

clean:
	$(RM) $(RMFLAGS) $(OBJS)

fclean: clean
	$(RM) $(RMFLAGS) $(LIB) $(NAME) 

re: fclean all

.PHONY: all clean fclean re
