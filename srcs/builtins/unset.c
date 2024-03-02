/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:18:20 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/02 01:32:34 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../includes/header.h"

int	get_range(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
		i++;
	return (i + 1);
}

int	get_env_indice(t_ms *ms, char *var)
{
	int	i;

	i = 0;
	while (ms->env[i] && ft_strncmp(ms->env[i] + get_range(ms->env[i]), var, ft_strlen(var)))
		i++;
	return (i);
}

char	*get_var(t_ms *ms, int indice)
{
	char	*var;

	var = ft_strdup_range(ms->env[indice], 0, 4);
	return(ft_strjoin(var, "="));
}

void	unset(t_ms *ms, char *var)
{
	int	indice;

	indice = get_env_indice(ms, var);
	printf("%s\n", ms->env[indice]);
	ms->env[indice] = ft_strdup_range(ft_strjoin(get_var(ms, indice), "="), 0, 5);
	printf("%s\n", ms->env[indice]);
}
