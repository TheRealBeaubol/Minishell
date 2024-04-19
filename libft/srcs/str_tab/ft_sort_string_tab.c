/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_string_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:28:12 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/24 14:46:43 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**sort_indice(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (i < ft_tablen(tab))
	{
		j = i + 1;
		while (j < ft_tablen(tab))
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
				ft_str_swap(&tab[i], &tab[j]);
			j++;
		}
		i++;
	}
	return (tab);
}

char	**ft_sort_string_tab(char **tab)
{
	int		i;
	char	**env_tab;

	env_tab = ft_calloc(ft_tablen(tab) + 1, sizeof(char *));
	if (!env_tab)
		return (NULL);
	i = -1;
	while (++i < ft_tablen(tab))
		env_tab[i] = ft_strdup(tab[i]);
	env_tab = sort_indice(env_tab);
	return (env_tab);
}
