/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:10:52 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/27 17:16:11 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_var_name(t_ms *ms, int i)
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
}

static char	*get_end_str(t_ms *ms, char *var_name, int i)
{
	char	*end_str;
	int		j;

	j = 0;
	end_str = ft_calloc((ft_strlen(ms->input) - i), sizeof(char));
	if (var_name && (var_name[ft_strlen(var_name) - 1] == '='))
		i += ft_strlen(var_name);
	else if (var_name)
		i += ft_strlen(var_name) + 2;
	else
		i++;
	if (ms->input[i] == '\0')
	{
		free(end_str);
		return (NULL);
	}
	while (ms->input[i] != '\0')
	{
		end_str[j] = ms->input[i];
		i++;
		j++;
	}
	end_str[j] = '\0';
	return (end_str);
}

static char	*get_new_input(t_ms *ms, int i, char *end_str, char *var_name)
{
	char	*input;
	char	*var_env;
	int		j;

	j = -1;
	var_env = get_env(ms->env, var_name);
	input = ft_calloc((ft_strlen(end_str) + ft_strlen(var_env) + i + 1), \
sizeof(char));
	while (++j != i)
		input[j] = ms->input[j];
	input = ft_strjoin(input, var_env, NULL, 0b011);
	if (end_str)
		input = ft_strjoin(input, end_str, NULL, 0b001);
	free(ms->input);
	return (input);
}

int	replace_var(t_ms *ms, int i)
{
	char	*var_name;
	char	*end_str;

	if (ft_iswhitespace(ms->input[i + 1]))
		return (i + 1);
	var_name = get_var_name(ms, i);
	if (!var_name)
		return (i + 1);
	end_str = get_end_str(ms, var_name, i);
	if (var_name && var_name[ft_strlen(var_name) - 1] != '=')
		ms->input = ft_strjoin(var_name, end_str, NULL, 0b001);
	else
	{
		ms->input = get_new_input(ms, i, end_str, var_name);
		free(var_name);
		if (ms->input[i] == '\0')
			return (i);
	}
	i = ft_strlen(ms->input) - ft_strlen(end_str);
	free(end_str);
	return (i);
}

int	parse_env(t_ms *ms)
{
	int		i;

	i = 0;
	while (ms->input[i] != '\0')
	{
		if (ms->input[i] == '"' && ms->input[i + 1] != '\0')
			i = handle_dquote_envvar(ms, i);
		else if (ms->input[i] == '\'')
			i = handle_squote_envvar(ms, i);
		else if (ms->input[i] == '$')
		{
			if (ms->input[i + 1] == '?')
				handle_exit_envvar(ms, &i);
			else
				i = replace_var(ms, i);
			if (ms->input[0] == '\0')
				return (1);
		}
		else
			i++;
		if (i == -1)
			return (1);
	}
	return (0);
}
