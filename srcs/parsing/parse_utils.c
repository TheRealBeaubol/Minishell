/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:09:41 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/19 14:52:28 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"	

t_list	*new_token(t_type type, char *content)
{
	t_list	*new;

	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return (NULL);
	new->type = type;
	new->content = content;
	new->next = NULL;
	return (new);
}

void	token_addback(t_list **lst, t_type type, char *content)
{
	t_list	*new;
	t_list	*tmp;

	new = new_token(type, content);
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

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
		token_addback(&(ms->lst), APPEND, ft_strdup(">>"));
		(*i)++;
	}
	else
		token_addback(&(ms->lst), REDIR_OUT, ft_strdup(">"));
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
		token_addback(&(ms->lst), HERE_DOC, ft_strdup("<<"));
		(*i)++;
	}
	else
		token_addback(&(ms->lst), REDIR_IN, ft_strdup("<"));
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
	token_addback(&(ms->lst), PIPE, ft_strdup("|"));
	(*i)++;
}
