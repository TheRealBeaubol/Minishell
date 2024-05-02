/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 06:11:36 by mhervoch          #+#    #+#             */
/*   Updated: 2024/05/02 22:51:50 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	exec(char **env, t_cmdlist *cmdlst, t_pipe *data, t_ms *ms)
{
	close(data->stdin_dup);
	close(data->stdout_dup);
	if (is_builtin(cmdlst->param[0]))
		format_builtin(cmdlst, data, ms);
	else
		format_exec(env, cmdlst, data, ms);
	free_exec(ms, data, 1);
}

void	close_and_free_exec(t_ms *ms, t_pipe *data, int status, char *err_arg)
{
	if (status == 1 || status == 2)
		close(data->pipe_fd[1]);
	if (status == 2 || status == 3)
	{
		ft_dprintf(2, "minishell: %s: command not found\n", err_arg);
		g_exit = 127;
	}
	close(data->stdin_dup);
	close(data->stdout_dup);
	free_exec(ms, data, 1);
}

void	format_exec(char **env, t_cmdlist *cmdlst, t_pipe *data, t_ms *ms)
{
	close(data->pipe_fd[0]);
	if (cmdlst->fd_out == -1 || cmdlst->fd_in == -1)
		close_and_free_exec(ms, data, 1, NULL);
	if (cmdlst->fd_out == -2)
		dup2(data->pipe_fd[1], STDOUT_FILENO);
	else
		dup2(cmdlst->fd_out, STDOUT_FILENO);
	if (!data->cmd && !is_builtin(cmdlst->param[0]))
		close_and_free_exec(ms, data, 2, cmdlst->param[0]);
	if (cmdlst->fd_in != -2)
		dup2(cmdlst->fd_in, STDIN_FILENO);
	close(data->pipe_fd[1]);
	close_fds(ms->cmdlist);
	if (!ft_strncmp(data->cmd, "|", 1))
		free_exec(ms, data, 1);
	execve(data->cmd, cmdlst->param, env);
	g_exit = 127;
	if (!check_perms(cmdlst->param[0]))
		free_exec(ms, data, 1);
	ft_dprintf(2, "Command not found\n");
}

void	format_builtin(t_cmdlist *cmdlst, t_pipe *data, t_ms *ms)
{
	close(data->pipe_fd[0]);
	if (cmdlst->fd_out == -1 || cmdlst->fd_in == -1)
	{
		close(data->pipe_fd[1]);
		close(data->stdin_dup);
		close(data->stdout_dup);
		free_exec(ms, data, 1);
	}
	if (cmdlst->fd_out == -2)
		dup2(data->pipe_fd[1], STDOUT_FILENO);
	else
		dup2(cmdlst->fd_out, STDOUT_FILENO);
	if (cmdlst->fd_in != -2)
		dup2(cmdlst->fd_in, STDIN_FILENO);
	close(data->pipe_fd[1]);
	close_fds(ms->cmdlist);
	exec_builtin(cmdlst, cmdlst->param[0], ms, 2);
}
