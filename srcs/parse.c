/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:09:25 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/19 18:31:47 by lboiteux         ###   ########.fr       */
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

int	parse_quote(t_ms *ms, int i, char c)
{
	i += 1;
	if (ms->input[i] == '\0')
		free_and_exit(ms);
	while (ms->input[i] != c)
	{
		if (ms->input[i] == '\0')
		{
			ft_putstr_fd("Parsing error\n", 2);
			free_and_exit(ms);
		}
		i++;
	}
	i += 1;
	return (i);
}

void	parse(t_ms *ms)
{
	int		i;
	int		old_i;

	i = 0;
	while (ms->input[i] != '\0')
	{
		while ((9 <= ms->input[i] && ms->input[i] <= 13) || ms->input[i] == 32)
			i++;
		old_i = i;
		while (ms->input[i] != ' ' && ms->input[i] != '\0')
		{
			if (ms->input[i] == '"' || ms->input[i] == '\'')
				i = parse_quote(ms, i, ms->input[i]);
			else
				i++;
		}
		if (ms->lst == NULL)
			ms->lst = ft_lstnew(str_split_strdup(ms->input, old_i, i));
		else
			ft_lstadd_back(&ms->lst, ft_lstnew(str_split_strdup(ms->input, \
		old_i, i)));
	}
}
