CC = cc
CFLAGS = -Werror
NAME = push_swap
HEAD = test.h
SRCS = test.c

OBJ = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) -I $(HEAD) $(CFLAGS) -o $@ $^

.c.o :
	$(CC) -I $(HEAD) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all re clean fclean
