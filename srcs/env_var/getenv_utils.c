/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 23:16:07 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/21 02:27:09 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_new_input(char **str, char **env, int i, char *var_name)
{
	char	*input;
	char	*var_env;
	char	*end_str;
	int		j;

	end_str = get_end_str(str, var_name, i);
	j = -1;
	var_env = get_env(env, var_name);
	input = ft_calloc((ft_strlen(end_str) + ft_strlen(var_env) + i + 1), \
sizeof(char));
	while (++j != i)
		input[j] = (*str)[j];
	input = ft_strjoin(input, var_env, NULL, 0b011);
	if (end_str)
		input = ft_strjoin(input, end_str, NULL, 0b001);
	free(*str);
	free(end_str);
	if (!*input)
	{
		free(var_name);
		free(input);
		return (ft_strdup("\026"));
	}
	return (input);
}

char	*get_var_name(char **str, int i)
{
	char	*var_name;
	int		stock_i;
	int		malloc_count;
	int		j;

	j = 0;
	malloc_count = 0;
	stock_i = i;
	i++;
	if ((*str)[i] == '?')
		return (ft_strdup("$?"));
	if (ft_isdigit((*str)[i]))
		return (NULL);
	if (!ft_isalpha((*str)[i]) && (*str)[i] != '_')
		return (NULL);
	while ((*str)[stock_i++] && (ft_isalnum((*str)[stock_i]) || \
		(*str)[stock_i] == '_'))
		malloc_count++;
	var_name = ft_calloc((malloc_count + 3), sizeof(char));
	if (!var_name)
		return (NULL);
	while (ft_isalnum((*str)[i]) || (*str)[i] == '_')
		var_name[j++] = (*str)[i++];
	var_name[j] = '=';
	return (var_name);
}

int	handle_squote_envvar(char **str, int i)
{
	i++;
	while ((*str)[i] != '\'')
	{
		if ((*str)[i] == '\0')
			return (-1);
		i++;
	}
	return (i + 1);
}
