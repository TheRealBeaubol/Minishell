/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:28:32 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/24 14:46:43 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_rev_int_tab(int *tab, int size)
{
	int	start;
	int	end;

	end = size;
	start = 0;
	if (size % 2 == 0)
	{
		while (end > (size / 2))
		{
			ft_int_swap(&tab[start], &tab[end - 1]);
			--end;
			++start;
		}
	}
	else
	{
		while (end > ((size / 2) + 1))
		{
			ft_int_swap(&tab[start], &tab[end - 1]);
			--end;
			++start;
		}
	}
}
