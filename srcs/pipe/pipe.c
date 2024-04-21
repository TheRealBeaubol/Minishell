/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:35:16 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/21 06:21:10 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	check_file(char *cmd)
{
	struct stat	stats;

	if (access(cmd, F_OK) == -1)
	{
		ft_dprintf(2, "minishell: %s: No such file or directory\n", cmd);
		g_exit = 127;
		return (0);
	}
	if (access(cmd, X_OK) == -1)
	{
		ft_dprintf(2, "minishell: %s: Permission denied\n", cmd);
		g_exit = 126;
		return (0);
	}
	stat(cmd, &stats);
	if (S_ISDIR(stats.st_mode))
	{
		ft_dprintf(2, "minishell: %s: is a directory\n", cmd);
		g_exit = 126;
		return (0);
	}
	return (1);
}

void	close_fds(t_cmdlist *cmdlst)
{
	t_cmdlist	*tmp;

	tmp = cmdlst;
	while (tmp)
	{
		if (tmp->fd_in > 2)
			close(tmp->fd_in);
		if (tmp->fd_out > 2)
			close(tmp->fd_out);
		tmp = tmp->next;
	}
}

int	process(char **env, t_cmdlist *cmdlst, t_pipe *data, t_ms *ms)
{
	int		pid;

	if (!cmdlst->param[0])
	{
		g_exit = 0;
		return (-1);
	}
	if (ft_strchr(cmdlst->param[0], '/'))
	{
		if (!check_file(cmdlst->param[0]))
			return (-1);
		data->cmd = ft_strdup(cmdlst->param[0]);
	}
	else
		data->cmd = get_cmd_path(grep(env), cmdlst->param[0]);
	pipe(data->pipe_fd);
	pid = fork();
	if (pid == 0)
		do_pipe_process(env, cmdlst, data, ms);
	close(data->pipe_fd[1]);
	dup2(data->pipe_fd[0], STDIN_FILENO);
	close(data->pipe_fd[0]);
	free_exec(ms, data, 0);
	return (pid);
}

int	no_pipe_process(\
	char **env, t_cmdlist *cmdlst, t_pipe *data, t_ms *ms)
{
	int		pid;

	if (!cmdlst->param[0])
	{
		g_exit = 0;
		return (-1);
	}
	if (ft_strchr(cmdlst->param[0], '/'))
	{
		if (!check_file(cmdlst->param[0]))
			return (-1);
		data->cmd = ft_strdup(cmdlst->param[0]);
	}
	else
		data->cmd = get_cmd_path(grep(env), cmdlst->param[0]);
	pid = fork();
	if (pid == 0)
		child_no_pipe_process(env, cmdlst, data, ms);
	free(ms->prompt);
	ms->prompt = get_prompt(ms);
	free(data->cmd);
	return (pid);
}

void	do_pipe(t_ms *ms)
{
	t_cmdlist	*tmp;
	t_pipe		*data;
	int			i;

	i = 0;
	tmp = ms->cmdlist;
	if (!check_redir(tmp, ms))
		return ;
	if (tmp->param[0] == NULL)
		return ;
	data = ft_calloc(2, sizeof(t_pipe));
	data->stdin_dup = dup(STDIN_FILENO);
	data->stdout_dup = dup(STDOUT_FILENO);
	if (!tmp->next && is_builtin(tmp->param[0]))
	{
		alone_builtin(tmp, ms, data);
		return ;
	}
	i = exec_pipe(ms, tmp, data);
	if (!i)
		return ;
	check_pid(data, ms, i);
	free_exec(ms, data, 2);
	return ;
}
