CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

# NOTE: Add files
# ================================================
SRC_MAN 								= push_swap \
									  check_init_data \
									  command_a \
									  command_b \
									  command_ab \
									  list_command \
									  ft_split \
									  merge_sort \
									  num_utils \
									  set \
									  solve \
									  sort \
									  sort_tools \
									  tools \
									  utils \

SRC_BO 								= chacker \
									  merge_sort \
									  command_a \
									  command_b \
									  command_ab \
									  list_command \
									  ft_split \
									  num_utils \
									  set \
									  check_init_data \
									  utils \
									  get_next_line \
									  get_next_line_utils \
# ================================================

SRC_CUR = $(addsuffix .c, $(SRC))

OBJ = $(SRC_CUR:.c=.o)
OBJ_BO = $(SRC_CUR:.c=.o)

NAME_MAN 	= push_swap
NAME_BO 	= checker
HEAD = push_swap.h

ifdef BONUS
		SRC = $(SRC_BO)
else
		SRC = $(SRC_MAN)
endif

ifdef BONUS
		OBJ_CUR = $(OBJ_BO)
else
		OBJ_CUR = $(OBJ)
endif

ifdef BONUS
	NAME = $(NAME_BO)
else
	NAME = $(NAME_MAN)
endif

Black	=\033[0;30m
Red		=\033[1;31m
Green	=\033[0;32m
Yellow	=\033[0;33m
Blue	=\033[0;34m
Purple	=\033[0;35m
Gray    = \033[0;90m
Cyan	=\033[0;36m
White	=\033[1;37m
DEF_COLOR = \033[0;39m

TOTAL_FILES = $(words $(SRC))
CURRENT_FILE = 1

progress_bar = printf "$(LF)$(Red)[ ♔Compiling...♔ ]$(DEF_COLOR) $(Cyan)[$(1)/$(2)]$(DEF_COLOR) [$(Yellow)%0.1f%%$(DEF_COLOR)] $(DEF_COLOR)\b" $(shell echo "scale=1; ($(1) / $(2)) * 100" | bc); \
		printf " $(White)[%-*s%s]$(DEF_COLOR)" 25 "$(shell printf '%0.*s' $$(($(1) * 25 / $(2))) '=========================================================================')>" ""; \
		printf "\n\033[2K$(DEF_COLOR)  ✔︎ $(Cyan)Compiling... $< $(DEF_COLOR) \033[A\033[999C\e[?25l" \

all : $(NAME)

LF = \e[1K\r

$(NAME) : $(OBJ_CUR) $(HEAD)
	@$(CC) $(CFLAGS) -I $(HEAD) $(OBJ_CUR) -o $(NAME)
	@printf "\n\033[1;32m✅ Compilation complete. $(NAME) has been created. ✅\033[0m\n\n\e[?25h"

ifdef BONUS
	@echo "$(Green)===============================================$(DEF_COLOR)"
	@echo "$(Green)|  🎉   Push_Swap bonus compile succsess.  🎉  |$(DEF_COLOR)"
	@echo "$(Green)===============================================$(DEF_COLOR)"
else
	@echo "$(Green)===============================================$(DEF_COLOR)"
	@echo "$(Green)|  🥳 Push_Swap mandatory compile succsess. 🥳 |$(DEF_COLOR)"
	@echo "$(Green)===============================================$(DEF_COLOR)"
endif

.c.o :
	@$(CC) $(CFLAGS) -I $(HEAD) -c -o $@ $<
	@$(call progress_bar,$(CURRENT_FILE),$(TOTAL_FILES))
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@sleep 0.05

clean :
	@rm -rf *.o all bonus
	@printf "$(LF)🚧 $(Yellow)Cleaning...🚨 $(Purple)libft$(White) $(OBJ) $(DEF_COLOR)\n"

fclean : clean
	@rm -rf $(NAME) $(NAME_BO)
	@echo "\n🚧 $(Red)Cleaning...🚨 $(White)$(NAME)\n"
	@echo "$(Cyan)Clearing terminal in [3seconds]...$(DEFAULT_COLOR)"
	@sleep 1
	@clear

re :
	@$(MAKE) fclean
	@sleep 0.5
	@clear
	@printf "$(Purple)♻️ REBUILD ♻️\n\n"
	@$(MAKE) all

bonus :
	@make BONUS=1 $(NAME_BO)

.PHONY : all re clean fclean bonus


