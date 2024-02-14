/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 00:26:26 by lboiteux          #+#    #+#             */
/*   Updated: 2023/11/26 00:04:46 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	if (*to_find == 0)
		return (str);
	while (*str != 0)
	{
		if (*str == *to_find)
		{
			i = 0;
			j = 0;
			while (to_find[i] != 0)
			{
				if (str[i] != to_find[i])
					j = 1;
				i++;
			}
			if (j == 0)
				return (str);
		}
		str++;
	}
	return (0);
}
