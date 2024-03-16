/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 23:06:15 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/16 17:15:23 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf_flag_mana(char c, va_list arg, int fd)
{
	int		s;
	int		condition;

	s = 0;
	if (c == 'c')
		s += ft_putchar_len_fd(va_arg(arg, int), fd);
	else if (c == 's')
		s += ft_putstr_len_fd(va_arg(arg, char *), fd);
	else if (c == 'p')
	{
		condition = ft_ul_nb_base_utils(va_arg(arg, unsigned long), &s, fd);
		if (condition == 0)
			ft_ul_nb_b(va_arg(arg, unsigned long), "0123456789abcdef", &s, fd);
	}
	else if (c == 'd' || c == 'i')
		ft_printf_putnbr(va_arg(arg, int), &s, fd);
	else if (c == 'u')
		ft_ui_nb_b(va_arg(arg, unsigned int), "0123456789", &s, fd);
	else if (c == 'x')
		ft_ui_nb_b(va_arg(arg, unsigned int), "0123456789abcdef", &s, fd);
	else if (c == 'X')
		ft_ui_nb_b(va_arg(arg, unsigned int), "0123456789ABCDEF", &s, fd);
	else if (c == '%')
		s += ft_putchar_len_fd('%', fd);
	return (s);
}

int	ft_printf_flag_verif(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%');
}
