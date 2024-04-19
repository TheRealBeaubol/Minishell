/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:48:10 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/24 14:46:43 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(char *s, ...)
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
		if (s[i] == '%' && (ft_printf_flag_verif(s[i + 1])))
		{
			size += ft_printf_flag_mana(s[i + 1], arg, 1);
			i += 2;
		}
		else if (s[i] == '%' && s[i + 1] == 0)
			return (-1);
		else
		{
			size += ft_putchar_len_fd(s[i], 1);
			i++;
		}
	}
	return (size);
}

int	ft_dprintf(int fd, char *s, ...)
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
		if (s[i] == '%' && (ft_printf_flag_verif(s[i + 1])))
		{
			size += ft_printf_flag_mana(s[i + 1], arg, fd);
			i += 2;
		}
		else if (s[i] == '%' && s[i + 1] == 0)
			return (-1);
		else
		{
			size += ft_putchar_len_fd(s[i], fd);
			i++;
		}
	}
	return (size);
}
