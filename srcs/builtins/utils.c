/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:16:04 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/16 19:41:44 by lboiteux         ###   ########.fr       */
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

char	*get_env(char **env, char *var_name)
{
	int		i;
	char	*cut_str;

	i = 0;
	if (!env || !*env || !var_name)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], var_name, ft_strlen(var_name)))
		i++;
	if (!env || !env[i])
		return (NULL);
	cut_str = ft_strcut(env[i], var_name);
	return (cut_str);
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

void	free_exec(t_ms *ms, int is_fork, int err_code)
{
	if (is_fork == 1)
	{
		printf("Command not found\n");
		rl_clear_history();
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
		g_exit = WEXITSTATUS(err_code);
		ft_free_tab(ms->data->cmd);
		ms->data->cmd = NULL;
		free(ms->path->str);
		ft_free_list(&ms->lst);
		free(ms->prompt);
		ms->prompt = get_prompt(ms);
	}
}
