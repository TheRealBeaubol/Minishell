/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:50:25 by mhervoch          #+#    #+#             */
/*   Updated: 2024/05/01 01:38:49 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_name(char *var, int *is_add)
{
	char	*name;
	int		len;

	len = ft_strlen_tr(var, '=');
	if (len == (int)ft_strlen(var))
		return (ft_strdup(var));
	else
	{
		if (var[len - 1] == '+')
		{
			*is_add = 1;
			len -= 1;
		}
		name = ft_substr(var, 0, len);
	}
	return (name);
}

int	is_in_env(char *var, t_ms *ms)
{
	int		i;
	int		len;
	char	*env;

	i = 0;
	while (ms->env[i])
	{
		len = ft_strlen_tr(ms->env[i], '=');
		if (len != (int)ft_strlen(ms->env[i]))
			env = ft_substr(ms->env[i], 0, len);
		else
			env = ft_strdup(ms->env[i]);
		if (!ft_strncmp(env, var, ft_strlen(var)))
		{
			free(env);
			return (1);
		}
		free(env);
		i++;
	}
	return (0);
}

char	*get_cwd(int i)
{
	char	cwd[65538];

	if (getcwd(cwd, sizeof(cwd)))
	{
		if (i == 1)
		{
			ft_dprintf(1, "%s\n", cwd);
			return (NULL);
		}
		return (ft_strdup(cwd));
	}
	return (NULL);
}

int	is_builtin(char *cmd)
{
	return (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "pwd", 4) || \
		!ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4) || \
		!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "export", 7) || \
		!ft_strncmp(cmd, "exit", 5));
}

void	exec_builtin(t_cmdlist *cmdlst, char *cmd, t_ms *ms, int status)
{
	if (!ft_strncmp(cmd, "cd", 3))
		change_directory(cmdlst, ms);
	else if (!ft_strncmp(cmd, "pwd", 4))
	{
		g_exit = 0;
		get_cwd(1);
	}
	else if (!ft_strncmp(cmd, "unset", 6))
		unset(cmdlst, ms);
	else if (!ft_strncmp(cmd, "env", 4))
		env(cmdlst, ms);
	else if (!ft_strncmp(cmd, "echo", 5))
		echo(cmdlst);
	else if (!ft_strncmp(cmd, "export", 7))
		export(cmdlst, ms);
	else if (!ft_strncmp(cmd, "exit", 5))
		exit_function(cmdlst, ms, status);
}
