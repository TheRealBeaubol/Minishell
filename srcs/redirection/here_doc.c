/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:18:12 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/19 20:08:16 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	here_doc(t_cmdlist *cmdlst, t_redirlst *redir)
{
	int		fd;
	int		pid;
	char	*line;

	pid = fork();
	if (pid == 0)
	{
		fd = open("here_doc", O_EXCL | O_WRONLY | O_CREAT, 0644);
		line = "";
		while (1)
		{
			line = readline(">");
			if (strncmp(redir->file, line, ft_strlen(redir->file)))
			{
				line = ft_strjoin(line, "\n", NULL, 0b100);
				ft_putstr_fd(line, fd);
			}
			else
				exit(g_exit);
		}
		exit(g_exit);
	}
	waitpid(pid, NULL, 0);
	fd = open("here_doc", O_RDONLY);
	unlink("here_doc");
	cmdlst->fd_in = fd;
	return (1);
}
