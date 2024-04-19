/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 23:16:07 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/19 20:00:33 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	input = ft_strjoin(input, var_env, NULL, 0b011);
	if (end_str)
		input = ft_strjoin(input, end_str, NULL, 0b001);
	free(ms->input);
	if (input[i] == '\0')
		free(var_name);
	return (input);
}

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
		return (ft_strdup("$?"));
	if (ft_isdigit(ms->input[i]))
		return (NULL);
	if (!ft_isalpha(ms->input[i]) && ms->input[i] != '_')
		return (NULL);
	while (ms->input[stock_i++] && (ft_isalnum(ms->input[stock_i]) || \
ms->input[stock_i] == '_'))
		malloc_count++;
	str = ft_calloc((malloc_count + 3), sizeof(char));
	if (!str)
		return (NULL);
	while (ft_isalnum(ms->input[i]) || ms->input[i] == '_')
		str[j++] = ms->input[i++];
	str[j] = '=';
	return (str);
}

int	handle_squote_envvar(t_ms *ms, int i)
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
