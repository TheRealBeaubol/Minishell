/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:14:00 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/16 15:35:12 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	redirection(t_redirlst *redir, int fd_out)
{
	int	fd_in;

	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			check_file(redir->file);
			fd_in = open(redir->file, O_RDONLY);
			if (redir->next->type == REDIR_IN)
				close(fd_in);
		}
		if (redir->type == REDIR_OUT)
		{
			check_file(redir->file);
			fd_out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (redir->next->type == REDIR_OUT)
				close(fd_out);
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
		redirection(cmdlst->redir, fd_out);
	if (cmdlst->redir->type == APPEND)
		append(cmdlst, fd_out);
	return (1);
}
