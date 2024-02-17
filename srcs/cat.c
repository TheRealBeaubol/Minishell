/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:47:19 by mhervoch          #+#    #+#             */
/*   Updated: 2024/02/17 16:17:48 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	executable(t_ms *ms)
{
	int		i;
	int		pid;
	char	**path;
	
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		child_process(char **env, char)
	}
}
