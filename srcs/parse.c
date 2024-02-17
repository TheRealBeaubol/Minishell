/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:10:05 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/17 02:20:16 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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

void	parse_quote(t_ms *ms, size_t *i)
{
	size_t	j;

	j = *i + 1;
	while (ms->input[*++i] != '"')
		;
	ft_printf("%d %c\n", *i, ms->input[*i]);
	if (*i == ft_strlen(ms->input))
		free_and_exit(ms);
	ms->lst->content = str_split_strdup(ms->input, j, *i);
}

void	parse(t_ms *ms)
{
	size_t	i;

	i = -1;
	while (ms->input[++i] != '\0')
	{
		if (ms->input[i] == '"')
			parse_quote(ms, &i);
		ft_printf("%s\n", ms->lst->content);
	}
}
