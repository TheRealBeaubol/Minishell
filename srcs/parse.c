/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 01:10:05 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/17 17:54:20 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
static int	count_malloc(t_ms *ms)
{
	int	i = 0;
	int	cpt = 0;

	while (ms->input[i] != '\0')
	{
		if (ms->input[i] == ' ')
		{
			i++;
			cpt += 1;
		}
		else if (ms->input[i++] == '"')
		{
			while (ms->input[i] != '"')
			{
				if (ms->input[i] == '\0')
				{
					ft_putstr_fd("Parsing error\n", 2);
					free_and_exit(ms);
				}
				i++;
			}
			i++;
			cpt++;
		}
		else if (ms->input[i++] == '\'')
		{
			while (ms->input[i] != '\'')
			{
				if (ms->input[i] == '\0')
				{
					ft_putstr_fd("Parsing error\n", 2);
					free_and_exit(ms);
				}
				i++;
			}
			i++;
			cpt++;
		}
		else if ((ms->input[i] == '|' && ms->input[i + 1] == '|') || (ms->input[i] == '&' && \
ms->input[i + 1] == '&') || (ms->input[i] == '>' && ms->input[i + 1] == '>') || (ms->input[i] \
== '<' && ms->input[i + 1] == '<') || (ms->input[i] == '<' && ms->input[i + 1] == ' ') || \
(ms->input[i] == '<' && ms->input[i + 1] == ' '))
		{
			i += 2;
			cpt += 1;
		}
		else if (ms->input[i] == '$')
		{
			while (ms->input[i] != ' ')
			{
				if (ms->input[i] == '\0')
				{
					ft_putstr_fd("Parsing error\n", 2);
					free_and_exit(ms);
				}
				i++;
			}
			cpt++;
		}
		else if (ms->input[i++] == ';')
			cpt++;
		else
			i++;
	}
	return (cpt);
}

// ; "" '' > >> < << | $ && ||
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

void	parse_char(t_ms *ms, size_t *i, char c)
{
	size_t	j;

	j = *i + 1;
	if (c == ' ')
	{
		while (ms->input[*i] != '"' && ms->input[*i] != '\'' && ms->input[*i] != ' ' && ms->input[*i] != '\0')
			(*i)++;
		ft_lstadd_back(&ms->lst, ft_lstnew(str_split_strdup(ms->input, j, (*i))));
	}
	if (c == '"' || c == '\'')
	{
		while (ms->input[++(*i)] != c && ms->input[*i] != '\0')
			;
		ft_lstadd_back(&ms->lst, ft_lstnew(str_split_strdup(ms->input, j, (*i))));
	}
}

void	print_list(t_list *lst)
{
	t_list	*next;
	int		i = 0;

	while (lst)
	{
		next = lst->next;
		ft_printf("%s %d\n", lst->content, i++);
		lst = next;
	}
}

void	parse(t_ms *ms)
{
	ft_printf("%d\n", count_malloc(ms));
	// size_t	i;

	// i = -1;
	// while (ms->input[++i] != '\0')
	// {
	// 	if (ms->input[i] == '"' || ms->input[i] == ' ' || ms->input[i] == '\'')
	// 		parse_char(ms, &i, ms->input[i]);
	// }
}