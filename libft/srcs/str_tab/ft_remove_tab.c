/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:14:44 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/26 14:15:27 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_remove_tab(char **tab, char c)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_calloc(2, sizeof(char *));
	while (tab[i])
	{
		if (*tab[i] != c)
			new = ft_join_tab(new, tab[i]);
		i++;
	}
	ft_free_tab(tab);
	return (new);
}
