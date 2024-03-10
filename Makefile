# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 13:00:22 by lboiteux          #+#    #+#              #
#    Updated: 2024/03/10 22:02:07 by lboiteux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# 								NAME PROJECT								   #
# **************************************************************************** #

NAME	=	minishell

# **************************************************************************** #
# 								  COMMANDS									   #
# **************************************************************************** #

CC					=	@cc
CFLAGS				=	-Wall -Wextra -Werror -g
MK					=	@mkdir -p
CPT_MINISHELL		=	$(shell ls -lR srcs | grep -F .c | wc -l)
FILE_MINISHELL		=	$(shell echo "$(CPT_MINISHELL)" | bc)
PROJ_CMP_MINISHELL	=	1
RM					= 	@rm -rf

LIBFT_NAME			= 	./libft/libft.a
LIBFT_PATH			=	./libft --no-print-directory

# **************************************************************************** #
#                                   COLORS                                     #
# **************************************************************************** #

# **************************************************************************** #
#                                   PRINTS                                     #
# **************************************************************************** #

# **************************************************************************** #
# 								   SOURCES									   #
# **************************************************************************** #

#SOURCES
SRCS	= 	srcs/main.c \
			srcs/path.c \
			srcs/error.c \
			srcs/get_input.c \
			srcs/builtins/cd.c \
			srcs/builtins/pwd.c \
			srcs/builtins/env.c \
			srcs/parsing/parse.c \
			srcs/builtins/echo.c \
			srcs/parsing/quote.c \
			srcs/builtins/exec.c \
			srcs/builtins/unset.c \
			srcs/parsing/getenv.c \
			srcs/parsing/parse_utils.c \
			srcs/parsing/getenv_utils.c \
# OBJECTS

OBJS_DIR	:=	.objs
OBJS		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

all: $(NAME)
$(OBJS_DIR)/%.o: %.c
	$(MK) $(@D)
	$(CC) $(CFLAGS) -c $< -o  $@
	@if [ "$(PROJ_CMP_MINISHELL)" -ne "$(FILE_MINISHELL)" ]; then \
		printf " \033[1;38;5;28m [\033[0m$(PROJ_CMP_MINISHELL)\033[1;38;5;28m/\033[0m$(FILE_MINISHELL)\033[1;38;5;28m]\t\033[0m$(GREEN)$<$(BLUE)$(RESET)                        \r"; \
	else \
		printf " \033[1;38;5;28m [\033[0m$(PROJ_CMP_MINISHELL)\033[1;38;5;28m/\033[0m$(FILE_MINISHELL)\033[1;38;5;28m]\t\033[0m$(GREEN)$<$(BLUE)$(RESET)\n\n"; \
	fi
	@$(eval PROJ_CMP_MINISHELL=$(shell echo $$(($(PROJ_CMP_MINISHELL)+1))))

$(NAME) : $(LIBFT_NAME) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT_NAME) -lreadline -o $(NAME)
		@printf "  ✅ \033[1;38;5;120mMinishell successfully compiled\033[0m\n"
		@printf "  🔄 \033[1;38;5;240mMinishell is ready to run\033[0m \n"

$(LIBFT_NAME):
		@printf "  📖 \033[1;38;5;240mCompiling libft\033[0m 📖\n"
		@make -C $(LIBFT_PATH) -j
		@printf "  ✅ \033[1;38;5;120mLibft successfully compiled\033[0m\n\n"
		@printf "  🖥️  \033[1;38;5;240mCompiling minishell\033[0m 🖥️\n"

clean:
		@printf "  👾 \033[1;4;38;5;240m$(NAME)\033[0m   \n  \033[1;38;5;240m└──> 🗑️    \033[1;38;5;255m.o \033[1;38;5;248mhave been deleted$(RESET)\n"
		@make clean -C $(LIBFT_PATH)
		$(RM) $(OBJS_DIR)

fclean: clean
		@make fclean -C $(LIBFT_PATH)
		@printf "  \033[1;38;5;240m└──> 🗑️    \033[1;38;5;255mlibft binary \033[1;38;5;248mhas been deleted$(RESET)\n"
		$(RM) $(NAME)
		@printf "  \033[1;38;5;240m└──> 🗑️    \033[1;38;5;255mminishell binary \033[1;38;5;248mhas been deleted$(RESET)\n\n"
clear:
	@clear

re:	clear fclean all

.PHONY:	re fclean all clean
