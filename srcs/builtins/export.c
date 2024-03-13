/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:29:20 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/13 21:48:40 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	**feed_env_p(t_ms *ms)
{
	char	**export_env;
	int		i;

	i = 0;
	export_env = malloc(sizeof(char *) * (ft_strstr_len(ms->env) + 2));
	while (ms->env[i])
	{
		export_env[i] = ft_strdup(ms->env[i]);
		i++;
	}
	export_env[i++] = ft_strdup(ms->lst->next->content);
	export_env[i] = 0;
	return (export_env);
}

void	export(t_ms *ms)
{
	char	**new_env;

	new_env = feed_env_p(ms);
	ft_free_tab(ms->env);
	ms->env = new_env;
}
