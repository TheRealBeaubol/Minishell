/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:10:52 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/19 20:01:22 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*get_end_str(t_ms *ms, char *var_name, int i)
{
	char	*end_str;
	int		j;

	j = 0;
	end_str = ft_calloc((ft_strlen(ms->input) - i), sizeof(char));
	if (!end_str)
		return (NULL);
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
		end_str[j++] = ms->input[i++];
	end_str[j] = '\0';
	return (end_str);
}

static void	handle_exit_envvar(t_ms *ms, int *i)
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

static int	replace_var(t_ms *ms, int i)
{
	char	*var_name;
	char	*end_str;

	if (ft_iswhitespace(ms->input[i + 1]))
		return (i + 1);
	var_name = get_var_name(ms, i);
	if (!var_name)
		return (i + 1);
	end_str = get_end_str(ms, var_name, i);
	if (var_name && var_name[0] == '$' && var_name[1] == '?')
		handle_exit_envvar(ms, &i);
	else if (var_name && var_name[ft_strlen(var_name) - 1] != '=')
		ms->input = ft_strjoin(var_name, end_str, NULL, 0b001);
	else
	{
		ms->input = get_new_input(ms, i, end_str, var_name);
		if (ms->input[i] == '\0')
			return (i);
	}
	if (var_name[0] != '$' && var_name[1] != '?')
		i = ft_strlen(ms->input) - ft_strlen(end_str);
	free(var_name);
	free(end_str);
	return (i);
}

static int	handle_dquote_envvar(t_ms *ms, int i)
{
	int	j;

	j = i + 1;
	while (ms->input[j] != '"')
	{
		if (ms->input[j] == '\0')
			return (-1);
		if (ms->input[j] == '$')
		{
			if (ms->input[j + 1] == '?')
				handle_exit_envvar(ms, &j);
			else if (ms->input[j + 1] == '$')
				j += 2;
			else
				j = replace_var(ms, j);
		}
		else
			j++;
	}
	return (j + 1);
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
				return (0);
		}
		else
			i++;
		if (i == -1)
			return (1);
	}
	return (0);
}
