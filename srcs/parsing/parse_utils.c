/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:09:41 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/16 14:42:58 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"	

int	add_redir_out_and_append(t_ms *ms, int *i, int *old_i, int *is_pipe)
{
	int	is_double;

	is_double = 0;
	*is_pipe = 1;
	if (ms->input[*i + 1] == '>')
		is_double = 1;
	if (*old_i != *i)
	{
		fill_list(ms->input, &(ms->lst), *i, *old_i);
		*old_i = *i + 1;
	}
	if (is_double == 1)
	{
		ft_lstadd_back(&(ms->lst), ft_lstnew(ft_strdup(">>")));
		(*i)++;
	}
	else
		ft_lstadd_back(&(ms->lst), ft_lstnew(ft_strdup(">")));
	(*i)++;
	return (is_double);
}

int	add_redir_in_and_heredoc(t_ms *ms, int *i, int *old_i, int *is_pipe)
{
	int	is_double;

	is_double = 0;
	*is_pipe = 1;
	if (ms->input[*i + 1] == '<')
		is_double = 1;
	if (*old_i != *i)
	{
		fill_list(ms->input, &(ms->lst), *i, *old_i);
		*old_i = *i + 1;
	}
	if (is_double == 1)
	{
		ft_lstadd_back(&(ms->lst), ft_lstnew(ft_strdup("<<")));
		(*i)++;
	}
	else
		ft_lstadd_back(&(ms->lst), ft_lstnew(ft_strdup("<")));
	(*i)++;
	return (is_double);
}

void	add_pipe(t_ms *ms, int *i, int *old_i, int *is_pipe)
{
	*is_pipe = 1;
	if (*old_i != *i)
	{
		fill_list(ms->input, &(ms->lst), *i, *old_i);
		*old_i = *i + 1;
	}
	ft_lstadd_back(&(ms->lst), ft_lstnew(ft_strdup("|")));
	(*i)++;
}
