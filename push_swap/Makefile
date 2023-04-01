CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = push_swap
NAME_BO = chacker
HEAD = test.h
HEAD_BO = test.h get_next_line.h
SRCS = push_swap.c
SRC_BO = chacker.c

OBJ = $(SRCS:.c=.o)
OBJ_BO = $(SRC_BO:.c=.o)

ifdef BONUS
		OBJ_CUR = $(OBJ_BO)
		NAME_TRUE = $(NAME_BO)
else
		OBJ_CUR = $(OBJ)
		NAME_TRUE = $(NAME)
endif

all : $(NAME_TRUE)

$(NAME_TRUE) : $(OBJ_CUR)
	$(CC) -I $(HEAD) $(CFLAGS) -o $@ $^

.c.o :
	$(CC) -I $(HEAD) -c $< -o $@

clean :
	rm -rf $(OBJ_CUR) all bonus

fclean : clean
	rm -rf $(NAME_TRUE)

re :
	$(MAKE) fclean
	$(MAKE) all

bonus :
	make BONUS=1 $(NAME_BO)

.PHONY : all re clean fclean bonus
