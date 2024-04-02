/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:29:20 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/02 12:16:15 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	check_export(char *var)
{
	int	i;

	i = 1;
	if (var[i - 1] == '-')
		return (-1);
	if (!ft_isalpha(var[i - 1]) && var[i - 1] != '_')
		return (0);
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_' || var[i] == '\\'))
	{
		if (var[i] == '\\' && var[i + 1] && (ft_isalnum(var[i + 1]) \
			|| var[i + 1] == '_'))
			i++;
		else if (var[i] != '\\')
			i++;
		else
			return (0);
	}
	if (((int)ft_strlen(var) != i + 1) && var[i] == '+' && var[i + 1] == '=')
		return (2);
	if (var[i] != '\0' && var[i] != '=')
		return (0);
	return (1);
}

static char	**fill_export_env(t_ms *ms, int	*b, int var_status)
{
	int		i;
	char	**export_env;

	i = 0;
	export_env = ft_calloc(ft_tablen(ms->env) + 2, sizeof(char *));
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
	if (!ft_strchr(ms->lst->next->content, '='))
		return (NULL);
	export_env = fill_export_env(ms, &b, var_status);
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

static int	print_export(char **tab)
{
	int		i;
	char	*tmp;
	char	*str;

	i = 0;
	while (i < ft_tablen(tab))
	{
		tmp = ft_strrev(tab[i]);
		str = ft_strjoin(ft_strrev(ft_strchr(tmp, '=')), \
		ft_strchr(tab[i], '=') + 1, "\"", 0b001);
		free(tmp);
		tmp = ft_strjoin(str, "\"", NULL, 0b001);
		ft_dprintf(1, "declare -x %s\n", tmp);
		free(tmp);
		i++;
	}
	return (1);
}

void	export(t_ms *ms)
{
	char	**new_env;
	int		var_status;

	if (!ms->lst->next || ms->lst->next->content[0] == '\0')
	{
		new_env = ft_sort_string_tab(ms->env);
		print_export(new_env);
		ft_free_tab(new_env);
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
	if (new_env)
	{
		ft_free_tab(ms->env);
		ms->env = new_env;
	}
}
