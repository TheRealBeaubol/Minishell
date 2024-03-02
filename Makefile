# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 13:00:22 by lboiteux          #+#    #+#              #
#    Updated: 2024/03/02 01:43:25 by mhervoch         ###   ########.fr        #
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
PINK1	=	\033[0;38;5;176m
PINK2   =   \033[0;38;5;177m
PINK3   =   \033[0;38;5;178m
PINK4   =   \033[0;38;5;179m
PINK5   =   \033[0;38;5;180m
PINK6   =   \033[0;38;5;181m
PINK7   =   \033[0;38;5;182m
PINK8   =   \033[0;38;5;183m
PINK9   =   \033[0;38;5;184m
PINK10  =   \033[0;38;5;185m
GRAY	=	\033[0;38;5;188m

# **************************************************************************** #
#                                   PRINTS                                     #
# **************************************************************************** #

PRINT_1  =   @printf "\n\n $(PINK1)⠀   ⠀⠀⠄⠠⠤⠤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠠⢀⣢⣈⣉⠁⡆⠀⠀⠀⠀⠀⠀\n\
⠀   ⠀⠀⡏⢠⣾⢷⢶⣄⣕⠢⢄⠀⠀⣀⣠⠤⠔⠒⠒⠒⠒⠒⠒⠢⠤⠄⣀⠤⢊⣤⣶⣿⡿⣿⢹⢀⡇⠀⠀⠀⠀⠀⠀\n\
⠀   ⠀⠀⢻⠈⣿⢫⡞⠛⡟⣷⣦⡝⠋⠉$(LBLUE)⣤⣤⣶⣶⣶⣿⣿⣿⡗⢲⣴$(PINK1)⠀⠈⠑⣿⡟⡏⠀⢱⣮⡏⢨⠃⠀⠀⠀⠀⠀⠀\n\
⠀⠀   ⠀⠸⡅⣹⣿⠀⠀⢩⡽⠋$(LBLUE)⣠⣤⣿⣿⣏⣛⡻⠿⣿⢟⣹⣴⢿⣹⣿⡟⢦⣀$(PINK1)⠙⢷⣤⣼⣾⢁⡾⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀   ⠀⠀⢻⡀⢳⣟⣶⠯$(LBLUE)⢀⡾⢍⠻⣿⣿⣽⣿⣽⡻⣧⣟⢾⣹⡯⢷⡿⠁⠀⢻⣦$(PINK1)⡈⢿⡟⠁⡼⠁⠀⠀⠀⠀⠀⠀⠀\n\
⠀   ⠀⠀⠀⠀⢷⠠⢻⠏$(LBLUE)⢰⣯⡞⡌⣵⠣⠘⡉⢈⠓⡿⠳⣯⠋⠁⠀⠀⢳⡀⣰⣿⣿⣷$(PINK1)⡈⢣⡾⠁⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀   ⠀⠀⠀⠀⠙⣎⠀$(LBLUE)⣿⣿⣷⣾⣷⣼⣵⣆⠂⡐⢀⣴⣌⠀⣀⣤⣾⣿⣿⣿⣿⣿⣿⣷⣀$(PINK1)⠣⠀⠀ ⠀⠀⠀⠀⠀⠀\n\
⠀   ⠀⠀⠀⠀⠀⠄⠑$(LBLUE)⢺⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣳⣿⢽⣧$(PINK1)⡤⢤⠀⠀ ⠀⠀⠀⠀⠀⠀\n\
⠀   ⠀⠀⠀⠀⠀⢸⣈$(LBLUE)⢹⣟⣿⣿⣿⣿⣿⣻⢹⣿⣻⢿⣿⢿⣽⣳⣯⣿⢷⣿⡷⣟⣯⣻⣽$(PINK1)⠧⠾⢤⠀ ⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀   ⠀⠀⠀⢇⠤$(LBLUE)⢾⣟⡾⣽⣿⣽⣻⡗⢹⡿⢿⣻⠸⢿⢯⡟⡿⡽⣻⣯⣿⣎⢷⣣⡿$(PINK1)⢾⢕⣎⠀ ⠀⠀⠀⠀⠀⠀\n\
⠀⠀   ⠀⠀⡠⡞⡟$(LBLUE)⣻⣮⣍⡛⢿⣽⣻⡀⠁⣟⣣⠿⡠⣿⢏⡞⠧⠽⢵⣳⣿⣺⣿⢿⡋$(PINK1)⠙⡀⠇⠱⡓   ⠀⠀⠀\n\
⠀⠀⠀   ⠀⢰⠠⠁⠀⢻$(LBLUE)⡿⣛⣽⣿⢟$(RESET)⡁⣭⣥⣅$(PINK1)⠀⠀⠀⠀⠀⠀$(RESET)⣶⣟⣧$(LBLUE)⠿⢿⣿⣯⣿⣿⣿$(PINK1)⡇⠀⢀⡇⠀⠀⠀⠀⠀⠀\n\
⠀⠀   ⠀⠀⢸⠀⠀⡇⢹$(LBLUE)⣾⣿⣿⣷⡿$(RESET)⢿$(RED)⢷$(RESET)⡏⡈⠀⠀⠀⠀⠀⠀$(RESET)⠈⡹$(RED)⡷$(RESET)⡎$(LBLUE)⢸⣿⣿⣿⣿⣿$(PINK1)⡇⠀⠸⡇⠀⠀⠀⠀⠀⠀\n\
⠀   ⠀⠀⠀⢸⡄⠂⠖⢸$(LBLUE)⣿⣿⣿⡏⢃$(RESET)⠘⡊⠩⠁⠀$(PINK1)⠀⠀⠀⠀⠀$(RESET)⠀⠁⠀⠁$(LBLUE)⢹⣿⣿⣿⣿$(PINK1)⢰⢁⡌⢀⠇⠀⠀⠀⠀⠀⠀\n\
⠀   ⠀⠀⠀⠀⢷⡘⠜$(LBLUE)⣤⣿⣿⣿⣷⡅⠐⠀⠀⠀⠀ ⠀   ⠀⠀⠀⠀⠀⢸⣿⣿⣧⣕⣼⣠⡵⠋⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀   ⠀⠀⠀⣸⣻⣿⣾⣿⣿⣿⣿⣾⡄⠀⠀⠀⠀⠀$(PINK1)⢀⣀⠀⠀⠀⠀⠀$(LBLUE)⣠⣿⣿⣿⣿⣿⣿⣿⢀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀   ⠀⠀⠀⡇⣿⣻⣿⣿⣿⣿⣿⣿⣿⣦⣤⣀⠀⠀⠀⠀⠀⠀⣠⣴⣾⣿⣿⣿⣿⣿⣿⣳⣿⡸⡀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀   ⠀⠀⣸⢡⣿⢿⣿⣿⣿⣿⣿⣿⣿⢿⣿$(RESET)⡟⣽⠉⠀⠒⠂⠉⣯⢹$(LBLUE)⣿⡿⣿⣿⣿⣿⣿⣯⣿⡇⠇⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀   ⠀⢰⡏⣼⡿⣿⣻⣿⣿⣿⣿⣿⢿⣻$(RESET)⡿⠁⠘⡆⠀⠀⠀⢠⠇⠘⣿$(LBLUE)⣿⣽⣿⣿⣿⣿⣯⣿⣷⣸⠀⠀⠀⠀⠀⠀⠀\n\
⠀   ⠀⢀⡟⢰⣾⢿⣿⣟⣿⣿⣿⣿⣿⡟$(RESET)⣿⣧⠀⠀⠈⠣⡄⡰⠋⠀⢀⢾⣿$(LBLUE)⡛⣿⣿⣿⣿⣿⣿⣿⣷⡆⠀⠀⠀⠀⠀⠀\n\
⠀   ⠀⢸⢁⢦⣿⣻⣿⢿⣻⡽⣾⢿⡿$(RESET)⢷⣽⣻⠃⠂⠴⣎⠘⠦⡸⠠⠄⢻⣟⣿$(LBLUE)⠻⣿⣻⢷⣯⢿⣿⣽⣷⡀⠀⠀⠀⠀⠀\n\
⠀   ⠀⡇⠎⣼⡷⣿⣟⣿⣯⢿⣽⣞⡇$(RESET)⣸⣷⡇⠰⠗⠐⣺⣀⣼⠒⠒⠦⠰⣿⣯⠇$(LBLUE)⢳⣯⣿⣞⣿⢾⣿⢿⢳⡄⠀⠀⠀⠀\n\
⠀ ⠀⠀⢸⡿⢠⣿⣻⣿⢿⣼⣿⣿⣿⣼$(RESET)⣄⡻⢼⣧⠀⣀⣼⠟⣻⡟⢧⣤⣄⢠⣿⡃$(LBLUE)⢼⣿⢧⣿⣿⡿⣟⣿⣿⡄⢻⡀⠀⠀⠀\n\
⠀ ⠀⠀⣼⠀⣾⡷⣿⣿⣿⢾⣿⣿⢾⠗$(RESET)⣛⡥⣾⠟⣞⠉⢀⣠⠙⢰⣀⡈⢙⡟⣿⣽⣲⢭$(LBLUE)⢛⣿⣿⣻⣽⣾⣷⣷⡀⠱⡀⠀⠀\n\
⠀ ⠀⢠⢛⣰⣿⣟⣿⣿⣿⣿⣿⢯⣿⣧$(RESET)⢹⣽⣻⢾⣮⣷⣠⠗⢪⠐⢧⣼⣷⣶⣾⢷⣯⠏$(LBLUE)⣼⣿⣻⣯⣿⣿⣿⣯⣷⡄⢣⠀⠀\n\
⠀ ⠀⡌⡆⣿⣿⣿⣿⣽⣿⣿⣿⣿⣿⣿⣦$(RESET)⡹⣿⣟⣾⣳⣿⣧⣼⣴⣝⣛⢾⣷⣯⣿⢊$(LBLUE)⣼⣿⣿⣿⣿⣿⣿⣿⣿⡿⣷⠈⡇⠀\n\
⠀ ⠀⡇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣍$(RESET)⡻⣿⣿⣿⣿⡄⣷⣯⣟⣿⡿⠏$(LBLUE)⣡⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠐⠀\n\n\n\n\n\
		$(PINK10)███    ███ ██ ███████ ██   ██ ███████ ██      ██        \n\
		$(PINK9)████  ████ ██ ██      ██   ██ ██      ██      ██        \n\
		$(PINK8)██ ████ ██ ██ ███████ ███████ █████   ██      ██        \n\
		$(PINK7)██  ██  ██ ██      ██ ██   ██ ██      ██      ██        \n\
		$(PINK6)██      ██ ██ ███████ ██   ██ ███████ ███████ ███████   \n\n\
		$(PINK5)██ ███████     ██████  ███████  █████  ██████  ██    ██ \n\
		$(PINK4)██ ██          ██   ██ ██      ██   ██ ██   ██  ██  ██  \n\
		$(PINK3)██ ███████     ██████  █████   ███████ ██   ██   ████   \n\
		$(PINK2)██      ██     ██   ██ ██      ██   ██ ██   ██    ██    \n\
		$(PINK1)██ ███████     ██   ██ ███████ ██   ██ ██████     ██    \n$(RESET)  \n\n"
PRINT_2	 =   @printf "\n\n			   $(INDI)mishell is cleaned !$(RESET)  \n\n"
PRINT_3  =   @printf "$(LBLUE)[$(RESET)$(PROJ_CMP_MINISHELL)$(LBLUE)] $(RESET)Compilation in progress... $(GREEN)$<$(BLUE) [$(RESET)$(PROJ_CMP_MINISHELL)$(BLUE)/$(RESET)$(FILE_MINISHELL)$(BLUE)]$(RESET)                        \r"

# **************************************************************************** #
# 								   SOURCES									   #
# **************************************************************************** #

#SOURCES
SRCS	= 	srcs/main.c \
				srcs/get_input.c \
				srcs/error.c \
				srcs/builtins/exec.c \
				srcs/builtins/cd.c \
				srcs/builtins/pwd.c \
				srcs/builtins/unset.c \
				srcs/builtins/echo.c \
				srcs/builtins/env.c \
				srcs/path.c \
				srcs/parsing/parse.c \
				srcs/parsing/quote.c \
				srcs/parsing/parse_utils.c \
				srcs/parsing/getenv.c \
				srcs/parsing/getenv_utils.c \
# OBJECTS

OBJS_DIR	:=	.objs
OBJS		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))


all: $(NAME)
$(OBJS_DIR)/%.o: %.c
	$(MK) $(@D)
	$(CC) $(CFLAGS) -c $< -o  $@
	$(PRINT_3)
	@$(eval PROJ_CMP_MINISHELL=$(shell echo $$(($(PROJ_CMP_MINISHELL)+1))))

$(NAME): $(LIBFT_NAME) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_NAME) -lreadline -o $(NAME) 
	@clear
	$(PRINT_1)

$(LIBFT_NAME):
		@make -C $(LIBFT_PATH)

clean:
		@make clean -C $(LIBFT_PATH)
		$(RM) $(OBJS_DIR)
		$(PRINT_2)

fclean: clean
		@make fclean -C $(LIBFT_PATH)
		$(RM) $(NAME)

re:	fclean all

.PHONY:	re fclean all clean
