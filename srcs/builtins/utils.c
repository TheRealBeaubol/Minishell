/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:16:04 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/12 17:51:11 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int	get_env_indice(t_ms *ms, char *var)
{
	int	i;

	i = 0;
	while (ms->env[i] && ft_strncmp(ms->env[i], var, ft_strlen(var)))
		i++;
	if (!ms->env[i])
		return (-1);
	return (i);
}

int	get_exit_code(int err_code)
{
	if (!WIFEXITED(err_code) && WCOREDUMP(err_code))
	{
		ft_dprintf(2, "Quit (core dumped)\n");
		return (131);
	}
	if (WTERMSIG(err_code) == 2)
	{
		ft_dprintf(2, "\n");
		return (130);
	}
	return (WEXITSTATUS(err_code));
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

void	free_exec(t_ms *ms, int is_fork, int err_code)
{
	if (is_fork == 1)
	{
		ft_dprintf(2, "Command not found\n");
		rl_clear_history();
		free(ms->input);
		ms->input = NULL;
		free(ms->prompt);
		free(ms->path->str);
		ft_free_tab(ms->env);
		ft_free_tab(ms->data->cmd);
		ft_free_list(&ms->lst);
		g_exit = 127;
		exit(g_exit);
	}
	else if (!is_fork)
	{
		g_exit = get_exit_code(err_code);
		ft_free_tab(ms->data->cmd);
		ms->data->cmd = NULL;
		free(ms->path->str);
		ft_free_list(&ms->lst);
		free(ms->prompt);
		ms->prompt = get_prompt(ms);
	}
}
