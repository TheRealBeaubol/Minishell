/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:14:00 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/19 20:05:46 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	is_last_redir(t_redirlst *redir, unsigned int type)
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

static int	check_outfile(char *file, int fd, int b)
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

static void	append(t_cmdlist *cmdlst)
{
	cmdlst->fd_out = open(cmdlst->redir->file, \
		O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (!check_outfile(cmdlst->redir->file, cmdlst->fd_out, 1))
		cmdlst->fd_out = -1;
}

int	redirection(t_cmdlist *cmdlst)
{
	t_cmdlist	*tmp;

	tmp = cmdlst;
	while (tmp)
	{
		tmp->fd_in = -2;
		tmp->fd_out = -2;
		while (tmp->redir && tmp->fd_in != -1 && tmp->fd_out != -1)
		{
			if (tmp->redir->type == REDIR_IN)
			{
				tmp->fd_in = open(tmp->redir->file, O_RDONLY);
				if (!check_outfile(tmp->redir->file, tmp->fd_in, 0))
					tmp->fd_in = -1;
				if (is_last_redir(tmp->redir, REDIR_IN) && tmp->fd_in != -1)
					close(tmp->fd_in);
			}
			if (tmp->redir->type == REDIR_OUT)
			{
				tmp->fd_out = open(tmp->redir->file, \
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (!check_outfile(tmp->redir->file, tmp->fd_out, 1))
					tmp->fd_out = -1;
				if (is_last_redir(tmp->redir, REDIR_OUT) && tmp->fd_out != -1)
					close(tmp->fd_out);
			}
			if (tmp->redir->type == APPEND)
				append(tmp);
			tmp->redir = tmp->redir->next;
		}
		tmp = tmp->next;
	}
	return (1);
}
