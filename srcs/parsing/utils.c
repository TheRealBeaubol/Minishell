/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:09:41 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/19 19:49:07 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"	

t_list	*new_element(t_type type, char *content)
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

void	addback_element(t_list **lst, t_type type, char *content)
{
	t_list	*new;
	t_list	*tmp;

	new = new_element(type, content);
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

void	fill_list(char *input, t_list **lst, int i, int old_i)
{
	char	*str;

	str = ft_strdup_range(input, old_i, i);
	if (*lst == NULL)
	{
		*lst = new_element(EMPTY, str);
		return ;
	}
	addback_element(lst, EMPTY, str);
}

void	add_pipe(t_ms *ms, int *i, int *old_i, int *is_pipe)
{
	*is_pipe = 1;
	if (*old_i != *i)
	{
		fill_list(ms->input, &(ms->lst), *i, *old_i);
		*old_i = *i + 1;
	}
	addback_element(&(ms->lst), PIPE, ft_strdup("|"));
	(*i)++;
}
