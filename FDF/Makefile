NAME 	= test
CC = cc
CFLAGS = -Wall -fsanitize=address -g

# NOTE: Add files
# ================================================
SRC 								= test \
									  get_next_line \
									  get_next_line_utils
# ================================================

SRC_CUR = $(addsuffix .c, $(SRC))
LIBFT		= libft
OBJ = $(SRC_CUR:.c=.o)
HEAD 	= get_next_line.h
HEAD_2 	= test.h

Black	=\033[0;30m
Red		=\033[0;31m
Green	=\033[0;32m
Yellow	=\033[0;33m
Blue	=\033[0;34m
Purple	=\033[0;35m
Cyan	=\033[0;36m
White	=\033[0;37m
DEF_COLOR = \033[0;39m
LF = \e[1K\r
# 	@install_name_tool -change libmlx.dylib ./mlx_mms/libmlx.dylib $(NAME)
all : $(NAME)

$(NAME) : $(OBJ) $(HEAD) $(HEAD_2)
	@make -C $(LIBFT)
	@make -C mlx_mms
	@mv libft/libft.a ./
	@cp mlx_mms/libmlx.dylib ./
	@$(CC) $(CFLAGS) -I $(HEAD) -I $(HEAD_2) libft.a -Lmlx_mms -lmlx -framework OpenGL -framework AppKit $(OBJ) -O3 -o $(NAME)
	@printf "$(LF)"

ifdef BONUS
	@echo "$(Green)===============================================$(DEF_COLOR)"
	@echo "$(Green)|     🎉  FDF bonus compile succsess.  🎉    |$(DEF_COLOR)"
	@echo "$(Green)===============================================$(DEF_COLOR)"
else
	@echo "$(Green)===============================================$(DEF_COLOR)"
	@echo "$(Green)|  🥳  FDF mandatory compile succsess. 🥳    |$(DEF_COLOR)"
	@echo "$(Green)===============================================$(DEF_COLOR)"
endif

.c.o : 
	@$(CC) $(CFLAGS) -I $(HEAD) -I $(HEAD_2) -Imlx_mms -c -o $@ $<
	@printf "$(LF)$(Green)🔰Compiling... \t$(White)$< $(DEF_COLOR)✅\b"
	@sleep 0.08


clean :
	@rm -rf *.o all bonus libft.a
	@printf "$(LF)🚧 $(Yellow)Cleaning...🚨 $(Purple)libft$(White) $(OBJ) \n$(DEF_COLOR)"
	@make clean -C $(LIBFT)

fclean : clean
	@printf "$(LF)🚧 $(Red)Cleaning...🚨 $(White)$(NAME) \n"
	@rm -rf $(NAME) libmlx.dylib

re :
	@$(MAKE) fclean
	@sleep 0.5
	@clear
	@printf "$(Purple)>>REBUILD<<\n"
	@$(MAKE) all

bonus :
	@make $(NAME)

.PHONY : all re clean fclean bonus


