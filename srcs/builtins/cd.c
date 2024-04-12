/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:44:17 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/12 12:24:46 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	edit_pwd(t_ms *ms, int condition)
{
	int	i;

	if (condition == 0)
	{
		i = get_env_indice(ms, "PWD");
		free(ms->env[i]);
		ms->env[i] = ft_strjoin("PWD=", get_cwd(0), NULL, 0b010);
	}
	else
	{
		i = get_env_indice(ms, "OLDPWD");
		free(ms->env[i]);
		ms->env[i] = \
			ft_strjoin("OLDPWD=", get_cwd(0), NULL, 0b010);
	}
}

static void	handle_flag(t_ms *ms)
{
	char	*old_pwd;
	char	*tmp;
	int		i;

	old_pwd = ft_strjoin("OLDPWD=", get_cwd(0), NULL, 0b010);
	tmp = ft_strcut(ms->env[get_env_indice(ms, "OLDPWD")], "OLDPWD=");
	chdir(tmp);
	free(tmp);
	i = get_env_indice(ms, "OLDPWD");
	free(ms->env[i]);
	ms->env[i] = old_pwd;
}

static int	handle_no_args(t_cmdlist *cmdlst, t_ms *ms)
{
	char	*home;

	if (!cmdlst->param[1])
	{
		edit_pwd(ms, 1);
		home = get_env(ms->env, "HOME");
		if (!home || chdir(home + 1) == -1)
		{
			free(home);
			g_exit = 1;
			if (!home)
				perror("minishell: cd: HOME not set\n");
			else
				perror("minishell: cd: permission denied\n");
			return (0);
		}
		free(home);
		free(ms->prompt);
		ms->prompt = get_prompt(ms);
		edit_pwd(ms, 0);
		return (0);
	}
	return (1);
}

static int	handle_wrong_args(t_cmdlist *cmdlst, t_ms *ms)
{
	int	i;

	i = handle_no_args(cmdlst, ms);
	if (i == 0)
		return (0);
	if (cmdlst->param[2])
	{
		g_exit = 1;
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (0);
	}
	return (1);
}

int	change_directory(t_cmdlist *cmdlst, t_ms *ms)
{
	char	*error;

	if (!handle_wrong_args(cmdlst, ms))
		return (0);
	if (!ft_strncmp(cmdlst->param[1], "-", 2))
		handle_flag(ms);
	else
	{
		edit_pwd(ms, 1);
		if (chdir(cmdlst->param[1]) == -1)
		{
			g_exit = 1;
			error = ft_strjoin("minishell: cd: ", \
				cmdlst->param[1], NULL, 0b000);
			perror(error);
			free(error);
			return (0);
		}
	}
	free(ms->prompt);
	ms->prompt = get_prompt(ms);
	edit_pwd(ms, 0);
	return (1);
}
