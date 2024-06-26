/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:44:17 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/30 23:39:09 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	edit_pwd(t_ms *ms, char *str1, char *str2)
{
	int		i;
	char	*tmp;

	i = get_env_indice(ms, str1);
	tmp = ft_strjoin(str2, get_cwd(0), NULL, 0b010);
	if (i != -1)
	{
		free(ms->env[i]);
		ms->env[i] = ft_strdup(tmp);
	}
	free(tmp);
}

static void	handle_flag(t_ms *ms)
{
	char	*old_pwd;
	char	*tmp;
	int		i;

	old_pwd = ft_strjoin("OLDPWD=", get_cwd(0), NULL, 0b010);
	i = get_env_indice(ms, "OLDPWD");
	if (i != -1)
	{
		tmp = ft_strcut(ms->env[i], "OLDPWD=");
		chdir(tmp);
		free(tmp);
		free(ms->env[i]);
		ms->env[i] = old_pwd;
		return ;
	}
	ft_dprintf(2, "minishell: cd: OLDPWD not set\n");
	free(old_pwd);
}

static int	handle_no_args(t_cmdlist *cmdlst, t_ms *ms)
{
	char	*home;

	if (!cmdlst->param[1])
	{
		edit_pwd(ms, "OLDPWD", "OLDPWD=");
		home = get_env(ms->env, "HOME");
		if (!home || chdir(home + 1) == -1)
		{
			free(home);
			g_exit = 1;
			if (!home)
				ft_dprintf(2, "minishell: cd: HOME not set\n");
			else
				ft_dprintf(2, "minishell: cd: permission denied\n");
			return (0);
		}
		free(home);
		free(ms->prompt);
		ms->prompt = get_prompt(ms);
		edit_pwd(ms, "PWD", "PWD=");
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
	if (cmdlst->param[2] && cmdlst->param[2][0] != '\0')
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
		edit_pwd(ms, "OLDPWD", "OLDPWD=");
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
	edit_pwd(ms, "PWD", "PWD=");
	g_exit = 0;
	return (1);
}
