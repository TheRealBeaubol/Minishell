/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 01:40:35 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/19 12:45:54 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	env(t_cmdlist *cmdlst, t_ms *ms)
{
	int		i;

	i = 0;
	if (!cmdlst->param[1])
	{
		while (ms->env[i])
		{
			if (ft_strchr(ms->env[i], '='))
				ft_printf("%s\n", ms->env[i]);
			i++;
		}
		g_exit = 0;
		return ;
	}
	if (cmdlst->param[1][0] == '-')
	{
		g_exit = 125;
		ft_dprintf(2, ENV_EXIT_MSG_1, cmdlst->param[1][1]);
	}
	else
	{
		g_exit = 127;
		ft_dprintf(2, ENV_EXIT_MSG_2, cmdlst->param[1]);
	}
}
