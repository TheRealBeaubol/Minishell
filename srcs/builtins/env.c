/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 01:40:35 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/02 20:24:55 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	env(t_ms *ms)
{
	int		i;
	char	*str;

	i = 0;
	if (!ms->lst->next)
	{
		while (ms->env[i])
		{
			str = ft_strjoin(ms->env[i], "\n", NULL, 0b000);
			ft_dprintf(1, str);
			free(str);
			i++;
		}
	}
	if (ms->lst->next->content[0] == '-')
	{
		g_exit = 125;
		ft_dprintf(2, "env: invalid option -- %c\n", ms->lst->next->content[1]);
	}
	else
	{
		g_exit = 127;
		ft_dprintf(2, "env: %s: No such file or directory\n", \
		ms->lst->next->content);
	}
}
