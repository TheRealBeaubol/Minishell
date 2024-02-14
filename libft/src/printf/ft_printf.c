/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:48:10 by lboiteux          #+#    #+#             */
/*   Updated: 2023/11/23 23:34:02 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf(const char *s, ...)
{
	va_list	arg;
	int		i;
	int		size;

	va_start(arg, s);
	i = 0;
	size = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '%' && (printf_flag_verif(s[i + 1])))
		{
			size += printf_flag_mana(s[i + 1], arg);
			i += 2;
		}
		else if (s[i] == '%' && s[i + 1] == 0)
			return (-1);
		else
		{
			size += ft_putchar_len(s[i]);
			i++;
		}
	}
	return (size);
}
