/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:39:17 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/23 17:01:30 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	get_exit_code(int err_code)
{
	if (!WIFEXITED(err_code) && WCOREDUMP(err_code))
	{
		ft_dprintf(2, "Quit (core dumped)\n");
		return (131);
	}
	if (WTERMSIG(err_code) == 2)
	{
		ft_dprintf(2, "\n");
		return (130);
	}
	return (WEXITSTATUS(err_code));
}

char	**grep(char **env)
{
	int		i;
	char	*cut_split;
	char	**splited_path;

	i = 0;
	if (!env || !*env)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env || !env[i])
		return (NULL);
	if (!ft_strncmp(env[i], "PATH=", 6))
		return (NULL);
	cut_split = ft_strcut(env[i], "PATH=");
	splited_path = ft_char_split(cut_split, ':');
	free(cut_split);
	return (splited_path);
}

char	*get_cmd_path(char **path, char *cmd)
{
	char	*path_cmd;
	int		i;

	i = -1;
	if (!path || !path[0])
		return (NULL);
	while (path[++i])
	{
		path_cmd = ft_strjoin(path[i], cmd, "/", 0b000);
		if (access(path_cmd, 0) == 0)
		{
			ft_free_tab(path);
			return (path_cmd);
		}
		if (path[i + 1])
			free(path_cmd);
	}
	ft_free_tab(path);
	return (path_cmd);
}

void	free_exec(t_ms *ms, t_pipe *data, int is_free_type)
{
	if (is_free_type == 1)
	{
		free_cmdlist(ms->cmdlist);
		ft_free_tab(ms->env);
		free(ms->input);
		free(ms->prompt);
		free(data->cmd);
		data->cmd = NULL;
		free(data);
		rl_clear_history();
		exit(g_exit);
	}
	else if (!is_free_type)
	{
		free(ms->prompt);
		ms->prompt = get_prompt(ms);
		free(data->cmd);
	}
	else if (is_free_type == 2)
	{
		free(ms->prompt);
		ms->prompt = get_prompt(ms);
		free(data);
	}
}

void	alone_builtin(t_cmdlist *tmp, t_ms *ms, t_pipe *data)
{
	if (tmp->fd_out == -1 || tmp->fd_in == -1)
		return ;
	if (tmp->fd_out != -2)
		dup2(tmp->fd_out, STDOUT_FILENO);
	if (tmp->fd_in != -2)
		dup2(tmp->fd_in, STDIN_FILENO);
	if (tmp->fd_in > 2)
		close(tmp->fd_in);
	if (tmp->fd_out > 2)
		close(tmp->fd_out);
	exec_builtin(tmp, tmp->param[0], ms);
	dup2(data->stdin_dup, STDIN_FILENO);
	dup2(data->stdout_dup, STDOUT_FILENO);
	close(data->stdin_dup);
	close(data->stdout_dup);
	free(data);
}
