/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:35:16 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/08 20:45:32 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_pipeline(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '|')
		{
			i++;
			while (ft_iswhitespace(content[i]))
				i++;
			if (content[i] == '|')
				return (0);
		}
		i++;
	}
	return (1);
}

void	print_tokens(t_list *pipeline)
{
	t_list	*tmp;
	int		i;

	i = 1;
	tmp = pipeline;
	while (tmp)
	{
		ft_printf("Element number : {%d}\n	-->[%s]\n", i, tmp->content);
		tmp = tmp->next;
		i++;
	}
}

char	**join_tab(char **tab, char *str)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	new_tab = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = ft_strdup(str);
	ft_free_tab(tab);
	return (new_tab);
}

t_cmdlist	*do_cmd_list(t_ms *ms)
{
	t_cmdlist	*tmpcmdlist;
	t_cmdlist	*cmdlist;
	t_list		*tmp;
	int			is_cmd;

	is_cmd = 0;
	tmp = ms->lst;
	cmdlist = ft_calloc(2, sizeof(t_cmdlist));
	tmpcmdlist = cmdlist;
	tmpcmdlist->param = ft_calloc(2, sizeof(char *));
	while (tmp)
	{
		if (!is_cmd)
		{
			is_cmd = 1;
			tmpcmdlist->cmd = ft_strdup(tmp->content);
			tmpcmdlist->param[0] = ft_strdup(tmp->content);
		}
		else if (ft_strncmp(tmp->content, "|", 2) == 0)
		{
			tmpcmdlist->next = ft_calloc(2, sizeof(t_cmdlist));
			tmpcmdlist = tmpcmdlist->next;
			tmpcmdlist->next = NULL;
			tmpcmdlist->param = ft_calloc(2, sizeof(char *));
			is_cmd = 0;
		}
		else
			tmpcmdlist->param = join_tab(tmpcmdlist->param, tmp->content);
		tmp = tmp->next;
	}
	return (cmdlist);
}
void	free_cmdlist(t_cmdlist *cmdlist)
{
	t_cmdlist	*tmp;

	while (cmdlist)
	{
		tmp = cmdlist->next;
		ft_free_tab(cmdlist->param);
		free(cmdlist->cmd);
		free(cmdlist);
		cmdlist = tmp;
	}
}

void	free_pipe(t_ms *ms, int err_code, t_cmdlist	*cmdlist)
{
	g_exit = get_exit_code(err_code);
	free_cmdlist(cmdlist);
	ft_free_list(&ms->lst);
	ms->lst = NULL;
	free(ms->prompt);
	ms->prompt = get_prompt(ms);
}

char	*get_cmd(char **path, char *cmd)
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

int	process(char **env, t_cmdlist *cmdlist, t_pipe *data)
{
	int		pid;

	pipe(data->pipe_fd);
	if (!data->input_fd)
		data->input_fd = data->pipe_fd[0];
	pid = fork();
	data->cmd = get_cmd(grep(env), cmdlist->cmd);
	if (pid == 0)
	{
		dup2(data->input_fd, STDIN_FILENO);
		close(data->pipe_fd[0]);
		if (cmdlist->next)
			dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[1]);
		execve(data->cmd, cmdlist->param, env);
		close (data->input_fd);
		free(data->cmd);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(data->pipe_fd[1]);
		data->input_fd = dup(data->pipe_fd[0]);
 		close(data->pipe_fd[0]);
	}
	free(data->cmd);
	return (pid);
}

void	do_pipe(t_cmdlist *cmdlist, t_ms *ms)
{
	t_cmdlist	*tmp;
	t_pipe		*data;
	int			pid[1024];
	int			i;
	int			j;
	int			err_code;

	i = 0;
	tmp = cmdlist;
	data = ft_calloc(2, sizeof(t_pipe));
	data->input_fd = 0;
	while (tmp)
	{
		err_code = 0;
		pid[i++] = process(ms->env, tmp, data);
		tmp = tmp->next;
	}
	j = 0;
	while (j < i)
		waitpid(pid[j++], &err_code, 0);
	free_pipe(ms, err_code, cmdlist);
	free(data);
	return ;
}
