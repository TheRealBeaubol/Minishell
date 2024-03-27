/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:46:19 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/18 16:47:42 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 420
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

int		ft_tablen(char **str);
int		ft_strlen_tr(char *str, char c);
char	**ft_sort_string_tab(char **tab);
int		ft_iswhitespace(char c);
int		ft_putchar_len_fd(char c, int fd);
int		ft_putstr_len_fd(char *s, int fd);
int		ft_ul_nb_base_utils(unsigned long nb, int *size, int fd);
char	*ft_strrev(char *str);
int		**ft_dup_int_tab(int **src, int size1, int size2);
int		ft_ishexa(char c);
void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
char	*ft_str_lower(char *str);
char	*ft_strcut(char *str, char *cut);
int		ft_count_words(char *str, char charset);
void	ft_free_list(t_list **stack);
size_t	ft_strlen(char *s);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
void	ft_free_int_tab(int **tab, int size);
int		ft_isprint(int c);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
char	*ft_str_start_del(char *str, char *del);
size_t	ft_strlcat(char *dst, char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strchr(char *s, int c);
char	*ft_strrchr(char *s, int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(char *big, char *little, size_t len);
int		ft_atoi(char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2, char *c, int tofree);
char	*ft_strtrim(char *s1, char *set);
char	**ft_char_split(char *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(char *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_printf(char *s, ...);
int		ft_dprintf(int fd, char *s, ...);
int		ft_printf_flag_verif(char c);
int		ft_printf_flag_mana(char c, va_list arg, int fd);
void	ft_ul_nb_b(unsigned long nb, char *base, int *size, int i);
void	ft_ui_nb_b(unsigned int nb, char *base, int *size, int fd);
void	ft_printf_putnbr(int nb, int *size, int fd);
int		ft_putstr_len(char *s);
int		ft_putchar_len(char c);
void	ft_putstr(char *s);
void	ft_putnbr(int n);
void	ft_putendl(char *s);
void	ft_putchar(char c);
void	ft_int_swap(int *a, int *b);
void	ft_str_swap(char **a, char **b);
void	ft_rev_int_tab(int *tab, int size);
void	ft_sort_int_tab(int *tab, int size);
int		ft_str_is_alpha(char *str);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
int		ft_str_is_numeric(char *str);
int		ft_str_is_lowercase(char *str);
char	*ft_strupcase(char *str);
int		ft_str_is_printable(char *str);
int		ft_str_is_uppercase(char *str);
char	*ft_strlowcase(char *str);
void	ft_putstr_non_printable(char *str);
void	*ft_print_memory(void *addr, unsigned int size);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcat(char *dest, char *src);
char	*ft_strncat(char *dest, char *src, unsigned int nb);
char	*ft_strstr(char *str, char *to_find);
void	ft_putnbr_base(int nbr, char *base);
int		ft_atoi_base(char *str, char *base);
int		ft_iterative_factorial(int nb);
int		ft_recursive_factorial(int nb);
int		ft_iterative_power(int nb, int power);
int		ft_recursive_power(int nb, int power);
int		ft_fibonacci(int index);
int		ft_sqrt(int nb);
int		ft_find_next_prime(int nb);
int		*ft_range(int min, int max);
int		ft_ultimate_range(int **range, int min, int max);
void	ft_putnbr_base(int nbr, char *base);
int		ft_intlen(int n);
char	*ft_convert_base(char *nbr, char *base_from, char *base_to);
int		ft_base_error(char *base);
int		ft_atoi_base(char *str, char *base);
char	**ft_str_split(char *str, char *charset);
void	ft_free_tab(char **tab);
void	*ft_realloc(char *ptr, int size);
char	*ft_gnl_strchr(char *s, int c);
int		ft_min(int nb1, int nb2);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*ft_get_next_line(int fd, int free_static);
int		ft_position_in_base(char *base, char c);
int		ft_convert_base_strlen(char *str);
char	*ft_convert_base_strcat(char *dest, char src);
int		ft_is_prime(int nb);
char	*ft_strdup_range(char *src, int start, int end);
#endif
