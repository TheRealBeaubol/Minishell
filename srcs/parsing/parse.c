/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:09:25 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/09 21:04:14 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static char	*str_split_strdup(char *src, int start, int end)
{
	int		i;
	int		j;
	char	*dest;

	dest = malloc(end - start + 1 * sizeof(*dest));
	if (dest == NULL)
		return (dest);
	i = start;
	j = 0;
	while (i < end)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = 0;
	return (dest);
}

void	fill_list(t_ms *ms, int i, int old_i)
{
	// ft_printf("%s\n", str_split_strdup(ms->input, old_i, i));
	if (ms->lst == NULL)
		ms->lst = ft_lstnew(str_split_strdup(ms->input, old_i, i));
	else
		ft_lstadd_back(&ms->lst, ft_lstnew(str_split_strdup(ms->input, \
	old_i, i)));
}


void	parse(t_ms *ms)
{
	int		i;
	int		old_i;

	i = 0;
	if (parse_env(ms) == 1)
		return ;
	while (ms->input[i] != '\0')
	{
		while (ft_iswhitespace(ms->input[i]))
			i++;
		old_i = i;
		while ((ms->input[i] != ' ') && ms->input[i] != '\0')
		{
			if (ms->input[i] == '"' || ms->input[i] == '\'')
			{
				i++;
				i = parse_quote(ms, i, ms->input[i - 1]);
				if (i == -1)
				{
					ft_dprintf(2, "Parsing Error\n");
					return ;
				}
			}
			else
				i++;
		}
		fill_list(ms, i, old_i);
	}
}
