/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:18:12 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/21 05:30:12 by mhervoch         ###   ########.fr       */
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

int	exit_heredoc(int err_code, char *heredoc_name, t_cmdlist *cmdlst)
{
	int	fd;
	int	status;

	status = WEXITSTATUS(err_code);
	if (status == 130)
	{
		unlink(heredoc_name);
		free(heredoc_name);
		return (0);
	}
	fd = open(heredoc_name, O_RDONLY);
	unlink(heredoc_name);
	free(heredoc_name);
	cmdlst->fd_in = fd;
	return (1);
}

void	exit_heredoc_process(char *line, char *heredoc_name, t_ms *ms)
{
	free(line);
	free(heredoc_name);
	rl_clear_history();
	free_cmdlist(ms->cmdlist);
	free(ms->prompt);
	ft_free_tab(ms->env);
}

void	here_doc_process(t_cmdlist *cmdlst, t_redirlst \
		*redir, t_ms *ms, char *heredoc_name)
{
	char	*line;
	int		fd;

	rl_catch_signals = 1;
	signal_state_manager(2);
	line = NULL;
	fd = open(heredoc_name, O_EXCL | O_CREAT | O_WRONLY, 0600);
	while (1)
	{
		free(line);
		line = readline(">");
		if (!line || (!ft_strncmp(redir->file, line, \
ft_strlen(redir->file) + 1)))
			break ;
		ft_putendl_fd(line, fd);
	}
	if (!line && g_exit != 130)
		ft_dprintf (2, "bash: warning: here-document at line 1 delimited\
 by end-of-file (wanted `%s')\n", cmdlst->redir->file);
	exit_heredoc_process(line, heredoc_name, ms);
	close(fd);
	exit(g_exit);
}

int	here_doc(t_cmdlist *cmdlst, t_redirlst *redir, t_ms *ms)
{
	int		pid;
	char	*heredoc_name;
	int		err_code;

	signal_state_manager(1);
	heredoc_name = ft_random();
	pid = fork();
	if (pid == 0)
		here_doc_process(cmdlst, redir, ms, heredoc_name);
	waitpid(pid, &err_code, 0);
	err_code = exit_heredoc(err_code, heredoc_name, cmdlst);
	signal_state_manager(0);
	return (err_code);
}
