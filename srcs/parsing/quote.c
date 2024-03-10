/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:16:06 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/09 18:18:32 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	parse_quote(t_ms *ms, int i, char c)
{
	char	*tmp;
	char	*unquote_str;
	int		j;

	tmp = ft_calloc(ft_strlen(ms->input) - i + 1, sizeof(char));
	if (!tmp)
		return (-1);
	unquote_str = tmp;
	j = 0;
	while (j != i - 1)
		*(tmp++) = ms->input[j++];
	while (ms->input[i] != c)
	{
		if (ms->input[i] == '\0')
			return (-1);
		*(tmp++) = ms->input[i++];
	}
	j = i++;
	while (ms->input[i] != '\0')
		*(tmp++) = ms->input[i++];
	*tmp = '\0';
	free(ms->input);
	ms->input = unquote_str;
	return (j - 1);
}
