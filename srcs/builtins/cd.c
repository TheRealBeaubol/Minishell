/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:44:17 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/08 16:07:14 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static void	edit_env(t_ms *ms)
{
	int	i;

	i = get_env_indice(ms, "PWD");
	ms->env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
}

static void	old_pwd(t_ms *ms)
{
	int	i;

	i = get_env_indice(ms, "OLDPWD");
	ms->env[i] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
}

static void	handle_flag(t_ms *ms)
{
	char	*old_pwd;
	int		i;

	old_pwd = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	chdir(ft_strcut(ms->env[get_env_indice(ms, "OLDPWD")], "OLDPWD="));
	i = get_env_indice(ms, "OLDPWD");
	ms->env[i] = old_pwd;
}

int	change_directory(t_ms *ms)
{
	char	*error;

	if (!ms->lst->next)
		return (0);
	ms->lst = ms->lst->next;
	if (ms->lst->content[0] == '-' && ms->lst->content[1] == '\0')
		handle_flag(ms);
	else
	{
		old_pwd(ms);
		if (chdir(ft_strjoin(ms->lst->content, "/")) == -1)
		{
			error = ft_strjoin("minishell: cd: ", ms->lst->content);
			perror(error);
			free(error);
			return (0);
		}
	}
	ms->prompt = get_prompt(ms);
	edit_env(ms);
	return (1);
}
