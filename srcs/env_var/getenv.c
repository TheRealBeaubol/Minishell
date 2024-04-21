/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:10:52 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/21 03:11:48 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_end_str(char **str, char *var_name, int i)
{
	char	*end_str;
	int		j;

	j = 0;
	end_str = ft_calloc((ft_strlen(*str) - i), sizeof(char));
	if (!end_str)
		return (NULL);
	if (var_name && (var_name[ft_strlen(var_name) - 1] == '='))
		i += ft_strlen(var_name);
	else if (var_name)
		i += ft_strlen(var_name) + 2;
	else
		i++;
	if ((*str)[i] == '\0')
	{
		free(end_str);
		return (NULL);
	}
	while ((*str)[i] != '\0')
		end_str[j++] = (*str)[i++];
	end_str[j] = '\0';
	return (end_str);
}

static void	handle_exit_envvar(char **str, int *i)
{
	char	*exit_code;
	char	*new_input;
	int		len;

	exit_code = ft_itoa(g_exit);
	new_input = ft_calloc((ft_strlen(*str) \
	+ ft_strlen(exit_code) - 1), sizeof(char));
	if (!new_input)
		return ;
	len = ft_strchr(*str, '$') - *str;
	ft_strncat(new_input, *str, len);
	ft_strcat(new_input + len, exit_code);
	ft_strcat(new_input + len + ft_strlen(exit_code), *str + len + 2);
	*i += ft_strlen(exit_code);
	free(exit_code);
	free(*str);
	*str = new_input;
}

static int	replace_var(char **str, char **env, int i)
{
	char	*var_name;
	char	*end_str;

	if (ft_iswhitespace((*str)[i + 1]))
		return (i + 1);
	var_name = get_var_name(str, i);
	if (!var_name)
		return (i + 1);
	end_str = get_end_str(str, var_name, i);
	if (var_name && var_name[0] == '$' && var_name[1] == '?')
		handle_exit_envvar(str, &i);
	else if (var_name && var_name[ft_strlen(var_name) - !!ft_strlen(var_name)] != '=')
		*str = ft_strjoin(var_name, end_str, NULL, 0b001);
	else
	{
		*str = get_new_input(str, env, i, var_name);
		if ((*str)[i] == '\026')
			return (i);
	}
	if (var_name[0] != '$' && var_name[1] != '?')
		i = ft_strlen(*str) - ft_strlen(end_str);
	free(var_name);
	free(end_str);
	return (i);
}

static int	handle_dquote_envvar(char **str, char **env, int i)
{
	int	j;

	j = i + 1;
	while ((*str)[j] != '"')
	{
		if ((*str)[j] == '\0')
			return (-1);
		if ((*str)[j] == '$')
		{
			if ((*str)[j + 1] == '?')
				handle_exit_envvar(str, &j);
			else if ((*str)[j + 1] == '$')
				j += 2;
			else
				j = replace_var(str, env, j);
		}
		else
			j++;
	}
	return (j + 1);
}

int	parse_env(char **str, char **env)
{
	int		i;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '"' && (*str)[i + 1] != '\0')
			i = handle_dquote_envvar(str, env, i);
		else if ((*str)[i] == '\'')
			i = handle_squote_envvar(str, i);
		else if ((*str)[i] == '$')
		{
			if ((*str)[i + 1] == '?')
				handle_exit_envvar(str, &i);
			else
				i = replace_var(str, env, i);
			if ((*str)[0] == '\0')
				return (0);
		}
		else
			i++;
		if (i == -1)
			return (1);
	}
	return (0);
}
