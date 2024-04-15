/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:35:16 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/15 17:26:21 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
int	check_file(char *cmd)
{
	struct stat stats;

	if (access(cmd, F_OK) == -1)
	{
		ft_dprintf(2, "minishell: %s: No such file or directory\n", cmd);
		g_exit = 127	;
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


	if (ft_strchr(cmdlst->cmd, '/'))
	{
		if (!check_file(cmdlst->cmd))
			return (-1);
		data->cmd = ft_strdup(cmdlst->cmd);
	}
	else
		data->cmd = get_cmd_path(grep(env), cmdlst->cmd);
	pipe(data->pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		close(data->stdin_dup);
		exec(env, cmdlst, data, ms);
		free_exec(ms, data, 1);
	}
	close(data->pipe_fd[1]);
	dup2(data->pipe_fd[0], STDIN_FILENO);
	close(data->pipe_fd[0]);
	free_exec(ms, data, 0);
	return (pid);
}

int	no_pipe_process(char **env, t_cmdlist *cmdlst, t_pipe *data, t_ms *ms)
{
	int		pid;


	if (cmdlst->cmd[0] == '\0')
	{
		g_exit = 0;
		return (-1);
	}
	if (ft_strchr(cmdlst->cmd, '/'))
	{
		if (!check_file(cmdlst->cmd))
			return (-1);
		data->cmd = ft_strdup(cmdlst->cmd);
	}
	else
		data->cmd = get_cmd_path(grep(env), cmdlst->cmd);
	pid = fork();
	if (pid == 0)
	{
		close(data->stdin_dup);
		if (is_builtin(cmdlst->cmd))
			exec_builtin(cmdlst, cmdlst->cmd, ms);
		else
		{
			execve(data->cmd, cmdlst->param, env);
			g_exit = 127;
			ft_dprintf(2, "Command not found\n");
		}
		free_exec(ms, data, 1);
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
	data->stdin_dup = dup(STDIN_FILENO);
	while (tmp)
	{
		if (tmp->next)
			data->pid[i++] = process(ms->env, tmp, data, ms);
		else
			data->pid[i++] = no_pipe_process(ms->env, tmp, data, ms);
		if (data->pid[i - 1] == -1)
		{
			close(data->stdin_dup);
			free_exec(ms, data, 2);
			return ;
		}
		tmp = tmp->next;
	}
	dup2(data->stdin_dup, STDIN_FILENO);
	close(data->stdin_dup);
	err_code = 0;
	j = 0;
	while (j < i)
		waitpid(data->pid[j++], &err_code, 0);
	g_exit = get_exit_code(err_code);
	free_exec(ms, data, 2);
	return ;
}
