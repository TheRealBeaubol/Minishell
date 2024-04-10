/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:35:16 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/10 18:44:54 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	exec(char **env, t_cmdlist *cmdlst, t_pipe *data)
{
	dup2(data->input_fd, STDIN_FILENO);
	close(data->pipe_fd[0]);
	if (cmdlst->next)
		dup2(data->pipe_fd[1], STDOUT_FILENO);
	close(data->pipe_fd[1]);
	execve(data->cmd, cmdlst->param, env);
	close (data->input_fd);
}

int	process(char **env, t_cmdlist *cmdlst, t_pipe *data, t_ms *ms)
{
	int		pid;

	pipe(data->pipe_fd);
	if (!data->input_fd)
		data->input_fd = data->pipe_fd[0];
	pid = fork();
	data->cmd = get_cmd(grep(env), cmdlst->cmd);
	if (pid == 0)
	{
		if (is_builtin(cmdlst->cmd))
		{
			exec_builtin(cmdlst, cmdlst->cmd, ms);
			close(data->pipe_fd[1]);
			// close(data->pipe_fd[0]);
			close(data->input_fd);
		}
		else
			exec(env, cmdlst, data);
		free_cmdlist(ms->cmdlist);
		ft_free_tab(env);
		free(ms->input);
		free(ms->prompt);
		free(data->cmd);
		free(data);
		rl_clear_history();
		exit(g_exit);
	}
	else
	{
		close(data->pipe_fd[1]);
		data->input_fd = dup(data->pipe_fd[0]);
		close(data->pipe_fd[0]);
	}
	free(ms->prompt);
	ms->prompt = get_prompt(ms);
	free(data->cmd);
	return (pid);
}

t_cmdlist	*cmd_list_init(t_ms *ms)
{
	t_cmdlist	*cmdlist;

	ms->cmdlist = ft_calloc(2, sizeof(t_cmdlist));
	if (!ms->cmdlist)
		return (NULL);
	cmdlist = ms->cmdlist;
	cmdlist->param = ft_calloc(2, sizeof(char *));
	if (!cmdlist->param)
		return (NULL);
	cmdlist->next = NULL;
	return (cmdlist);
}

void	do_cmd_list(t_ms *ms)
{
	t_cmdlist	*tmpcmdlist;
	t_list		*tmp;
	int			is_cmd;

	is_cmd = 0;
	tmp = ms->lst;
	tmpcmdlist = cmd_list_init(ms);
	while (tmp)
	{
		if (!is_cmd++)
			tmpcmdlist->cmd = ft_strdup(tmp->content);
		if (!is_cmd++)
			tmpcmdlist->param[0] = ft_strdup(tmp->content);
		else if (ft_strncmp(tmp->content, "|", 2) == 0)
		{
			tmpcmdlist->next = ft_calloc(2, sizeof(t_cmdlist));
			tmpcmdlist = tmpcmdlist->next;
			tmpcmdlist->param = ft_calloc(2, sizeof(char *));
			is_cmd = 0;
		}
		else
			tmpcmdlist->param = ft_join_tab(tmpcmdlist->param, tmp->content);
		tmp = tmp->next;
	}
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
	if (!data)
		return ;
	data->input_fd = 0;
	while (tmp)
	{
		err_code = 0;
		data->pid[i++] = process(ms->env, tmp, data, ms);
		tmp = tmp->next;
	}
	j = 0;
	while (j < i)
		waitpid(data->pid[j++], &err_code, 0);
	g_exit = get_exit_code(err_code);
	free(ms->prompt);
	ms->prompt = get_prompt(ms);
	close(data->input_fd);
	free(data);
	return ;
}
