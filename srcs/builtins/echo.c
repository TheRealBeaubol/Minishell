/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:48:18 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/07 15:30:15 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"
#include <string.h>

void	echo(t_ms *ms)
{
	t_list	*tmp;
	int		cpt;
	int		n;

	if (!ms->lst->next)
	{
		ft_dprintf(1, "\n");
		return ;
	}
	cpt = 0;
	n = 1;
	tmp = ms->lst->next;
	if (!ft_strncmp(tmp->content, "-n", 2))
	{
		n = 0;
		if (tmp->next)
			tmp = tmp->next;
		else
			return ;
	}
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
