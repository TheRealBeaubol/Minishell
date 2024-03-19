/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:35:35 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/19 16:51:02 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long double	ft_atold(char *nbr)
{
	int			i;
	long double	stock;
	long double	sign;

	sign = 1;
	i = 0;
	stock = 0;
	while ((9 <= nbr[i] && nbr[i] <= 13) || nbr[i] == 32)
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nbr[i] != 0 && nbr[i] >= '0' && nbr[i] <= '9')
	{
		stock = (stock * 10) + (nbr[i] - 48);
		i++;
	}
	return (stock * sign);
}

void	exit(t_ms *ms)
{
	ft_dprintf(2, "exit\n");

}
