/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:35:16 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/08 14:55:01 by lboiteux         ###   ########.fr       */
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
		if (!++is_cmd)
		{
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
// echo "Hello | World" | cat Makefile | ls
void	print_cmd_list(t_cmdlist *cmd)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (cmd)
	{
		i = 0;
		ft_printf("[cmd %d] : %s\n", j, cmd->cmd);
		while (cmd->param[i])
		{
			ft_printf("	->[param][%d] : %s\n", i, cmd->param[i]);
			i++;
		}
		j++;
		cmd = cmd->next;
	}
}

char	*get_cmd(char **path, t_pipe *data)
{
	char	*join_path;
	char	*path_cmd;
	int		i;

	i = -1;
	ft_dprintf(2, "cmd1 : %s\n", data->cmd);
	while (path[++i])
	{
		join_path = ft_strjoin(path[i], "/", NULL, 0b000);
		path_cmd = ft_strjoin(join_path, data->cmd, NULL, 0b000);
		free(join_path);
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
	pid = fork();
	ft_dprintf(2, "cmd : %s\n", data->cmd);
	data->cmd = get_cmd(grep(env), data);
	if (pid == 0)
	{
		close(data->pipe_fd[0]);
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[1]);
		close(data->output_fd);
		if (execve(data->cmd, cmdlist->param, env) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		close(data->pipe_fd[1]);
		dup2(data->pipe_fd[0], STDIN_FILENO);
		close(data->pipe_fd[0]);
		dup2(data->output_fd, STDOUT_FILENO);
		close(data->output_fd);
	}
	return (pid);
}

void	do_pipe(t_cmdlist *cmdlist, t_ms *ms)
{
	t_cmdlist	*tmp;
	t_pipe	*data;
	int		pid[1024];
	int		i;

	i = 0;
	tmp = cmdlist;
	data = ft_calloc(2, sizeof(t_pipe));
	ft_printf("cmdlist\n");
	while (tmp->next)
	{
		pid[i++] = process(ms->env, tmp, data);
		ft_printf("1cmdlist\n");
		tmp = tmp->next;
	}
	data->cmd = get_cmd(grep(ms->env), data);
	if (execve(data->cmd, tmp->param, ms->env) == -1)
		exit(EXIT_FAILURE);
	i = -1;
	while (pid[++i])
		waitpid(pid[i], NULL, 0);
	}
