/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 06:24:09 by mhervoch          #+#    #+#             */
/*   Updated: 2024/05/02 22:28:58 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	do_redir_out(t_cmdlist *tmp, t_redirlst *tmpr)
{
	tmp->fd_out = open(tmpr->file, O_WRONLY \
			| O_CREAT | O_TRUNC, 0644);
	if (!check_outfile(tmpr->file, tmp->fd_out, 1))
		tmp->fd_out = -1;
	if ((is_last_redir(tmpr, REDIR_OUT) || \
				is_last_redir(tmpr, APPEND)) && tmp->fd_out != -1)
		close(tmp->fd_out);
}

void	do_redir_in(t_cmdlist *tmp, t_redirlst *tmpr)
{
	tmp->fd_in = open(tmpr->file, O_RDONLY);
	if (!check_outfile(tmpr->file, tmp->fd_in, 0))
		tmp->fd_in = -1;
	if ((is_last_redir(tmpr, REDIR_IN) || \
				is_last_redir(tmpr, HERE_DOC)) && tmp->fd_in != -1)
		close(tmp->fd_in);
}

void	do_here_doc(t_cmdlist *tmp, t_redirlst *tmpr, t_ms *ms)
{
	if (!here_doc(tmp, tmpr, ms))
		tmp->fd_in = -3;
	if (!check_outfile(tmpr->file, tmp->fd_in, 0))
		tmp->fd_in = -1;
	if ((is_last_redir(tmpr, REDIR_IN) || \
is_last_redir(tmpr, HERE_DOC)) && tmp->fd_in != -1 && tmp->fd_in != -3)
		close(tmp->fd_in);
}

void	do_append(t_cmdlist *tmp, t_redirlst *tmpr)
{
	tmp->fd_out = open(tmpr->file, O_APPEND | \
			O_WRONLY | O_CREAT, 0644);
	if (!check_outfile(tmpr->file, tmp->fd_out, 1))
		tmp->fd_out = -1;
	if ((is_last_redir(tmpr, REDIR_OUT) || \
				is_last_redir(tmpr, APPEND)) && tmp->fd_out != -1)
		close(tmp->fd_out);
}
