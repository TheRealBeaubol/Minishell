/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:44:17 by mhervoch          #+#    #+#             */
/*   Updated: 2024/02/24 19:35:17 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	change_directory(t_ms *ms)
{
	char	*error;
	char	*tmp;

	if (!ms->lst->next)
		return (0);
	ms->lst = ms->lst->next;
	if (ms->lst->content[0] == '-' && ms->lst->content[1] == '\0')
	{
		free(ms->lst->content);
		tmp = get_env(ms->env, "HOME=");
		ms->lst->content = ft_calloc((ft_strlen(tmp) + \
ft_strlen("/Desktop") + 1), sizeof(char));
		ms->lst->content = ft_strdup(tmp);
		ms->lst->content = ft_strjoin(ms->lst->content, "/Desktop");
		free(tmp);
	}
	if (chdir(ft_strjoin(ms->lst->content, "/")) == -1)
	{
		error = ft_strjoin("minishell: cd: ", ms->lst->content);
		perror(error);
		free(error);
		return (0);
	}
	ms->prompt = ft_strjoin(getcwd(NULL, 0), ">");
	return (1);
}
