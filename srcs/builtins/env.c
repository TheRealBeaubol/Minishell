/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 01:40:35 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/15 01:28:46 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

extern int	g_exit;

void	env(t_ms *ms)
{
	int		i;
	char	*str;

	i = 0;
	while (ms->env[i])
	{
		str = ft_strjoin(ms->env[i], "\n", NULL, 0b000);
		ft_dprintf(1, str);
		free(str);
		i++;
	}
}
