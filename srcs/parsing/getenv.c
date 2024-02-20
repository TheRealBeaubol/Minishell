/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:10:52 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/21 00:18:01 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*get_var_name(t_ms *ms, int i)
{
	char	*str;
	int		stock_i;
	int		malloc_count;
	int		j;

	j = 0;
	malloc_count = 0;
	stock_i = i;
	if (!ft_isalpha(ms->input[i]) && ms->input[i] != '_')
		return (NULL);
	while (ms->input[stock_i] && (ft_isalnum(ms->input[stock_i]) || \
ms->input[stock_i] == '_'))
	{
		stock_i++;
		malloc_count++;
	}
	str = malloc((malloc_count + 2) * sizeof(char));
	while (ft_isalnum(ms->input[i]) || ms->input[i] == '_')
		str[j++] = ms->input[i++];
	str[j] = '=';
	str[++j] = '\0';
	return (str);
}

char	*get_end_str(t_ms *ms, char *var_name, int i)
{
	char	*end_str;
	int		j;

	j = 0;
	end_str = malloc((ft_strlen(ms->input) - i) * sizeof(char));
	i += ft_strlen(var_name);
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

char	*get_new_input(t_ms *ms, int i, char *end_str, char *var_name)
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
	input = ft_strjoin(input, var_env);
	free(var_env);
	if (end_str)
		input = ft_strjoin(input, end_str);
	free(ms->input);
	return (input);
}

char	*get_env(char **env, char *var_name)
{
	int		i;
	char	*cut_str;

	i = 0;
	if (!env || !*env)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], var_name, ft_strlen(var_name)))
		i++;
	if (!env || !env[i])
		return (NULL);
	cut_str = ft_strcut(env[i], var_name);
	return (cut_str);
}

void	parse_env(t_ms *ms)
{
	int		i;
	char	*var_name;
	char	*end_str;

	i = 0;
	while (ms->input[i] != '\0')
	{
		if (ms->input[i] == '$')
		{
			var_name = get_var_name(ms, i + 1);
			end_str = get_end_str(ms, var_name, i);
			ms->input = get_new_input(ms, i, end_str, var_name);
			i = ft_strlen(ms->input) - ft_strlen(end_str);
			if (end_str)
				free(end_str);
		}
		else
			i++;
	}
}
