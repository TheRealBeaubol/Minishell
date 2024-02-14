/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:25:30 by lboiteux          #+#    #+#             */
/*   Updated: 2023/11/25 01:30:27 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putstr_non_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] < 32 || str[i] > 126)
		{
			write(1, "\\", 1);
			write(1, &"0123456789abcdef"[(unsigned char)(str[i]) / 16], 1);
			write(1, &"0123456789abcdef"[(unsigned char)(str[i]) % 16], 1);
		}
		else
		{
			write(1, &str[i], 1);
		}
		i++;
	}
}
