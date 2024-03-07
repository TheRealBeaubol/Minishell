/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:16:06 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/07 23:34:28 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	parse_quote(t_ms *ms, int i, char c)
{
	int	j;

	j = i;
	i += 1;
	if (ms->input[i] == '\0')
		free_and_exit(ms);
	while (ms->input[i] != c)
	{
		if (ms->input[i] == '\0')
		{
			ft_putstr_fd("Parsing error\n", 2);
			return (-1);
		}
		i++;
	}
	ms->input = clear_quotes(ms->input, i, j, ms);
	ms->quote = 1;
	if (ms->input[i] != '\0')
		i++;
	return (i);
}

char	*clear_quotes(char *content, int i, int j, t_ms *ms)
{
	if (ms->quote == 0)
		j++;
	while (j != i)
	{
		content[j - 1] = content[j];
		j++;
	}
	j++;
	if (content[j + 1] == '\0')
		content[j - 1] = '\0';
	else
	{
		while (content[j] != '\0')
		{
			content[j - 2] = content[j];
			j++;
		}
		content[j - 2] = '\0';
	}
	return (content);
}
