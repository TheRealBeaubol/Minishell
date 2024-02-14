/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:03:56 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/11 16:48:10 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	**ft_dup_int_tab(int **src, int size1, int size2)
{
	int	**dest;
	int	i;
	int	j;

	dest = ft_calloc(size1, sizeof(int *));
	if (!dest)
		return (NULL);
	i = -1;
	while (++i != size1)
	{
		dest[i] = ft_calloc(size2, sizeof(int));
		if (!dest[i])
		{
			ft_free_int_tab(dest, i);
			return (NULL);
		}
	}
	i = -1;
	while (++i != size1 - 1)
	{
		j = -1;
		while (++j != size2 - 1)
			dest[i][j] = src[i][j];
	}
	return (dest);
}
