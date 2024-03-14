/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:44:17 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/14 01:23:47 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int	g_exit;

static void	edit_env(t_ms *ms)
{
	int	i;

	i = get_env_indice(ms, "PWD");
	free(ms->env[i]);
	ms->env[i] = ft_strjoin("PWD=", get_cwd(), NULL, 0b010);
}

static void	old_pwd(t_ms *ms)
{
	int		i;

	i = get_env_indice(ms, "OLDPWD");
	free(ms->env[i]);
	ms->env[i] = \
		ft_strjoin("OLDPWD=", get_cwd(), NULL, 0b010);
}

static void	handle_flag(t_ms *ms)
{
	char	*old_pwd;
	char	*tmp;
	int		i;

	old_pwd = ft_strjoin("OLDPWD=", get_cwd(), NULL, 0b010);
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
			error = ft_strjoin("minishell: cd: ", tmp->content, \
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
