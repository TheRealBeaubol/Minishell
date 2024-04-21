/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 06:13:52 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/21 06:16:38 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	exec_pipe(t_ms *ms, t_cmdlist *tmp, t_pipe *data)
{
	int	i;

	i = 0;
	while (tmp)
	{
		if (tmp->next)
			data->pid[i++] = process(ms->env, tmp, data, ms);
		else
			data->pid[i++] = no_pipe_process(ms->env, tmp, data, ms);
		if (data->pid[i - 1] == -1)
		{
			dup2(data->stdin_dup, STDIN_FILENO);
			dup2(data->stdout_dup, STDOUT_FILENO);
			close(data->stdin_dup);
			close(data->stdout_dup);
			free_exec(ms, data, 2);
			return (0);
		}
		tmp = tmp->next;
	}
	return (i);
}

void	check_pid(t_pipe *data, t_ms *ms, int i)
{
	int	j;
	int	err_code;

	err_code = 0;
	j = 0;
	close_fds(ms->cmdlist);
	dup2(data->stdin_dup, STDIN_FILENO);
	close(data->stdin_dup);
	close(data->stdout_dup);
	err_code = 0;
	j = 0;
	while (j < i)
		waitpid(data->pid[j++], &err_code, 0);
	g_exit = get_exit_code(err_code);
}

int	check_redir(t_cmdlist *tmp, t_ms *ms)
{
	redirection(tmp, ms);
	while (tmp)
	{
		if (tmp->fd_in == -3)
			return (0);
		tmp = tmp->next;
	}
	tmp = ms->cmdlist;
	return (1);
}

void	child_no_pipe_process(char **env, \
		t_cmdlist *cmdlst, t_pipe *data, t_ms *ms)
{
	if (cmdlst->fd_out == -1 || cmdlst->fd_in == -1)
	{
		close(data->stdin_dup);
		close(data->stdout_dup);
		free_exec(ms, data, 1);
	}
	if (cmdlst->fd_out != -2)
		dup2(cmdlst->fd_out, STDOUT_FILENO);
	if (cmdlst->fd_in != -2)
		dup2(cmdlst->fd_in, STDIN_FILENO);
	close_fds(ms->cmdlist);
	close(data->stdin_dup);
	close(data->stdout_dup);
	if (is_builtin(cmdlst->param[0]))
		exec_builtin(cmdlst, cmdlst->param[0], ms);
	else if (cmdlst->fd_in != -1)
	{
		if (!ft_strncmp(data->cmd, "|", 1))
			free_exec(ms, data, 1);
		execve(data->cmd, cmdlst->param, env);
		g_exit = 127;
		ft_dprintf(2, "Command not found\n");
	}
	free_exec(ms, data, 1);
}
