/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:35:16 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/14 13:56:24 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	exec(char **env, t_cmdlist *cmdlst, t_pipe *data, t_ms *ms)
{
	if (is_builtin(cmdlst->cmd))
	{
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		exec_builtin(cmdlst, cmdlst->cmd, ms);
	}
	else
	{
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		execve(data->cmd, cmdlst->param, env);
		g_exit = 127;
		ft_dprintf(2, "Command not found\n");
	}
}

int	process(char **env, t_cmdlist *cmdlst, t_pipe *data, t_ms *ms)
{
	int		pid;

	pipe(data->pipe_fd);
	pid = fork();
	if (ft_strchr(cmdlst->cmd, '/'))
		data->cmd = ft_strdup(cmdlst->cmd);
	else
		data->cmd = get_cmd_path(grep(env), cmdlst->cmd);
	if (pid == 0)
	{
		exec(env, cmdlst, data, ms);
		free_exec(ms, data, 1);
	}
	if (cmdlst->next)
	{
		close(data->pipe_fd[1]);
		dup2(data->pipe_fd[0], STDIN_FILENO);
		close(data->pipe_fd[0]);
	}
	free_exec(ms, data, 0);
	return (pid);
}

int	no_pipe_process(char **env, t_cmdlist *cmd, t_pipe *data, t_ms *ms)
{
	int		pid;

	pid = fork();
	if (ft_strchr(cmd->cmd, '/'))
		data->cmd = ft_strdup(cmd->cmd);
	else
		data->cmd = get_cmd_path(grep(env), cmd->cmd);
	if (pid == 0)
	{
		if (is_builtin(cmd->cmd))
			exec_builtin(cmd, cmd->cmd, ms);
		else
		{
			execve(data->cmd, cmd->param, env);
			g_exit = 127;
			ft_dprintf(2, "Command not found\n");
		}
	}
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
	int			j;
	int			err_code;

	i = 0;
	tmp = ms->cmdlist;
	if (!tmp->next && is_builtin(tmp->cmd))
	{
		exec_builtin(tmp, tmp->cmd, ms);
		return ;
	}
	data = ft_calloc(2, sizeof(t_pipe));
	while (tmp)
	{
		if (tmp->next)
			data->pid[i++] = process(ms->env, tmp, data, ms);
		else
			data->pid[i++] = no_pipe_process(ms->env, tmp, data, ms);
		tmp = tmp->next;
	}
	err_code = 0;
	j = 0;
	while (j < i)
		waitpid(data->pid[j++], &err_code, 0);
	g_exit = get_exit_code(err_code);
	free_exec(ms, data, 2);
	return ;
}
