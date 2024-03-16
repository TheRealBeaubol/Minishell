/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:18:20 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/16 16:45:10 by lboiteux         ###   ########.fr       */
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

void	unset(t_ms *ms, char *var)
{
	int		indice;
	char	**new_env;

	if (!ms->lst->next)
		return ;
	free(var);
	var = ms->lst->next->content;
	indice = get_env_indice(ms, var);
	if (indice == -1)
		return ;
	new_env = feed_env(ms, indice);
	ft_free_tab(ms->env);
	ms->env = new_env;
}
