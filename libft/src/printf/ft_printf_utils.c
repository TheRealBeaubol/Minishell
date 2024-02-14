/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 23:06:15 by lboiteux          #+#    #+#             */
/*   Updated: 2023/11/23 23:39:37 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	printf_flag_mana(char c, va_list arg)
{
	int	size;

	size = 0;
	if (c == 'c')
		size += ft_putchar_len(va_arg(arg, int));
	else if (c == 's')
		size += ft_putstr_len(va_arg(arg, char *));
	else if (c == 'p')
		ft_ul_nb_base(va_arg(arg, unsigned long), "0123456789abcdef", &size, 1);
	else if (c == 'd' || c == 'i')
		ft_printf_putnbr(va_arg(arg, int), &size);
	else if (c == 'u')
		ft_ui_putnbr_base(va_arg(arg, unsigned int), "0123456789", &size);
	else if (c == 'x')
		ft_ui_putnbr_base(va_arg(arg, unsigned int), "0123456789abcdef", &size);
	else if (c == 'X')
		ft_ui_putnbr_base(va_arg(arg, unsigned int), "0123456789ABCDEF", &size);
	else if (c == '%')
		size += ft_putchar_len('%');
	return (size);
}

int	printf_flag_verif(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%');
}
