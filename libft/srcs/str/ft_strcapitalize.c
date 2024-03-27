/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 01:27:37 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/24 14:46:43 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *str)
{
	int	j;

	j = 0;
	ft_strlowcase(str);
	if ('a' <= str[j] && str[j] <= 'z')
		str[j] = str[j] - 32;
	while (str[j + 1] != 0)
	{
		if (!(('a' <= str[j] && str[j] <= 'z')
				|| ('A' <= str[j] && str[j] <= 'Z')
				|| ('0' <= str[j] && str[j] <= '9')))
			if ('a' <= str[j + 1] && str[j + 1] <= 'z')
				str[j + 1] = str[j + 1] - 32;
		j++;
	}
	return (str);
}
