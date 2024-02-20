/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:44:17 by mhervoch          #+#    #+#             */
/*   Updated: 2024/02/21 00:53:13 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

/*void	edit_env(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->env[i] && strncmp(ms->env[i], "PWD=", 4))
		i++;
	ms->env[i] = ft_strjoin(ft_strjoin(ms->env[i], "/"), ms->lst->content);
}*/

int	change_directory(t_ms *ms)
{
	ms->lst = ms->lst->next;
	if (chdir(ft_strjoin(ms->lst->content, "/")) == -1)
	{
		printf("Directory not found\n");
		return (0);
	}
	//edit_env(ms);
	ms->prompt = ft_strjoin(getcwd(NULL, 0) + 20, ">");
	return (1);
}
