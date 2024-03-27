/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:41:33 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/24 14:46:43 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	convert_to_hex(unsigned long long int addr, int cond)
{
	char	*base;

	base = "0123456789abcdef";
	if (addr < 16 && cond == 1)
	{
		write(1, "0", 1);
		write(1, &base[addr % 16], 1);
	}
	else if (addr >= 17)
	{
		convert_to_hex(addr / 16, 0);
		convert_to_hex(addr % 16, 0);
	}
	else
		write(1, &base[addr], 1);
}

static void	print_addr(unsigned long long int addr)
{
	unsigned long long int	car;
	int						i;

	car = addr;
	i = 1;
	while (i < 16)
	{
		if (car < 16)
			write(1, "0", 1);
		car = car / 16;
		i++;
	}
	convert_to_hex(addr, 0);
}

static void	print_values(unsigned char *car, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < 16)
	{
		if (i % 2 == 0)
			write(1, " ", 1);
		if (i <= size)
			convert_to_hex((unsigned long long int)*(car + i), 1);
		else
		{
			write(1, "  ", 2);
		}
		i++;
	}
	write(1, " ", 1);
	i = 0;
	while (i <= size)
	{
		if (*(car + i) <= 31 || *(car + i) >= 127)
			write(1, ".", 1);
		else
			write(1, (car + i), 1);
		i++;
	}
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	i;
	unsigned char	*car;
	unsigned int	size2;

	i = 0;
	car = addr;
	if (size == 0)
		return (0);
	while (i * 16 < size)
	{
		if (i < size / 16)
			size2 = 16;
		else
			size2 = size % 16;
		print_addr((unsigned long long int)car + (i * 16));
		write(1, ":", 1);
		print_values(car + (i * 16), size2);
		write(1, "\n", 1);
		i++;
	}
	return (addr);
}
