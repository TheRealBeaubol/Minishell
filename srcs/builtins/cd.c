/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:44:17 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/02 14:38:11 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	edit_env(t_ms *ms)
{
	int	i;

	i = get_env_indice(ms, "PWD");
	ms->env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
}

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
	ms->prompt = ft_strjoin(get_prompt(), ">");
	edit_env(ms);
	return (1);
}
