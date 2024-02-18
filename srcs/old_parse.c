/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:10:05 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/18 23:07:13 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

// "" '' > >> < << | $		 && ||

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

int	parse_char(t_ms *ms, int i, char c)
{
	size_t	j;

	i += 1;
	j = i;
	if (c == '"' || c == '\'')
	{
		while (ms->input[i] != c && ms->input[i] != '\0')
		{
			i++;
			ft_printf("Test 4 : [%c]\n", ms->input[i]);
		}
		ft_lstadd_back(&ms->lst, ft_lstnew(str_split_strdup(ms->input, j, i)));
		ft_printf("Test 5 : [%c]\n", ms->input[i]);
	}
	else if (c == ' ')
	{
		while (ms->input[i] != ' ' && ms->input[i] != '\0')
		{
			ft_printf("Test 2 : [%c]\n", ms->input[i]);
			i++;
		}
		ft_printf("Test 3 : [%c]\n", ms->input[i]);
		ft_lstadd_back(&ms->lst, ft_lstnew(str_split_strdup(ms->input, j, i)));
	}
	ft_printf("Test 6 : [%c]\n", ms->input[i]);
	return (i);
}

void	print_list(t_list *lst)
{
	t_list	*next;
	int		i;

	i = 0;
	while (lst)
	{
		next = lst->next;
		ft_printf("lst->content : [%s]\n	   i : [%d]\n", lst->content, i);
		i++;
		lst = next;
	}
}

void	parse(t_ms *ms)
{
	size_t	i;
	char	quote;

	quote = '\0';
	i = 0;
	while (ms->input[i] != ' ' && ms->input[i] != '\0')
	{
		if (ms->input[i] == '"' || ms->input[i] == '\'')
		{
			quote = ms->input[i];
			i++;
			while (ms->input[i] != quote)
				i++;
			i++;
		}
		else
			i++;
	}
	ms->lst = ft_lstnew(str_split_strdup(ms->input, 0, i));
	while (ms->input[i] != '\0')
	{
		if (ms->input[i] == ' ' && (ms->input[i + 1] != '"' \
		&& ms->input[i + 1] != '\''))
			i = parse_char(ms, i, ms->input[i]);
		else if (ms->input[i] == ' ' && (ms->input[i + 1] == '"' \
		|| ms->input[i + 1] == '\''))
			i = parse_char(ms, i, ms->input[i]);
	}
}
