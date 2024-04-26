/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extend_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:14:42 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/26 14:16:46 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_extend_tab(char **dest, char **src, int *i)
{
	int		j;
	int		k;
	char	**new;

	j = 0;
	k = 0;
	new = ft_calloc(ft_tablen(dest) + ft_tablen(src) + 1, sizeof(char *));
	if (!new)
		return (NULL);
	while (j < *i)
	{
		new[j] = ft_strdup(dest[j]);
		j++;
	}
	while (src[k])
	{
		new[j] = ft_strdup(src[k]);
		j++;
		k++;
	}
	*i = j;
	ft_free_tab(src);
	ft_free_tab(dest);
	return (new);
}
