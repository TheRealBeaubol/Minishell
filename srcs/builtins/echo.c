/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:48:18 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/12 20:12:09 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"
#include <string.h>

static int	is_valid_flag(char *str)
{
	if (*str == '-')
	{
		str++;
		while (*str != '\0')
		{
			if (*str == 'n')
				str++;
			else
				return (1);
		}
		return (0);
	}
	else
		return (1);
}

static void	echo_printing(t_list *tmp, int n)
{
	int	cpt;

	cpt = 0;
	while (tmp->next)
	{
		if (cpt++ == 0)
			ft_dprintf(1, tmp->content);
		else
		{
			ft_dprintf(1, " ");
			ft_dprintf(1, tmp->content);
		}
		tmp = tmp->next;
	}
	if (cpt != 0)
		ft_dprintf(1, " ");
	ft_dprintf(1, tmp->content);
	if (n == 1)
		ft_dprintf(1, "\n");
}

void	echo(t_ms *ms)
{
	t_list	*tmp;
	int		n;

	if (!ms->lst->next)
	{
		ft_dprintf(1, "\n");
		return ;
	}
	n = 1;
	tmp = ms->lst->next;
	while (!is_valid_flag(tmp->content))
	{
		n = 0;
		if (tmp->next)
			tmp = tmp->next;
		else
			return ;
	}
	echo_printing(tmp, n);
}
