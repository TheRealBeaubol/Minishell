/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:14:00 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/17 20:30:15 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_last_redir(t_redirlst *redir, unsigned int type)
{
	t_redirlst	*tmp;

	tmp = redir;
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
			g_exit = 126;
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

int	redirection(t_cmdlist *cmdlst)
{
	t_cmdlist	*tmp;

	tmp = cmdlst;
	while (tmp)
	{
		while (tmp->redir)
		{
			if (tmp->redir->type == REDIR_IN)
			{
				tmp->fd_in = open(tmp->redir->file, O_RDONLY);
				if (!check_outfile(tmp->redir->file, tmp->fd_in, 0))
				{
					tmp->fd_in = -1;
					return (0);
				}
				if (tmp->redir->next && is_last_redir(tmp->redir, REDIR_IN))
					close(tmp->fd_in);
			}
			if (tmp->redir->type == REDIR_OUT)
			{
				tmp->fd_out = open(tmp->redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (!check_outfile(tmp->redir->file, tmp->fd_out, 1))
				{
					tmp->fd_in = 1;
					return (0);
				}
				if (tmp->redir->next && is_last_redir(tmp->redir, REDIR_OUT))
					close(tmp->fd_out);
			}
			if (tmp->redir->type == APPEND)
				append(tmp->redir, tmp->fd_out);
			tmp->redir = tmp->redir->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

// int	here_doc(t_cmdlist *cmdlst)
// {
// 	char *line;

// 	while (!strncmp(cmdlst->redir->file, line, ft_strlen(cmdlst->redir->file)))
// 	{
// 		line = readline(">");
// 	}
// }

int	append(t_redirlst *redir, int fd_out)
{
	fd_out = open(redir->file, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (!check_outfile(redir->file, fd_out, 1))
	{
		fd_out = -1;
		return (0);
	}
	if (fd_out)
		dup2(fd_out, STDOUT_FILENO);
	if (fd_out > 2)
		close(fd_out);
	return (1);
}


