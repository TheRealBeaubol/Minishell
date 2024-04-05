/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:18:20 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/04 16:10:34 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	**feed_env(t_ms *ms, int unset)
{
	int		i;
	int		j;
	char	**unset_env;

	unset_env = malloc(sizeof(char *) * ft_tablen(ms->env));
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

void	unset(t_ms *ms, char *var)
{
	int		indice;
	char	**new_env;

	if (!ms->lst->next)
		return ;
	var = ms->lst->next->content;
	if (var[0] == '-')
		g_exit = 2;
	indice = get_env_indice(ms, var);
	if (indice == -1)
		return ;
	new_env = feed_env(ms, indice);
	ft_free_tab(ms->env);
	ms->env = new_env;
}
