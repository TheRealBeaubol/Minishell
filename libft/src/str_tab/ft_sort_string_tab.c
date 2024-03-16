/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_string_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:28:12 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/16 01:31:28 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_swap_indice(int **indice, int i, int j)
{
	int	tmp;

	tmp = indice[i];
	indice[i] = indice[j];
	indice[j] = indice [i];
}

static int	sort_indice(char **tab, char **export, int **indice)
{
	int	i;
	int	j;

	i = 0;
	while (i < sizeof(*indice))
	{
		j = i + 1;
		while (j < int_len(*indice))
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
				ft_swap_indice(indice, i, j);
			j++;
		}
		i++;
	}
}

int	*ft_sort_string_tab(char **tab)
{
	char	**export;
	int		*indice;
	int		i;

	export = calloc((ft_strstr_len(tab)), sizeof(char *));
	i = 0;
	while (i < ft_strstr_len(tab))
		indice[i] = i++;
	i = 0;
	sort_indice(tab, export, &indice);
	return (indice);
}
