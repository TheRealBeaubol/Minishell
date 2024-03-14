/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:10:52 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/14 17:34:46 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int	g_exit;

char	*handle_exit_env_var(t_ms *ms, char *var_name, char *end_str, int i)
{
	char	*input;
	int		j;

	j = -1;
	input = ft_calloc((ft_strlen(end_str) + ft_strlen(var_name) + i + 1), \
sizeof(char));
	while (++j != i)
		input[j] = ms->input[j];
	input = ft_strjoin(input, var_name, NULL, 0b011);
	if (end_str)
		input = ft_strjoin(input, end_str, NULL, 0b001);
	free(ms->input);
	return (input);
}

void	replace_var(t_ms *ms, int *i)
{
	char	*var_name;
	char	*end_str;

	if (ft_iswhitespace(ms->input[*i + 1]))
	{
		(*i)++;
		return ;
	}
	var_name = get_var_name(ms, *i);
	if (!var_name)
	{
		(*i)++;
		return ;
	}
	end_str = get_end_str(ms, var_name, *i);
	if (var_name && (var_name[ft_strlen(var_name) - 1] != '=' \
		&& ms->input[*i + 1] != '?'))
		ms->input = ft_strjoin(var_name, end_str, NULL, 0b001);
	else
	{
		if (ms->input[*i + 1] == '?')
			ms->input = handle_exit_env_var(ms, var_name, end_str, *i);
		else
		{
			ms->input = get_new_input(ms, *i, end_str, var_name);
			free(var_name);
			if (ms->input[*i] == '\0')
				return ;
		}
	}
	*i = ft_strlen(ms->input) - ft_strlen(end_str);
	free(end_str);
}

static int	handle_dquote_envvar(t_ms *ms, int i)
{
	int	j;

	j = i + 1;
	while (ms->input[j] != '"')
	{
		if (ms->input[j] == '\0')
			return (-1);
		if (ms->input[j] == '\'')
			i++;
		if (ms->input[j] == '$' && (ft_iswhitespace(ms->input[j + 1]) \
	|| ms->input[j + 1] == '"'))
			j++;
		else if (ms->input[j] == '$' && !ft_iswhitespace(ms->input[j + 1]))
			return (i + 1);
		else
			j++;
	}
	return (j + 1);
}

static int	handle_squote_envvar(t_ms *ms, int i)
{
	i++;
	while (ms->input[i] != '\'')
	{
		if (ms->input[i] == '\0')
			return (-1);
		i++;
	}
	return (i + 1);
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
			replace_var(ms, &i);
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
