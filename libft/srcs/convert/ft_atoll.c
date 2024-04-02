/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:07:24 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/02 20:07:44 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(char *nbr)
{
	int			i;
	long long	stock;
	long long	sign;

	sign = 1;
	i = 0;
	stock = 0;
	while (nbr[i] == '0')
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nbr[i] != 0 && nbr[i] >= '0' && nbr[i] <= '9')
		stock = (stock * 10) + (nbr[i++] - 48);
	return (stock * sign);
}
