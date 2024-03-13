/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:18:20 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/13 21:26:50 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	get_range(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
		i++;
	return (i);
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

char	*get_var(t_ms *ms, int indice)
{
	char	*var;

	var = ft_strdup_range(ms->env[indice], 0, get_range(ms->env[indice]));
	return (var);
}

int	ft_strstr_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**feed_env(t_ms *ms, int unset)
{
	int		i;
	char	**unset_env;
	
	unset_env = malloc(sizeof(char *) * ft_strstr_len(ms->env));
	i = 0;
	while (ms->env[i])
	{
		if (i != unset)
			unset_env[i] = ft_strdup(ms->env[i]);
		i++;
	}
	return (unset_env);
}

void	unset(t_ms *ms, char *var)
{
	int		indice;
	char	**new_env;
	
	indice = get_env_indice(ms, var);
	new_env = feed_env(ms, indice);
	ft_free_tab(ms->env);
	ms->env = new_env;
}
