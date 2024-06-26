/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:29:20 by mhervoch          #+#    #+#             */
/*   Updated: 2024/05/01 00:20:11 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	check_export(char *var)
{
	char	*tmp;

	tmp = var;
	if (!var)
		return (0);
	if (*var == '=')
		return (0);
	if (ft_isdigit(var[0]))
		return (0);
	tmp++;
	while (*tmp && (ft_isalnum(*tmp) || *tmp == '_'))
		tmp++;
	return (!ft_strncmp(tmp, "=", 1) || !ft_strncmp(tmp, "+=", 2) \
		|| !ft_strncmp(tmp, "\0", 1));
}

static void	edit_env(t_ms *ms, char *var, char *param, int is_add)
{
	int	j;

	j = get_env_indice(ms, var);
	if (is_add)
	{
		if (ms->env[j][ft_strlen(var)] != '=')
			ms->env[j] = ft_strjoin(ms->env[j], "=", NULL, 0b001);
		ms->env[j] = ft_strjoin(ms->env[j], param + \
			ft_strlen(var) + 2, NULL, 0b001);
	}
	else
	{
		if (ft_strchr(param, '='))
		{
			free(ms->env[j]);
			ms->env[j] = ft_strdup(param);
		}
	}
}

static void	add_to_env(char *var, t_ms *ms, char *param, int is_add)
{
	char	*tmp;

	if (is_in_env(var, ms))
		edit_env(ms, var, param, is_add);
	else
	{
		if (ft_strchr(param, '+'))
		{
			tmp = ft_calloc(ft_strlen(param) + 1, sizeof(char));
			ft_strlcpy(tmp, param, ft_strlen_tr(param, '+') + 1);
			ft_strlcpy(tmp + ft_strlen(tmp), param + ft_strlen(tmp) + 1, \
				ft_strlen(param) - ft_strlen(tmp) + 1);
			ms->env = ft_join_tab(ms->env, tmp);
			free(tmp);
		}
		else
			ms->env = ft_join_tab(ms->env, param);
	}
}

static void	print_export(t_ms *ms)
{
	int		i;
	char	*tmp;
	char	*str;
	char	**tab;

	i = 0;
	tab = ft_sort_string_tab(ms->env);
	while (i < ft_tablen(tab))
	{
		if (ft_strchr(tab[i], '='))
		{
			str = ft_strjoin(ft_substr(tab[i], 0, ft_strlen_tr(tab[i], \
		'=') + 1), tab[i] + ft_strlen_tr(tab[i], '=') + 1, "\"", 0b001);
			tmp = ft_strjoin(str, "\"", NULL, 0b001);
			ft_dprintf(1, "declare -x %s\n", tmp);
			free(tmp);
		}
		else
			ft_dprintf(1, "declare -x %s\n", tab[i]);
		i++;
	}
	ft_free_tab(tab);
}

void	export(t_cmdlist *cmdlst, t_ms *ms)
{
	int		i;
	char	*var;
	int		is_add;

	i = 1;
	if (!cmdlst->param[i])
		print_export(ms);
	while (cmdlst->param[i])
	{
		is_add = 0;
		if (!check_export(cmdlst->param[i]))
		{
			ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n", \
				cmdlst->param[i]);
			g_exit = 1;
			i++;
			continue ;
		}
		var = get_name(cmdlst->param[i], &is_add);
		add_to_env(var, ms, cmdlst->param[i], is_add);
		free(var);
		i++;
	}
}
