/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:18:20 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/13 12:05:09 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	**feed_env(t_ms *ms, int unset)
{
	int		i;
	int		j;
	char	**unset_env;

	unset_env = ft_calloc(ft_tablen(ms->env), sizeof(char *));
	if (!unset_env)
		return (NULL);
	i = 0;
	j = 0;
	while (ms->env[i])
	{
		if (i != unset)
			unset_env[j++] = ft_strdup(ms->env[i]);
		i++;
	}
	unset_env[j] = NULL;
	return (unset_env);
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

void	unset(t_cmdlist *cmdlst, char *var, t_ms *ms)
{
	int		indice;
	char	**new_env;

	if (!cmdlst->param[1])
		return ;
	if (var[0] == '-')
		g_exit = 2;
	indice = get_env_indice(ms, cmdlst->param[1]);
	if (indice == -1)
		return ;
	new_env = feed_env(ms, indice);
	if (new_env)
	{
		ft_free_tab(ms->env);
		ms->env = new_env;
	}
	else
	{
		ft_dprintf(2, "malloc error: nothing done\n");
		return ;
	}
}
