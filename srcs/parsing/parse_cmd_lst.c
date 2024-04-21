/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:01:35 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/21 06:07:24 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_cmdlist	*cmd_list_init(t_ms *ms)
{
	t_cmdlist	*cmdlist;

	ms->cmdlist = ft_calloc(2, sizeof(t_cmdlist));
	if (!ms->cmdlist)
		return (NULL);
	cmdlist = ms->cmdlist;
	cmdlist->param = ft_calloc(2, sizeof(char *));
	if (!cmdlist->param)
		return (NULL);
	cmdlist->next = NULL;
	return (cmdlist);
}

static int	get_redir_type(char *content)
{
	if (!ft_strncmp(content, "<", 2))
		return (REDIR_IN);
	else if (!ft_strncmp(content, ">", 2))
		return (REDIR_OUT);
	else if (!ft_strncmp(content, "<<", 3))
		return (HERE_DOC);
	else if (!ft_strncmp(content, ">>", 3))
		return (APPEND);
	return (EMPTY);
}

static t_redirlst	*ft_redir_list(t_redirlst *redir, char *type, char *file)
{
	t_redirlst	*tmp;
	t_redirlst	*new;

	if (!redir)
	{
		redir = ft_calloc(2, sizeof(t_redirlst));
		redir->type = get_redir_type(type);
		redir->file = ft_strdup(file);
		redir->next = NULL;
		return (redir);
	}
	new = ft_calloc(2, sizeof(t_redirlst));
	new->type = get_redir_type(type);
	new->file = ft_strdup(file);
	tmp = redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (redir);
}

void	add_pipe_to_cmdlist(t_cmdlist **tmplist, int *is_cmd)
{
	(*tmplist)->next = ft_calloc(2, sizeof(t_cmdlist));
	(*tmplist) = (*tmplist)->next;
	(*tmplist)->param = ft_calloc(2, sizeof(char *));
	*is_cmd = 0;
	(*tmplist)->redir = NULL;
}

void	do_cmd_list(t_ms *ms)
{
	t_cmdlist	*tmplist;
	t_list		*tmp;
	int			is_cmd;

	is_cmd = 0;
	tmp = ms->lst;
	tmplist = cmd_list_init(ms);
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || \
			tmp->type == HERE_DOC || tmp->type == APPEND)
		{
			tmplist->redir = ft_redir_list(tmplist->redir, tmp->content, \
				tmp->next->content);
			tmp = tmp->next;
		}
		else if (!is_cmd++ && tmp->type == EMPTY)
			tmplist->param[0] = ft_strdup(tmp->content);
		else if (ft_strncmp(tmp->content, "|", 2) == 0 && tmp->type == PIPE)
			add_pipe_to_cmdlist(&tmplist, &is_cmd);
		else
			tmplist->param = ft_join_tab(tmplist->param, tmp->content);
		tmp = tmp->next;
	}
}
