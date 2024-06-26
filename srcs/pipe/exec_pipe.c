/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 06:13:52 by mhervoch          #+#    #+#             */
/*   Updated: 2024/05/02 22:56:18 by lboiteux         ###   ########.fr       */
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

int	check_perms(char *cmd)
{
	struct stat	stats;

	ft_memset(&stats, 0, sizeof(struct stat));
	stat(cmd, &stats);
	if (S_ISREG(stats.st_mode))
	{
		if (access(cmd, X_OK) == -1)
		{
			g_exit = 126;
			ft_dprintf(2, "minishell: %s: Permission denied\n", cmd);
			return (0);
		}
	}
	return (1);
}

void	child_no_pipe_process(char **env, \
		t_cmdlist *cmdlst, t_pipe *data, t_ms *ms)
{
	if (cmdlst->fd_out == -1 || cmdlst->fd_in == -1)
		close_and_free_exec(ms, data, 4, NULL);
	if (cmdlst->fd_out != -2)
		dup2(cmdlst->fd_out, STDOUT_FILENO);
	if (!data->cmd && !is_builtin(cmdlst->param[0]))
		close_and_free_exec(ms, data, 3, cmdlst->param[0]);
	if (cmdlst->fd_in != -2)
		dup2(cmdlst->fd_in, STDIN_FILENO);
	close_fds(ms->cmdlist);
	close(data->stdin_dup);
	close(data->stdout_dup);
	if (is_builtin(cmdlst->param[0]))
		exec_builtin(cmdlst, cmdlst->param[0], ms, 1);
	else if (cmdlst->fd_in != -1)
	{
		if (!ft_strncmp(data->cmd, "|", 1))
			free_exec(ms, data, 1);
		execve(data->cmd, cmdlst->param, env);
		g_exit = 127;
		if (!check_perms(cmdlst->param[0]))
			free_exec(ms, data, 1);
		ft_dprintf(2, "Command not found : %s\n", cmdlst->param[0]);
	}
	free_exec(ms, data, 1);
}
