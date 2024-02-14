# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 13:00:22 by lboiteux          #+#    #+#              #
#    Updated: 2024/02/14 00:51:13 by lboiteux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# 								NAME PROJECT								   #
# **************************************************************************** #

NAME	=	minishell

# **************************************************************************** #
# 								  COMMANDS									   #
# **************************************************************************** #

CC					=	@clang
CFLAGS				=	-Wall -Wextra -Werror
MK					=	@mkdir -p
CPT_MINISHELL		=	$(shell ls -l | grep -F .c | wc -l)
FILE_MINISHELL		=	$(shell echo "$(CPT_MINISHELL)" | bc)
PROJ_CMP_MINISHELL	=	1
RM					= 	@rm -rf

LIBFT_NAME			= 	./libft/libft.a
LIBFT_PATH			=	./libft --no-print-directory

# **************************************************************************** #
#                                   COLORS                                     #
# **************************************************************************** #
GREEN	=	\033[38;5;76m
RED		=	\033[38;5;160m
YELLOW	=	\033[38;5;226m
ORANGE	=	\033[38;5;202m
PURPLE	=	\033[38;5;213m
LBLUE	=	\033[38;5;51m
BLUE	=	\033[38;5;117m
INDI	=	\033[38;5;99m
LIME 	=	\033[38;5;47m
RESET	=	\033[00m
ANIMATED=	\033[93;1;5m

# **************************************************************************** #
#                                   PRINTS                                     #
# **************************************************************************** #
PRINT_1  =   @printf "\n\n			$(RED)mishell is ready to run !$(RESET)  \n\n"
PRINT_2  =	 @printf "\n\n		   	  (PURPLE)bonus are ready to run !$(RESET)  \n\n"
PRINT_3	 =   @printf "\n\n			   $(INDI)minishell is cleaned !$(RESET)  \n\n"
PRINT_4  =   @printf "$(LBLUE)[$(RESET)$(PROJ_CMP_MINISHELL)$(LBLUE)] $(RESET)Compilation in progress... $(GREEN)$<$(BLUE) [$(RESET)$(PROJ_CMP_MINISHELL)$(BLUE)/$(RESET)$(FILE_MINISHELL)$(BLUE)]$(RESET)                        \r"

# **************************************************************************** #
# 								   SOURCES									   #
# **************************************************************************** #

#SOURCES
SRCS	= 	main.c \
				maincopy.c

# OBJECTS

OBJS_DIR	:=	.objs
OBJS		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))


all: $(NAME)
$(OBJS_DIR)/%.o: %.c
	$(MK) $(@D)
	$(CC) $(CFLAGS) -c $< -o  $@
	$(PRINT_4)
	@$(eval PROJ_CMP_MINISHELL=$(shell echo $$(($(PROJ_CMP_MINISHELL)+1))))

$(NAME): $(LIBFT_NAME) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_NAME) -o $(NAME) 
	$(PRINT_1)

$(LIBFT_NAME):
		@make -C $(LIBFT_PATH)

clean:
		@make clean -C $(LIBFT_PATH)
		$(RM) $(OBJS_DIR)
		$(PRINT_3)

fclean: clean
		@make fclean -C $(LIBFT_PATH)
		$(RM) $(NAME)

re:	fclean all

.PHONY:	re fclean all clean