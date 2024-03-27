# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 09:36:52 by lboiteux          #+#    #+#              #
#    Updated: 2024/03/24 17:38:30 by lboiteux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# 								NAME PROJECT								   #
# **************************************************************************** #
NAME	=	libft.a

# **************************************************************************** #
# 								  COMMANDS									   #
# **************************************************************************** #
CC		=	@cc
CFLAGS	=	-Wall -Wextra -Werror -g
IFLAGS	=	-I ./includes
MK		=	@mkdir -p
RM		=	@rm -rf
FILE	=	$(shell ls -lR srcs/ | grep -F .c | wc -l)
PROJ_CMP	=	1
RM		= 	@rm -rf
CLEAR	=	@clear

# **************************************************************************** #
# 								   COLORS									   #
# **************************************************************************** #
COLOR_1	= \033[1;38;5;28m
COLOR_2	= \033[1;38;5;120m
COLOR_3	= \033[1;38;5;240m
COLOR_4	= \033[1;38;5;255m
COLOR_5	= \033[1;38;5;248m
RESET	= \033[0m

# **************************************************************************** #
# 								   SOURCES									   #
# **************************************************************************** #
# SOURCES
SRCS		:=	char/ft_isalnum.c\
							char/ft_isalpha.c\
							char/ft_isascii.c\
							char/ft_toupper.c\
							char/ft_tolower.c\
							char/ft_isdigit.c\
							char/ft_ishexa.c\
							char/ft_isprint.c\
							char/ft_iswhitespace.c\
							malloc/ft_memcpy.c\
							malloc/ft_memmove.c\
							malloc/ft_memset.c\
							malloc/ft_memchr.c\
							malloc/ft_memcmp.c\
							malloc/ft_calloc.c\
							malloc/ft_bzero.c\
							malloc/ft_strdup.c\
							malloc/ft_free_tab.c\
							malloc/ft_free_list.c\
							malloc/ft_free_int_tab.c\
							malloc/ft_realloc.c\
							malloc/ft_strdup_range.c\
							str/ft_str_lower.c\
							str/ft_substr.c\
							str/ft_strjoin.c\
							str/ft_strnstr.c\
							str/ft_strncmp.c\
							str/ft_strrev.c\
							str/ft_str_start_del.c\
							str/ft_strchr.c\
							str/ft_strrchr.c\
							str/ft_strlen.c\
							str/ft_strlcpy.c\
							str/ft_strlcat.c\
							str/ft_strtrim.c\
							str/ft_str_split.c\
							str/ft_char_split.c\
							str/ft_strmapi.c\
							str/ft_striteri.c\
							str/ft_str_is_alpha.c\
							str/ft_strcpy.c\
							str/ft_strncpy.c\
							str/ft_str_is_numeric.c\
							str/ft_str_is_lowercase.c\
							str/ft_str_is_uppercase.c\
							str/ft_str_is_printable.c\
							str/ft_strcapitalize.c\
							str/ft_strupcase.c\
							str/ft_strlowcase.c\
							str/ft_strcmp.c\
							str/ft_strcat.c\
							str/ft_strcut.c\
							str/ft_strstr.c\
							str/ft_strncat.c\
							str/ft_strlen_tr.c\
							str/ft_str_swap.c\
							str_tab/ft_tablen.c\
							str_tab/ft_sort_string_tab.c\
							chain_list/ft_lstnew.c\
							chain_list/ft_lstadd_front.c\
							chain_list/ft_lstsize.c\
							chain_list/ft_lstlast.c\
							chain_list/ft_lstadd_back.c\
							chain_list/ft_lstdelone.c\
							chain_list/ft_lstclear.c\
							chain_list/ft_lstiter.c\
							chain_list/ft_lstmap.c\
							chain_list/print_list.c\
							write/ft_putchar_fd.c\
							write/ft_putstr_fd.c\
							write/ft_putendl_fd.c\
							write/ft_putnbr_fd.c\
							write/ft_putstr_len.c\
							write/ft_putchar_len.c\
							write/ft_putchar_len_fd.c\
							write/ft_putstr_len_fd.c\
							write/ft_putstr_non_printable.c\
							write/ft_print_memory.c\
							write/ft_putstr.c\
							write/ft_putchar.c\
							write/ft_putendl.c\
							write/ft_putnbr.c\
							printf/ft_printf.c\
							printf/ft_printf_nbr_utils.c\
							printf/ft_printf_utils.c\
							int_tab/ft_int_swap.c\
							int_tab/ft_dup_int_tab.c\
							int_tab/ft_rev_int_tab.c\
							int_tab/ft_sort_int_tab.c\
							int_tab/ft_range.c\
							int_tab/ft_ultimate_range.c\
							int/ft_intlen.c\
							int/ft_min.c\
							convert/ft_atoi_base.c\
							convert/ft_atoi.c\
							convert/ft_base_error.c\
							convert/ft_convert_base.c\
							convert/ft_convert_base_utils.c\
							convert/ft_itoa.c\
							convert/ft_putnbr_base.c\
							get_next_line/get_next_line.c\
							get_next_line/get_next_line_utils.c\
							maths/ft_iterative_factorial.c\
							maths/ft_iterative_power.c\
							maths/ft_recursive_factorial.c\
							maths/ft_recursive_power.c\
							maths/ft_fibonacci.c\
							maths/ft_sqrt.c\
							maths/ft_is_prime.c\
							maths/ft_find_next_prime.c\

SRCS_DIR	:=	srcs
SRCS		:=	$(SRCS:%=$(SRCS_DIR)/%)

# OBJECTS
OBJS_DIR	:=	.objs
OBJS		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

# **************************************************************************** #
# 								     RULES									   #
# **************************************************************************** #

all: $(NAME)

$(OBJS_DIR)/%.o: %.c
	$(MK) $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@if [ "$(PROJ_CMP)" -ne "$(FILE)" ]; then \
		printf " $(COLOR_1) [$(RESET)$(PROJ_CMP)$(COLOR_1)/$(RESET)$(FILE)$(COLOR_1)]\t$(RESET)$<                     \r"; \
	else \
		printf " $(COLOR_1) [$(RESET)$(PROJ_CMP)$(COLOR_1)/$(RESET)$(FILE)$(COLOR_1)]\t$(RESET)$<                 \n\n"; \
	fi
	@$(eval PROJ_CMP=$(shell echo $$(($(PROJ_CMP)+1))))

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf "  ✅ $(COLOR_2)$(NAME) successfully compiled$(RESET)\n"
	@printf "  🔄 $(COLOR_3)$(NAME) is ready to run$(RESET) \n\n"

clean:
	@printf "  👾 \033[1;4;38;5;240m$(NAME)$(RESET)   \n  $(COLOR_3)└──> 🗑️    \033[1;38;5;255m.o \033[1;38;5;248mhave been deleted$(RESET)\n"	
	$(RM) $(OBJS_DIR)

fclean: clean
	@printf "  $(COLOR_3)└──> 🗑️    \033[1;38;5;255mlibft binary \033[1;38;5;248mhas been deleted$(RESET)\n\n"
	$(RM) $(NAME)

clear:
	@clear

re:	clear fclean all

.PHONY:	re fclean all clean

