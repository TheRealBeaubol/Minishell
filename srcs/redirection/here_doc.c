/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:18:12 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/20 20:33:44 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*ft_random(void)
{
	int		i;
	int		fd;
	char	*file;

	i = 1;
	file = ft_calloc(11, sizeof(char));
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	file[0] = '.';
	while (i < 10)
	{
		read(fd, &file[i], 1);
		if (file[i] >= 33 && file[i] <= 126)
			i++;
	}
	close(fd);
	return (file);
}

void	exit_heredoc(int err_code, char *heredoc_name, t_cmdlist *cmdlst)
{
	int	fd;
	int	status;

	status = WEXITSTATUS(err_code);
	if (status == 0)
	{
		ft_dprintf (2, "bash: warning: here-document at line 1 delimited\
 by end-of-file (wanted `%s')\n", cmdlst->redir->file);
	}
	if (status == 127)
	{
		unlink(heredoc_name);
		free(heredoc_name);
		g_exit = status;
		return ;
	}
	fd = open(heredoc_name, O_RDONLY);
	unlink(heredoc_name);
	free(heredoc_name);
	cmdlst->fd_in = fd;
}

int	here_doc(t_cmdlist *cmdlst, t_redirlst *redir, t_ms *ms)
{
	int		fd;
	int		pid;
	char	*line;
	char	*heredoc_name;
	int		err_code;

	signal_state_manager(1);
	heredoc_name = ft_random();
	pid = fork();
	if (pid == 0)
	{
		rl_catch_signals = 1;
		signal_state_manager(2);
		line = NULL;
		fd = open(heredoc_name, O_EXCL | O_CREAT, 0600);
		while (1)
		{
			free(line);
			line = readline(">");
			if (!line || (!ft_strncmp(redir->file, line, ft_strlen(redir->file) + 1)))
				break ;
			ft_putendl_fd(line, fd);
		}
		free(line);
		free(heredoc_name);
		rl_clear_history();
		free_cmdlist(cmdlst);
		free(ms->prompt);
		ft_free_tab(ms->env);
		close(fd);
		exit(g_exit);
	}
	waitpid(pid, &err_code, 0);
	exit_heredoc(err_code, heredoc_name, cmdlst);
	signal_state_manager(0);
	return (1);
}
