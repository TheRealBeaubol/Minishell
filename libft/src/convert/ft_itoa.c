/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 01:53:46 by lboiteux          #+#    #+#             */
/*   Updated: 2023/11/26 00:38:23 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_itoa_rec(int n, char **str)
{
	if (n == -2147483648)
	{
		ft_strlcat(*str, "-2147483648", 12);
		*str += 12;
		return (*str);
	}
	else if (n < 0)
	{
		**str = '-';
		n = n * -1;
		(*str)++;
	}
	if (n < 10)
	{
		**str = n + 48;
		(*str)++;
	}
	else if (n >= 10)
	{
		ft_itoa_rec(n / 10, str);
		**str = n % 10 + 48;
		(*str)++;
	}
	return (*str);
}

char	*ft_itoa(int n)
{
	char	*str;
	char	*start;

	str = ft_calloc((ft_intlen(n) + 1), sizeof(char));
	if (!str)
		return (NULL);
	start = str;
	ft_itoa_rec(n, &str);
	return (start);
}
