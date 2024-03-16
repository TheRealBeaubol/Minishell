/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:44:17 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/16 10:15:43 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	change_directory(t_ms *ms)
{
	char	*error;
	t_list	*tmp;

	tmp = ms->lst;
	if (!tmp->next)
		return (0);
	tmp = tmp->next;
	if (tmp->content[0] == '-' && tmp->content[1] == '\0')
		handle_flag(ms);
	else
	{
		old_pwd(ms);
		if (chdir(tmp->content) == -1)
		{
			g_exit = 1;
			error = ft_strjoin("minishell: cd: ", tmp->content, NULL, 0b000);
			perror(error);
			free(error);
			return (0);
		}
	}
	free(ms->prompt);
	ms->prompt = get_prompt(ms);
	edit_env(ms);
	return (1);
}
