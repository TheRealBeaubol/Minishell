/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:55:30 by mhervoch          #+#    #+#             */
/*   Updated: 2024/02/24 19:37:07 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	pwd(t_ms *ms)
{
	char	*pwd;

	(void) ms;
	//pwd = get_pwd(ms);
	pwd = getcwd(NULL, 0);
	printf("%s", pwd);
	return (0);
}

char	*get_pwd(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->env[i] && strncmp(ms->env[i], "PWD=", 4))
		i++;
	return (ms->env[i] + 4);
}

char	*get_prompt(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->env[i] && strncmp(ms->env[i], "PWD=", 4))
		i++;
	return (ms->env[i] + 24);
}
