/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:51:32 by lboiteux          #+#    #+#             */
/*   Updated: 2023/11/25 01:18:37 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_sort_int_tab(int *tab, int size)
{
	int	start1;
	int	start2;

	start1 = 0;
	while (start1 < size - 1)
	{
		start2 = start1 + 1;
		while (start2 < size)
		{
			if (tab[start1] > tab[start2])
				ft_swap(&tab[start1], &tab[start2]);
			start2++;
		}
		start1++;
	}
}
