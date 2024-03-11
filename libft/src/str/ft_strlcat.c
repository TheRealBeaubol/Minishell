/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:30:21 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/11 21:33:52 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (!src)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	len = ft_strlen(dst);
	if (len > size)
		return (ft_strlen(src) + size);
	if (!*(src + i))
		return (len);
	while (*(src + i) && i + len + 1 < size)
	{
		*(dst + len + i) = *(src + i);
		i ++;
	}
	*(dst + len + i) = '\0';
	while (*(src + i))
		i++;
	return (len + i);
}
