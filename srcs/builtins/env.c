/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 01:40:35 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/04 10:40:59 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	env(t_ms *ms)
{
	int		i;

	i = 0;
	if (!ms->lst->next)
	{
		while (ms->env[i])
		{
			if (ft_strchr(ms->env[i], '='))
				ft_dprintf(1, "%s\n", ms->env[i]);
			i++;
		}
		return ;
	}
	if (ms->lst->next->content[0] == '-')
	{
		g_exit = 125;
		ft_dprintf(2, ENV_EXIT_MSG_1, ms->lst->next->content[1]);
	}
	else
	{
		g_exit = 127;
		ft_dprintf(2, ENV_EXIT_MSG_2, ms->lst->next->content);
	}
}
