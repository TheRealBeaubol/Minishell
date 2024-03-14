/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:29:20 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/14 01:24:39 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int	g_exit;

int	ft_strlen_tr(char *str, char c)
{
	char	*tmp;

	tmp = str;
	if (!str)
		return (0);
	while (*tmp && *tmp != c)
		tmp++;
	return (tmp - str);
}

char	**feed_env_p(t_ms *ms)
{
	char	**export_env;
	int		i;
	int		b;

	b = 0;
	i = 0;
	export_env = malloc(sizeof(char *) * (ft_strstr_len(ms->env) + 2));
	while (ms->env[i])
	{
		if (!strncmp(ms->lst->next->content, ms->env[i], \
		ft_strlen_tr(ms->env[i], '=')))
		{
			export_env[i] = ft_strdup(ms->lst->next->content);
			b = 1;
		}
		else
			export_env[i] = ft_strdup(ms->env[i]);
		i++;
	}
	if (!b)
		export_env[i++] = ft_strdup(ms->lst->next->content);
	export_env[i] = 0;
	return (export_env);
}

void	e_xport(t_ms *ms)
{
	char	**new_env;

	new_env = feed_env_p(ms);
	ft_free_tab(ms->env);
	ms->env = new_env;
}
