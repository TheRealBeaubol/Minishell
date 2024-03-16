/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_string_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:28:12 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/16 22:08:40 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_swap_indice(int **indice, int i, int j)
{
	int	tmp;

	tmp = (*indice)[i];
	(*indice)[i] = (*indice)[j];
	(*indice)[j] = tmp;
}

static void	sort_indice(char **tab, int **indice)
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
				ft_swap_indice(indice, i, j);
			j++;
		}
		i++;
	}
}

void	print_indice(int *indice, char **tab)
{
	int	i;

	i = 0;
	while (i < ft_tablen(tab))
	{
		ft_printf("%d\n", indice[i]);
		i++;
	}
}

int	*ft_sort_string_tab(char **tab)
{
	int		*indice;
	int		i;

	indice = calloc((ft_tablen(tab)), sizeof(int));
	i = -1;
	while (++i < ft_tablen(tab))
		indice[i] = i;
	sort_indice(tab, &indice);
	//print_indice(indice, tab);
	return (indice);
}
