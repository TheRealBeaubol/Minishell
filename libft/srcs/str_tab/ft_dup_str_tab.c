/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_str_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:39:51 by lboiteux          #+#    #+#             */
/*   Updated: 2024/05/01 01:40:05 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dup_str_tab(char **tab)
{
	char	**dup_tab;
	int		i;

	dup_tab = ft_calloc(ft_tablen(tab) + 1, sizeof(char *));
	i = 0;
	while (tab[i])
	{
		dup_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	ft_free_tab(tab);
	return (dup_tab);
}
