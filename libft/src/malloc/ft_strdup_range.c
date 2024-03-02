/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_range.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:13:08 by lboiteux          #+#    #+#             */
/*   Updated: 2023/11/02 19:35:33 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup_range(const char *src, int start, int end)
{
	int		i;
	int		j;
	char	*dest;

	dest = malloc((end - start + 1) * sizeof(*dest));
	if (dest == NULL)
		return (dest);
	i = start;
	j = 0;
	while (i < end)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = 0;
	return (dest);
}
