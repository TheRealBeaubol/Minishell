/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:29:20 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/11 11:14:21 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	**fill_export_env(t_ms *ms, int	*b, int var_status, char *content)
{
	int		i;
	char	**export_env;

	i = 0;
	export_env = ft_calloc(ft_tablen(ms->env) + 2, sizeof(char *));
	if (!export_env)
		return (NULL);
	while (ms->env[i])
	{
		if (!ft_strncmp(content, ms->env[i], \
			ft_strlen_tr(ms->env[i], '=') - var_status + 2))
		{
			if (var_status == 2)
				export_env[i] = ft_strjoin(ms->env[i], \
					ft_strchr(content, '=') + 1, NULL, 0b000);
			else
				export_env[i] = ft_strdup(content);
			*b = 1;
		}
		else
			export_env[i] = ft_strdup(ms->env[i]);
		i++;
	}
	return (export_env);
}

static int	handle_wrong_args(char *content)
{
	int	i;

	i = 0;
	if (!ft_isalpha(content[i]) && content[i] != '_')
	{
		ft_dprintf(2, "minishell: export: `%s': not a \
valid identifier\n", content);
		g_exit = 1;
		return (1);
	}
	i++;
	while (content[i])
	{
		if (ft_isalnum(content[i]) || content[i] == '_')
			i++;
		else
		{
			ft_dprintf(2, "minishell: export: `%s': not a \
valid identifier\n", content);
			g_exit = 1;
			return (1);
		}
	}
	return (0);
}

static char	**feed_env_p(t_ms *ms, int var_status, char *content)
{
	char	**export_env;
	int		i;
	int		b;
	char	*tmp;

	if (!ft_strchr(content, '='))
	{
		b = handle_wrong_args(content);
		if (b)
			return (ms->env);
	}
	b = 0;
	export_env = fill_export_env(ms, &b, var_status, content);
	i = ft_tablen(ms->env);
	if (!b)
	{
		if (var_status == 2)
		{
			tmp = ft_strrev(content);
			export_env[i++] = ft_strjoin(ft_strrev(ft_strchr(tmp, '+') + 1), \
				ft_strchr(content, '+') + 1, NULL, 0b001);
			free(tmp);
		}
		else
			export_env[i++] = ft_strdup(content);
	}
	export_env[i] = 0;
	return (export_env);
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
	char	**new_env;
	int		var_status;
	int		i;

	i = 1;
	var_status = 0;
	if (!cmdlst->param[i])
		print_export(ms);
	while (cmdlst->param[i])
	{
		if (ft_strchr(cmdlst->param[i], '='))
		{
			var_status = check_export(cmdlst->param[i]);
			if (var_status < 1)
				g_exit = var_status + 1 + (var_status * -2);
			if (var_status < 1)
				return ;
		}
		new_env = feed_env_p(ms, var_status, cmdlst->param[i]);
		if (new_env)
			ft_free_tab(ms->env);
		if (new_env)
			ms->env = new_env;
		i++;
	}
}
