/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:48:18 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/06 20:41:57 by mhervoch         ###   ########.fr       */
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
		write(1, "\n", 1);
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
			write(1, tmp->content, ft_strlen(tmp->content) + 1);
		else
		{
			write(1, " ", 1);
			write(1, tmp->content, ft_strlen(tmp->content) + 1);
		}
		tmp = tmp->next;
	}
	if (cpt != 0)
		write(1, " ", 1);
	write(1, tmp->content, ft_strlen(tmp->content) + 1);
	if (n == 1)
		write(1, "\n", 1);
}
