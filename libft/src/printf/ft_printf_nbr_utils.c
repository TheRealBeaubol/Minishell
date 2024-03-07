/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 23:37:55 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/07 14:31:30 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_ul_nb_base_utils(unsigned long nb, int *size, int fd)
{
	if (!nb)
	{
		ft_putstr_len_fd("(nil)", fd);
		(*size) += 5;
		return (1);
	}
	if (nb != 0)
		(*size) += ft_putstr_len_fd("0x", fd);
	return (0);
}

void	ft_ul_nb_b(unsigned long nb, char *base, int *size, int fd)
{
	unsigned long	cpt;

	cpt = ft_strlen(base);
	if (nb >= cpt)
	{
		ft_ul_nb_b(nb / cpt, base, size, fd);
		ft_putchar_len_fd(base[nb % cpt], fd);
		(*size)++;
	}
	else
	{
		ft_putchar_len_fd(base[nb], fd);
		(*size)++;
	}
}

void	ft_ui_nb_b(unsigned int nb, char *base, int *size, int fd)
{
	unsigned int	cpt;

	cpt = ft_strlen(base);
	if (nb >= cpt)
	{
		ft_ui_nb_b(nb / cpt, base, size, fd);
		ft_putchar_len_fd(base[nb % cpt], fd);
		(*size)++;
	}
	else
	{
		ft_putchar_len_fd(base[nb], fd);
		(*size)++;
	}
}

void	ft_printf_putnbr(int nb, int *size, int fd)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*size) += 11;
		return ;
	}
	if (nb < 0)
	{
		ft_putchar_len_fd('-', fd);
		nb = nb * -1;
		(*size)++;
	}
	if (nb < 10)
	{
		ft_putchar_len_fd(nb + '0', fd);
		(*size)++;
		return ;
	}
	else if (nb >= 10)
	{
		(*size)++;
		ft_printf_putnbr(nb / 10, size, fd);
		write(1, &(char){nb % 10 + 48}, 1);
	}
}
