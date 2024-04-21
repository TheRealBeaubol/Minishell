/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:39:17 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/21 05:01:14 by lboiteux         ###   ########.fr       */
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
