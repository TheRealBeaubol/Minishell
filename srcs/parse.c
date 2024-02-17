/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:10:05 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/17 16:15:37 by lboiteux         ###   ########.fr       */
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
	while (ms->input[++(*i)] != '"')
		;
	if (*i == ft_strlen(ms->input))
		free_and_exit(ms);
	ft_printf("%s\n", str_split_strdup(ms->input, j, *i));
	ft_lstadd_back(&ms->lst, ft_lstnew(str_split_strdup(ms->input, j, *i)));
}
void	print_list(t_list *lst)
{
	t_list	*current;
	t_list	*next;

	current = lst;
	while (current)
	{
		next = current->next;
		ft_printf("%s\n", lst->content);
		current = next;
	}
}
void	parse(t_ms *ms)
{
	size_t	i;

	i = -1;
	while (ms->input[++i] != '\0')
	{
		if (ms->input[i] == '"')
		{
			parse_quote(ms, &i);
			print_list(ms->lst);
		}
	}
	
}
