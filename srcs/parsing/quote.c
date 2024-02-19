/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:16:06 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/19 21:30:42 by lboiteux         ###   ########.fr       */
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

void	clear_quotes(char *content, int i, char c)
{
	i++;
	while (content[i] != c)
	{
		content[i - 1] = content[i];
		i++;
	}
	while (content[i + 1] != '\0')
	{
		content[i - 1] = content[i + 1];
		i++;
	}
	content[i - 1] = '\0';
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
		if (tmp->content[0] == '"' || tmp->content[0] == '\'')
		{
			clear_quotes(tmp->content, i, tmp->content[i]);
			if (tmp->content[i + 1] != '\0')
			{
				while (tmp->content[++i] != '\0')
				{
					if (tmp->content[i] == '"' || tmp->content[i] == '\'')
						clear_quotes(tmp->content, i, tmp->content[i]);
				}
			}
		}
		tmp = next;
	}
}
