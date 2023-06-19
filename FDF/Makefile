NAME 	= fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror

# NOTE: Add files
# ================================================
SRC 								= get_next_line \
									  get_next_line_utils \
									  coordinat_correction \
									  main \
									  bresenham \
									  bresenham2 \
									  controle_mouse \
									  controle_keybord \
									  drew \
									  set \
									  utils \
									  mlx_hook \
									  check \
									  find_color\
# ================================================

SRC_CUR = $(addsuffix .c, $(SRC))
LIBFT		= libft
OBJ = $(SRC_CUR:.c=.o)
HEAD 	= get_next_line.h
HEAD_2 	= fdf.h

Black	=\033[0;30m
Red		=\033[1;31m
Green	=\033[0;32m
Yellow	=\033[0;33m
Blue	=\033[0;34m
Purple	=\033[1;35m
Cyan	=\033[0;36m
White	=\033[1;37m
DEF_COLOR = \033[0;39m
Gray    = \033[0;90m
LF = \e[1K\r
TOTAL_FILES = $(words $(SRC))
CURRENT_FILE = 1

progress_bar = printf "$(LF)$(Red)[ ♔Compiling...♔ ]$(DEF_COLOR) $(Cyan)[$(1)/$(2)]$(DEF_COLOR) [$(Yellow)%0.1f%%$(DEF_COLOR)] $(DEF_COLOR)\b" $(shell echo "scale=1; ($(1) / $(2)) * 100" | bc); \
		printf " $(White)[%-*s%s]$(DEF_COLOR)" 25 "$(shell printf '%0.*s' $$(($(1) * 25 / $(2))) '=========================================================================')>" ""; \
		printf "\n\033[2K$(DEF_COLOR)  ✔︎ $(Cyan)Compiling... $< $(DEF_COLOR) \033[A\033[999C\e[?25l" \


all : $(NAME)

$(NAME) : $(OBJ) $(HEAD) $(HEAD_2)
	@make -C $(LIBFT)
	@make -C mlx_mms
	@mv libft/libft.a ./
	@cp mlx_mms/libmlx.dylib ./
	@$(CC) $(CFLAGS) -I $(HEAD) -I $(HEAD_2) libft.a -Lmlx_mms -lmlx -framework OpenGL -framework AppKit $(OBJ) -O3 -o $(NAME)
	@printf "$(LF)"
	@printf "\n\033[1;32m✅ Compilation complete. $(NAME) has been created. ✅\033[0m\n\n\e[?25h"

ifdef BONUS
	@sleep 0.5
	@echo "$(Green)===============================================$(DEF_COLOR)"
	@echo "$(Green)|     🎉  FDF bonus compile succsess.  🎉    |$(DEF_COLOR)"
	@echo "$(Green)===============================================$(DEF_COLOR)"
else
	@sleep 0.5
	@echo "$(Green)===============================================$(DEF_COLOR)"
	@echo "$(Green)|  🥳  FDF mandatory compile succsess. 🥳    |$(DEF_COLOR)"
	@echo "$(Green)===============================================$(DEF_COLOR)"
endif

.c.o :
	@$(CC) $(CFLAGS) -I $(HEAD) -c -o $@ $<
	@$(call progress_bar,$(CURRENT_FILE),$(TOTAL_FILES))
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@sleep 0.05


clean :
	@rm -rf *.o all bonus libft.a
	@make clean -C $(LIBFT)
	@printf "$(LF)🚧 $(Yellow)Cleaning...🚨 $(Purple)libft$(White) $(OBJ) $(DEF_COLOR)\n"

fclean : clean
	@rm -rf $(NAME) libmlx.dylib
	@echo "\n🚧 $(Red)Cleaning...🚨 $(White)$(NAME)\n"
	@echo "$(Cyan)Clearing terminal in [3seconds]...$(DEFAULT_COLOR)"
	@sleep 1
	@clear

re : fclean
	@sleep 0.5
	@clear
	@printf "$(Purple)♻️ REBUILD ♻️\n\n"
	@$(MAKE) all

bonus :
	@make BONUS=1 $(NAME)

.PHONY : all re clean fclean bonus
