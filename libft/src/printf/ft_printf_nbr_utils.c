/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 23:37:55 by lboiteux          #+#    #+#             */
/*   Updated: 2023/11/23 23:36:33 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_ul_nb_base(unsigned long nb, char *base, int *size, int i)
{
	unsigned long	cpt;

	if (!nb)
	{
		ft_putstr_len("(nil)");
		(*size) += 5;
		return ;
	}
	if (nb != 0 && i == 1)
		(*size) += ft_putstr_len("0x");
	cpt = ft_strlen(base);
	if (nb >= cpt)
	{
		ft_ul_nb_base(nb / cpt, base, size, 0);
		ft_putchar_len(base[nb % cpt]);
		(*size)++;
	}
	else
	{
		ft_putchar_len(base[nb]);
		(*size)++;
	}
}

void	ft_ui_putnbr_base(unsigned int nb, char *base, int *size)
{
	unsigned int	cpt;

	cpt = ft_strlen(base);
	if (nb >= cpt)
	{
		ft_ui_putnbr_base(nb / cpt, base, size);
		ft_putchar_len(base[nb % cpt]);
		(*size)++;
	}
	else
	{
		ft_putchar_len(base[nb]);
		(*size)++;
	}
}

void	ft_printf_putnbr(int nb, int *size)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*size) += 11;
		return ;
	}
	if (nb < 0)
	{
		ft_putchar_len('-');
		nb = nb * -1;
		(*size)++;
	}
	if (nb < 10)
	{
		ft_putchar_len(nb + '0');
		(*size)++;
		return ;
	}
	else if (nb >= 10)
	{
		(*size)++;
		ft_printf_putnbr(nb / 10, size);
		write(1, &(char){nb % 10 + 48}, 1);
	}
}
