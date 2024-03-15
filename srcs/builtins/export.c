/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:29:20 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/15 19:51:15 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

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
	export_env = ft_calloc(ft_strstr_len(ms->env) + 2, sizeof(char *));
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

int	print_export(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->env[i])
	{
		ft_dprintf(1, "declare -x %s\n", ms->env[i]);
		i++;
	}
	return (1);
}

/*char	*get_var_name(t_ms *ms, int i)
{
	char	*str;
	int		stock_i;
	int		malloc_count;
	int		j;

	j = 0;
	malloc_count = 0;
	stock_i = i;
	i++;
	if (ms->input[i] == '?')
		return (ft_itoa(g_exit));
	if (ft_isdigit(ms->input[i]))
		return (NULL);
	if (!ft_isalpha(ms->input[i]) && ms->input[i] != '_')
		return (NULL);
	while (ms->input[stock_i++] && (ft_isalnum(ms->input[stock_i]) || \
ms->input[stock_i] == '_'))
		malloc_count++;
	str = ft_calloc((malloc_count + 3), sizeof(char));
	while (ft_isalnum(ms->input[i]) || ms->input[i] == '_')
		str[j++] = ms->input[i++];
	str[j] = '=';
	str[++j] = '\0';
	return (str);
}*/
int	check_export(char *var)
{
	int	i;

	i = 1;
	if (var[i - 1] == '-')
		return (-1);
	if (!ft_isalpha(var[i - 1]) && var[i - 1] != '_')
		return (0);
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_' || var[i] == '\\'))
	{
		if (var[i] == '\\' && var[i + 1] && (ft_isalnum(var[i + 1]) || var[i + 1] == '_'))
			i++;
		else if (var[i] != '\\')
			i++;
		else
			return (0);
	}
	if (var[i] != '\0' && var[i] != '=')
		return (0);
	return (1);
}

void	export(t_ms *ms)
{
	char	**new_env;
	int		var_status;

	if (!ms->lst->next || ms->lst->next->content[0] == '\0')
	{
		print_export(ms);
		return ;
	}
	var_status = check_export(ms->lst->next->content);
	if (var_status != 1)
	{
		if (!var_status)
			g_exit = 1;
		else
			g_exit = 2;
		return ;
	}
	new_env = feed_env_p(ms);
	ft_free_tab(ms->env);
	ms->env = new_env;
}
