/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:10:52 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/15 01:48:48 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int	g_exit;

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
	if (var_name && var_name[ft_strlen(var_name) - 1] != '=')
		ms->input = ft_strjoin(var_name, end_str, NULL, 0b001);
	else
	{
		ms->input = get_new_input(ms, *i, end_str, var_name);
		free(var_name);
		if (ms->input[*i] == '\0')
			return ;
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

void	handle_exit_envvar(t_ms *ms, int *i)
{
	char	*exit_code;
	char	*new_input;
	int		len;

	exit_code = ft_itoa(g_exit);
	new_input = ft_calloc((ft_strlen(ms->input) \
	+ ft_strlen(exit_code) - 1), sizeof(char));
	if (!new_input)
		return ;
	len = ft_strchr(ms->input, '$') - ms->input;
	ft_strncat(new_input, ms->input, len);
	ft_strcat(new_input + len, exit_code);
	ft_strcat(new_input + len + ft_strlen(exit_code), ms->input + len + 2);
	*i += ft_strlen(exit_code);
	free(exit_code);
	free(ms->input);
	ms->input = new_input;
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
