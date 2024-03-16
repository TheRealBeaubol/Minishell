/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:29:20 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/16 20:50:32 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	**fill_export_env(t_ms *ms, int	*b, char **export_env, \
	int var_status)
{
	int	i;

	i = 0;
	while (ms->env[i])
	{
		if (!ft_strncmp(ms->lst->next->content, ms->env[i], \
			ft_strlen_tr(ms->env[i], '=') - var_status + 2))
		{
			if (var_status == 2)
				export_env[i] = ft_strjoin(ms->env[i], \
					ft_strchr(ms->lst->next->content, '=') + 1, NULL, 0b000);
			else
				export_env[i] = ft_strdup(ms->lst->next->content);
			*b = 1;
		}
		else
			export_env[i] = ft_strdup(ms->env[i]);
		i++;
	}
	return (export_env);
}

static char	**feed_env_p(t_ms *ms, int var_status)
{
	char	**export_env;
	int		i;
	int		b;
	char	*tmp;

	b = 0;
	i = 0;
	export_env = ft_calloc(ft_tablen(ms->env) + 2, sizeof(char *));
	export_env = fill_export_env(ms, &b, export_env, var_status);
	i = ft_tablen(ms->env);
	if (!b)
	{
		if (var_status == 2)
		{
			tmp = ft_strrev(ms->lst->next->content);
			export_env[i++] = ft_strjoin(ft_strrev(ft_strchr(tmp, '+') + 1), \
				ft_strchr(ms->lst->next->content, '+') + 1, NULL, 0b001);
			free(tmp);
		}
		else
			export_env[i++] = ft_strdup(ms->lst->next->content);
	}
	export_env[i] = 0;
	return (export_env);
}

static int	print_export(t_ms *ms, int *indice)
{
	unsigned long	i;
	unsigned long	len;
	char			*tmp;
	char			*str;
	int				pos;
	int				var;

	i = 0;
	len = sizeof(ms->env);
	pos = 0;
	while (i < len)
	{
		var = 0;
		while (indice[var] != pos)
			var++;
		tmp = ft_strrev(ms->env[var]);
		str = ft_strjoin(ft_strrev(ft_strchr(tmp, '=')), \
		ft_strchr(ms->env[var], '=') + 1, "\"", 0b011);
		free(tmp);
		tmp = ft_strjoin(str, "\"", NULL, 0b001);
		ft_dprintf(1, "declare -x %s\n", tmp);
		free(tmp);
		pos++;
		i++;
	}
	return (1);
}

void	export(t_ms *ms)
{
	char	**new_env;
	int		var_status;
	int		*indice;

	if (!ms->lst->next || ms->lst->next->content[0] == '\0')
	{
		indice = ft_sort_string_tab(ms->env);
		print_export(ms, indice);
		return ;
	}
	var_status = check_export(ms->lst->next->content);
	if (var_status < 1)
	{
		if (!var_status)
			g_exit = 1;
		else
			g_exit = 2;
		return ;
	}
	new_env = feed_env_p(ms, var_status);
	ft_free_tab(ms->env);
	ms->env = new_env;
}
