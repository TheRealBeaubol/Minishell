/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:29:20 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/12 17:54:32 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	add_to_env(char *var, t_ms *ms, char *param, int is_add)
{
	int		j;

	if (is_in_env(var, ms))
	{
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
			if (ms->env[j][ft_strlen(var)] != '=')
			{
				free(ms->env[j]);
				ms->env[j] = ft_strdup(param);
			}
		}
	}
	else
		ms->env = ft_join_tab(ms->env, param);
}

char	*get_name(char *var, int *is_add)
{
	char	*name;
	int		len;

	len = ft_strlen_tr(var, '=');
	if (len == (int)ft_strlen(var))
		return (ft_strdup(var));
	else
	{
		if (var[len - 1] == '+')
		{
			*is_add = 1;
			len -= 1;
		}
		name = ft_substr(var, 0, len);
	}
	return (name);
}

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
