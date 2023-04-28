NAME 	= pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

# NOTE: Add files
# ================================================
SRC 								= pipex \
									  get_next_line_utils \
									  get_next_line \
									  here_doc \
									  pre_processing \
									  utils \
# ================================================

SRC_CUR = $(addsuffix .c, $(SRC))
LIBFT		= libft
OBJ = $(SRC_CUR:.c=.o)
HEAD 	= pipex.h

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
TOTAL_FILES = $(words $(SRC_CUR))
CURRENT_FILE = 1

all : $(NAME)

$(NAME) : $(OBJ) $(HEAD)
	@make -C $(LIBFT)
	@mv libft/libft.a ./
	@$(CC) $(CFLAGS) -I $(HEAD) libft.a $(OBJ) -o $(NAME)
	@printf "$(LF)"

ifdef BONUS
	@echo "$(Green)===============================================$(DEF_COLOR)"
	@echo "$(Green)|     🎉  pipex bonus compile succsess.  🎉   |$(DEF_COLOR)"
	@echo "$(Green)===============================================$(DEF_COLOR)"
else
	@echo "$(Green)===============================================$(DEF_COLOR)"
	@echo "$(Green)|  🥳  pipex mandatory compile succsess. 🥳   |$(DEF_COLOR)"
	@echo "$(Green)===============================================$(DEF_COLOR)"
endif


.c.o : 
	@$(CC) $(CFLAGS) -I $(HEAD) -c -o $@ $<
	@printf "$(LF)$(Cyan)[$(CURRENT_FILE)/$(TOTAL_FILES)]$(DEF_COLOR) [$(Yellow)%0.1f%%$(DEF_COLOR)] $(Green)🔰Compiling... $(Red)$(NAME) $(DEF_COLOR)\b" $(shell echo "scale=1; ($(CURRENT_FILE) / $(TOTAL_FILES)) * 100" | bc)
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@sleep 0.5


clean :
	@rm -rf *.o all bonus libft.a
	@printf "$(LF)🚧 $(Yellow)Cleaning...🚨 $(Purple)libft$(White) $(OBJ) \n$(DEF_COLOR) "
	@make clean -C $(LIBFT)

fclean : clean
	@printf "$(LF)🚧 $(Red)Cleaning...🚨 $(White)$(NAME) \n"
	@rm -rf $(NAME)

re :
	@$(MAKE) fclean
	@sleep 0.5
	@clear
	@printf "$(Purple)>>REBUILD<<\n"
	@$(MAKE) all

bonus :
	@make $(NAME)

.PHONY : all re clean fclean bonus


