/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:30:16 by lboiteux          #+#    #+#             */
/*   Updated: 2023/11/26 01:33:12 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	position_in_base(char *base, char c)
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

int	convert_base_strlen(char *str)
{
	int	n;

	n = 0;
	while (str[n] != '\0')
		++n;
	return (n);
}

char	*convert_base_strcat(char *dest, char src)
{
	int	i;

	i = 0;
	while (dest[i] != 0)
		i++;
	dest[i] = src;
	dest[i + 1] = 0;
	return (dest);
}
