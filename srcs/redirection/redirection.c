/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:14:00 by mhervoch          #+#    #+#             */
/*   Updated: 2024/05/02 20:27:18 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_last_redir(t_redirlst *redir, unsigned int type)
{
	t_redirlst	*tmp;

	tmp = redir->next;
	while (tmp)
	{
		if (tmp->type == type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_outfile(char *file, int fd, int b)
{
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			ft_dprintf(2, "minishell: %s: Permission denied\n", file);
			g_exit = 1;
			return (0);
		}
		if (errno == ENOENT)
		{
			ft_dprintf(2, "minishell: %s: No such file or directory\n", file);
			g_exit = 1;
			return (0);
		}
		if (errno == EDQUOT && b)
		{
			ft_dprintf(2, "minishell: %s: the user's quota of disk blocks \
or inodes on the filesystem has been exhausted \n", file);
			g_exit = 127;
			return (0);
		}
	}
	return (1);
}

void	init_fd(t_cmdlist *cmdlst)
{
	cmdlst->fd_in = -2;
	cmdlst->fd_out = -2;
}

static int	open_heredoc(t_cmdlist *cmdlst, t_ms *ms)
{
	t_cmdlist	*tmp;
	t_redirlst	*tmpr;

	tmp = cmdlst;
	while (tmp)
	{
		init_fd(tmp);
		tmpr = tmp->redir;
		while (tmpr && tmp->fd_in != -1 && tmp->fd_in != -3)
		{
			if (tmpr->type == HERE_DOC)
				do_here_doc(tmp, tmpr, ms);
			tmpr = tmpr->next;
		}
		if (tmp->fd_in == -3)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	redirection(t_cmdlist *cmdlst, t_ms *ms)
{
	t_cmdlist	*tmp;
	t_redirlst	*tmpr;

	tmp = cmdlst;
	if (!open_heredoc(tmp, ms))
		return ;
	while (tmp)
	{
		tmpr = tmp->redir;
		while (tmpr && tmp->fd_in != -1 && tmp->fd_out != -1 \
				&& tmp->fd_in != -3)
		{
			if (tmpr->type == REDIR_IN)
				do_redir_in(tmp, tmpr);
			if (tmpr->type == REDIR_OUT)
				do_redir_out(tmp, tmpr);
			if (tmpr->type == APPEND)
				do_append(tmp, tmpr);
			tmpr = tmpr->next;
		}
		if (tmp->fd_in == -3)
			break ;
		tmp = tmp->next;
	}
}
