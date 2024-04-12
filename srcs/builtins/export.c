/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:29:20 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/12 13:14:00 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	print_export(t_ms *ms)
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
			tmp = ft_strrev(tab[i]);
			str = ft_strjoin(ft_strrev(ft_strchr(tmp, '=')), \
			ft_strchr(tab[i], '=') + 1, "\"", 0b001);
			free(tmp);
			tmp = ft_strjoin(str, "\"", NULL, 0b001);
			ft_dprintf(1, "declare -x %s\n", tmp);
			free(tmp);
		}
		else
			ft_dprintf(1, "declare -x %s\n", tab[i]);
		i++;
	}
	ft_free_tab(tab);
	return (1);
}

int	check_export(char *var)
{
	char	*tmp;

	tmp = var;
	if (!var)
		return (0);
	if (ft_isdigit(var[0]))
		return (0);
	tmp++;
	while (*tmp && (ft_isalnum(*tmp) || *tmp == '_'))
		tmp++;
	return (!ft_strncmp(tmp, "=", 1) || !ft_strncmp(tmp, "+=", 2) \
		|| !ft_strncmp(tmp, "\0", 1));
}

int	is_in_env(char *var, t_ms *ms)
{
	int		i;
	int		len;
	char	*env;

	i = 0;
	while (ms->env[i])
	{
		len = ft_strlen_tr(ms->env[i], '=');
		if (len != (int)ft_strlen(ms->env[i]))
			env = ft_substr(ms->env[i], 0, len);
		else
			env = ft_strdup(ms->env[i]);
		if (!ft_strncmp(env, var, ft_strlen(var)))
		{
			free(env);
			return (1);
		}
		free(env);
		i++;
	}
	return (0);
}

void	export(t_cmdlist *cmdlst, t_ms *ms)
{
	int		i;
	int		j;
	char	*var;

	i = 1;
	if (!cmdlst->param[i])
		print_export(ms);
	while (cmdlst->param[i])
	{
		if (!check_export(cmdlst->param[i]))
		{
			ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n", \
				cmdlst->param[i]);
			g_exit = 1;
			i++;
			continue ;
		}
		j = ft_strlen_tr(cmdlst->param[i], '=');
		if (j != (int)ft_strlen(cmdlst->param[i]))
			var = ft_substr(cmdlst->param[i], 0, j);
		else
			var = ft_strdup(cmdlst->param[i]);
		if (is_in_env(var, ms))
		{
			j = get_env_indice(ms, var);
			if (var[ft_strlen(var) - 1] == '+')
				ms->env[j] = ft_strjoin(ms->env[j], cmdlst->param[i] + \
					ft_strlen(var), NULL, 0b001);
			else
			{
				free(ms->env[j]);
				ms->env[j] = ft_strdup(cmdlst->param[i]);
			}
		}
		else
			ms->env = ft_join_tab(ms->env, cmdlst->param[i]);
		free(var);
		i++;
	}
}
