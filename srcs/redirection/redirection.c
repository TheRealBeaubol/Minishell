/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:14:00 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/21 04:25:30 by lboiteux         ###   ########.fr       */
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

void	redirection(t_cmdlist *cmdlst, t_ms *ms)
{
	t_cmdlist	*tmp;
	t_redirlst	*tmpr;

	tmp = cmdlst;
	while (tmp)
	{
		tmp->fd_in = -2;
		tmp->fd_out = -2;
		tmpr = tmp->redir;
		while (tmpr && tmp->fd_in != -1 && tmp->fd_out != -1 && tmp->fd_in != -3)
		{
			if (tmpr->type == REDIR_IN)
			{
				tmp->fd_in = open(tmpr->file, O_RDONLY);
				if (!check_outfile(tmpr->file, tmp->fd_in, 0))
					tmp->fd_in = -1;
				if ((is_last_redir(tmpr, REDIR_IN) || is_last_redir(tmpr, HERE_DOC)) && tmp->fd_in != -1)
					close(tmp->fd_in);
			}
			if (tmpr->type == HERE_DOC)
			{
				if (!here_doc(tmp, tmpr, ms))
					tmp->fd_in = -3;
				if (!check_outfile(tmpr->file, tmp->fd_in, 0))
					tmp->fd_in = -1;
				if ((is_last_redir(tmpr, REDIR_IN) || is_last_redir(tmpr, HERE_DOC)) && tmp->fd_in != -1)
					close(tmp->fd_in);
			}
			if (tmpr->type == REDIR_OUT)
			{
				tmp->fd_out = open(tmpr->file, O_WRONLY \
					| O_CREAT | O_TRUNC, 0644);
				if (!check_outfile(tmpr->file, tmp->fd_out, 1))
					tmp->fd_out = -1;
				if ((is_last_redir(tmpr, REDIR_OUT) || is_last_redir(tmpr, APPEND)) && tmp->fd_out != -1)
					close(tmp->fd_out);
			}
			if (tmpr->type == APPEND)
			{
				tmp->fd_out = open(tmpr->file, O_APPEND | O_WRONLY | O_CREAT, 0644);
				if (!check_outfile(tmpr->file, tmp->fd_out, 1))
					tmp->fd_out = -1;
				if ((is_last_redir(tmpr, REDIR_OUT) || is_last_redir(tmpr, APPEND)) && tmp->fd_out != -1)
					close(tmp->fd_out);
			}
			tmpr = tmpr->next;
		}
		if (tmp->fd_in == -3)
			break ;
		tmp = tmp->next;
	}
}
