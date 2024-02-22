/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:10:52 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/22 23:16:47 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	replace_var(t_ms *ms, int *i)
{
	char	*var_name;
	char	*end_str;

	var_name = get_var_name(ms, *i + 1);
	end_str = get_end_str(ms, var_name, *i);
	if (var_name[ft_strlen(var_name) - 1] != '=')
	{
		ms->input = ft_strjoin(var_name, end_str);
		*i = ft_strlen(ms->input) - ft_strlen(end_str);
	}
	else
	{
		ms->input = get_new_input(ms, *i, end_str, var_name);
		if (ms->input[*i] == '\0')
			return ;
		*i = ft_strlen(ms->input) - ft_strlen(end_str);
	}
	if (end_str)
		free(end_str);
}

int	parse_env(t_ms *ms)
{
	int		i;

	i = 0;
	while (ms->input[i] != '\0')
	{
		if (ms->input[i] == '$')
		{
			replace_var(ms, &i);
			if (ms->input[0] == '\0')
				return (1);
		}
		else
			i++;
	}
	return (0);
}
