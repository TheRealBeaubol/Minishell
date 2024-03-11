/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:18:20 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/11 21:22:07 by lboiteux         ###   ########.fr       */
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

void	unset(t_ms *ms, char *var)
{
	int	indice;

	indice = get_env_indice(ms, var);
	printf("%s\n", ms->env[indice]);
	ms->env[indice] = ft_strjoin(get_var(ms, indice), "=", NULL, 0b000);
	printf("%s\n", ms->env[indice]);
}
