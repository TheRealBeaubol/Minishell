/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:14:00 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/16 17:10:21 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_outfile(char *file, int fd)
{
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			ft_dprintf(2, "minishell: %s: Permission denied\n", file);
			g_exit = 126;
			return (0);
		}
		if (errno == EDQUOT)
		{
			ft_dprintf(2, "minishell: %s: the  user's  quota  of  disk blocks or inodes on the filesystem has been exhausted \n", file);
			g_exit = 127;
			return (0);
		}
	}
	return (1);
}

int	redirection(t_redirlst *redir, int fd_out)
{
	int	fd_in;

	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (!check_file(redir->file) && !redir->next)
				return (0);
			fd_in = open(redir->file, O_RDONLY);
			if (redir->next)
			{
				if (redir->next->type == REDIR_IN)
					close(fd_in);
			}
		}
		if (redir->type == REDIR_OUT)
		{
			fd_out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (!check_outfile(redir->file, fd_out))
				return (0);
			if (redir->next)
			{
				if (redir->next->type == REDIR_OUT)
					close(fd_out);
			}
		}
		redir = redir->next;
	}
	if (fd_in)
		dup2(fd_in, STDIN_FILENO);
	if (fd_in > 2)
		close(fd_in);
	if (fd_out)
		dup2(fd_out, STDOUT_FILENO);
	if (fd_out > 2)
		close(fd_out);
	return (1);
}

int	append(t_cmdlist *cmdlist, int fd_out)
{
	check_file(cmdlist->redir->file);
	fd_out = open(cmdlist->redir->file, O_APPEND | O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd_out, STDOUT_FILENO);
	if (fd_out > 2)
		close(fd_out);
	return (1);
}

int	display(t_cmdlist *cmdlst, int fd_out)
{
	if (cmdlst->redir->type == REDIR_IN || cmdlst->redir->type == REDIR_OUT)
	{
		if (!redirection(cmdlst->redir, fd_out))
			return (0);
	}
	if (cmdlst->redir->type == APPEND)
	{
		if (!append(cmdlst, fd_out))
			return (0);
	}
	return (1);
}
