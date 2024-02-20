/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:16:06 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/20 20:50:41 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

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
			return (-1);
		}
		i++;
	}
	i += 1;
	return (i);
}

char	*clear_quotes(char *content, int i, char c)
{
	i++;
	while (content[i] != c)
	{
		content[i - 1] = content[i];
		i++;
	}
	i++;
	while (content[i] != '\0')
	{
		content[i - 2] = content[i];
		i++;
	}
	content[i - 2] = '\0';
	return (content);
}

void	rm_quote(t_ms *ms)
{
	t_list	*next;
	t_list	*tmp;
	int		i;

	tmp = ms->lst;
	while (tmp)
	{
		i = 0;
		next = tmp->next;
		while (tmp->content[i] != '\0')
		{
			if (tmp->content[i] == '"' || tmp->content[i] == '\'')
				tmp->content = clear_quotes(tmp->content, i, tmp->content[i]);
			else
				i++;
		}
		tmp = next;
	}
}
