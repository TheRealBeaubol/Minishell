/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:50:25 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/11 18:33:30 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*grep(t_ms *ms)
{
	char	*path;
	int		i;

	i = 0;
	while (ft_strncmp(ms->env[i], "PATH=", 5))
		i++;
	path = ft_strdup(ms->env[i] + 5);
	return (path);
}

void	get_path(t_ms *ms)
{
	int		i;

	ms->path->path_str = grep(ms);
	ms->path->dec_path = ft_char_split(ms->data->cmd[0], ' ');
	ms->path->commande = ft_strjoin("/", ms->path->dec_path[0]);
	i = 0;
	ft_free_tab(ms->path->dec_path);
	ms->path->dec_path = ft_char_split(ms->path->path_str, ':');
	ms->path->str = ft_strjoin(ms->path->dec_path[i], ms->path->commande);
	while (ms->path->dec_path[i++] && access(ms->path->str, X_OK) == -1)
	{
		free(ms->path->str);
		ms->path->str = ft_strjoin(ms->path->dec_path[i], ms->path->commande);
	}
	ft_free_tab(ms->path->dec_path);
	free(ms->path->path_str);
}

void	initialyse_data(t_ms *ms)
{
	int		len;
	int		i;
	t_list	*next;
	t_list	*tmp;

	tmp = ms->lst;
	i = 0;
	len = ft_lstsize(ms->lst);
	ms->data->cmd = ft_calloc((len + 1), sizeof(char *));
	ms->data->cmd[0] = ft_strdup(tmp->content);
	tmp = tmp->next;
	i++;
	while (i < len)
	{
		next = tmp->next;
		if (tmp->content[0] == '-')
			ms->data->cmd[i] = ft_strdup(tmp->content);
		else
		{
			i++;
			break ;
		}
		tmp = next;
		i++;
	}
	if (i++ < len)
		ms->data->fd_in = open(tmp->content, O_RDONLY);
		//data->fd_in = open(ms->lst->next->content, O_RDONLY);
	if (i < len)
		ms->data->fd_out = open(tmp->next->content, O_RDONLY | O_CREAT | O_TRUNC, 0777);
	//data->fd_out = open(ms->lst->next->next->content, O_RDONLY | O_CREAT | O_TRUNC, 0777);
	//if (data->fd_out)
		//data->fd_out = 1;
}

//a finir pour executer les commande

void	exec(t_ms *ms)
{
	int		pid;

	initialyse_data(ms);
	get_path(ms);
	pid = fork();
	if (pid == 0)
	{
		if (ms->data->fd_in)
			dup2(ms->data->fd_in, STDIN_FILENO);
		if (ms->data->fd_out)
			dup2(ms->data->fd_out, STDIN_FILENO);
		close(ms->data->fd_in);
		close(ms->data->fd_out);
		if (execve(ms->path->str, ms->data->cmd, ms->env) == -1)
			printf("Command not found\n");
		ft_free_tab(ms->data->cmd);
		free(ms->path->str);
		free(ms->prompt);
		ft_free_list(&ms->lst);
		exit(127);
	}
	waitpid(pid, NULL, 0);
	ms->prompt = get_prompt(ms);
}

int	choose_cmd(t_ms *ms)
{
	if (!ft_strncmp(ms->lst->content, "cd", 3))
		change_directory(ms);
	else if (!ft_strncmp(ms->lst->content, "pwd", 4))
		printf("%s\n", getcwd(NULL, 0));
	else if (!ft_strncmp(ms->lst->content, "unset", 6))
		unset(ms, ms->lst->next->content);
	else if (!ft_strncmp(ms->lst->content, "env", 4))
		env(ms);
	else if (!ft_strncmp(ms->lst->content, "echo", 5))
		echo(ms);
	else if (!ft_strncmp(ms->lst->content, "exit", 5))
		return (42);
	else
		exec(ms);
	return (0);
}
