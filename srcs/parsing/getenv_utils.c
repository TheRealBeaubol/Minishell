/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 23:16:07 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/13 19:57:26 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int	handle_dquote_envvar(t_ms *ms, int i)
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

int	handle_alone_var(t_ms *ms)
{
	int		i;
	char	*var_name;

	i = 0;
	if (ms->input[i] == '$')
	{
		if (ms->input[i + 1] == '?' && ms->input[i + 2] == '\0')
		{
			free(ms->input);
			ms->input = ft_itoa(g_exit);
		}
		else if (ms->input[i + 1] == '$' && ms->input[i + 2] == '\0')
			free(ms->input);
		else if (ms->input[i + 1] == '\0')
		{
			free(ms->input);
			ms->input = ft_strdup("$");
		}
		else
		{
			while (ms->input[i] != '\0' && ms->input[i] != ' ')
				i++;
			if (ms->input[i] == ' ')
				return (1);
			else
			{
				var_name = get_var_name(ms, 0);
				free(ms->input);
				ms->input = NULL;
				if (var_name)
					ms->input = ft_strdup(var_name);
			}
		}
		return (0);
	}
	return (1);
}
