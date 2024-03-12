/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:44:17 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/12 23:41:15 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*cwdget(void)
{
	char	cwd[65536];

	if (getcwd(cwd, 0))
		return (ft_strdup(cwd));
	return (NULL);
}

static void	edit_env(t_ms *ms)
{
	int	i;

	i = get_env_indice(ms, "PWD");
	free(ms->env[i]);
	ms->env[i] = ft_strjoin("PWD=", cwdget(), NULL, 0b010);
}

static void	old_pwd(t_ms *ms)
{
	int		i;

	i = get_env_indice(ms, "OLDPWD");
	free(ms->env[i]);
	ms->env[i] = \
		ft_strjoin("OLDPWD=", cwdget(), NULL, 0b010);
}

static void	handle_flag(t_ms *ms)
{
	char	*old_pwd;
	char	*tmp;
	int		i;

	old_pwd = ft_strjoin("OLDPWD=", cwdget(), NULL, 0b010);
	tmp = ft_strcut(ms->env[get_env_indice(ms, "OLDPWD")], "OLDPWD=");
	chdir(tmp);
	free(tmp);
	i = get_env_indice(ms, "OLDPWD");
	free(ms->env[i]);
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
		if (chdir(ms->lst->content) == -1)
		{
			error = ft_strjoin("minishell: cd: ", ms->lst->content, \
		NULL, 0b000);
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
