/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:37:29 by lboiteux          #+#    #+#             */
/*   Updated: 2023/11/26 01:30:24 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	stock;
	int	signe;

	if (ft_base_error(base))
		return (0);
	signe = 1;
	i = 0;
	stock = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] && position_in_base(base, str[i]) != -1)
	{
		stock = stock * ft_strlen(base) + position_in_base(base, str[i]);
		i++;
	}
	return (stock * signe);
}
