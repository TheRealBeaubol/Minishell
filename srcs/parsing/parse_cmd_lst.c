/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:01:35 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/16 01:04:32 by lboiteux         ###   ########.fr       */
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
		redir->prev = NULL;
		return (redir);
	}
	new = ft_calloc(2, sizeof(t_redirlst));
	new->type = get_redir_type(type);
	new->file = ft_strdup(file);
	tmp = redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (redir);
}

void	do_cmd_list(t_ms *ms)
{
	t_cmdlist	*tmpcmdlist;
	t_list		*tmp;
	int			is_cmd;

	is_cmd = 0;
	tmp = ms->lst;
	tmpcmdlist = cmd_list_init(ms);
	while (tmp)
	{
		if (!is_cmd)
			tmpcmdlist->cmd = ft_strdup(tmp->content);
		if (!is_cmd++)
			tmpcmdlist->param[0] = ft_strdup(tmp->content);
		else if (ft_strncmp(tmp->content, "|", 2) == 0)
		{
			tmpcmdlist->next = ft_calloc(2, sizeof(t_cmdlist));
			tmpcmdlist = tmpcmdlist->next;
			tmpcmdlist->param = ft_calloc(2, sizeof(char *));
			is_cmd = 0;
		}
		else if (ft_strncmp(tmp->content, "<", 2) == 0 || ft_strncmp(tmp->content, ">", 2) == 0 || ft_strncmp(tmp->content, ">>", 3) == 0 || ft_strncmp(tmp->content, "<<", 3) == 0)
		{
			tmpcmdlist->redir = ft_redir_list(tmpcmdlist->redir, tmp->content, tmp->next->content);
			tmp = tmp->next;
		}
		else
			tmpcmdlist->param = ft_join_tab(tmpcmdlist->param, tmp->content);
		tmp = tmp->next;
	}
}