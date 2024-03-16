/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:30:16 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/16 17:20:15 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_position_in_base(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_convert_base_strlen(char *str)
{
	int	n;

	n = 0;
	while (str[n] != '\0')
		++n;
	return (n);
}

char	*ft_convert_base_strcat(char *dest, char src)
{
	int	i;

	i = 0;
	while (dest[i] != 0)
		i++;
	dest[i] = src;
	dest[i + 1] = 0;
	return (dest);
}
