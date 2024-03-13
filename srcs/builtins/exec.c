/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:50:25 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/13 23:25:42 by mhervoch         ###   ########.fr       */
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
	ms->path->commande = ft_strjoin("/", ms->path->dec_path[0], NULL, 0b000);
	i = 0;
	ft_free_tab(ms->path->dec_path);
	ms->path->dec_path = ft_char_split(ms->path->path_str, ':');
	ms->path->str = ft_strjoin(ms->path->dec_path[i], ms->path->commande, \
	NULL, 0b000);
	while (ms->path->dec_path[i++] && access(ms->path->str, X_OK) == -1)
	{
		free(ms->path->str);
		ms->path->str = ft_strjoin(ms->path->dec_path[i], \
		ms->path->commande, NULL, 0b000);
	}
	ft_free_tab(ms->path->dec_path);
	free(ms->path->commande);
	free(ms->path->path_str);
}

void	initialyse_data(t_ms *ms)
{
	int		len;
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = ms->lst;
	len = ft_lstsize(ms->lst);
	ms->data->cmd = ft_calloc((len + 1), sizeof(char *));
	ms->data->cmd[0] = ft_strdup(ms->lst->content);
	tmp = tmp->next;
	i++;
	while (tmp)
	{
		ms->data->cmd[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
}

void	exec(t_ms *ms)
{
	int		pid;

	initialyse_data(ms);
	get_path(ms);
	pid = fork();
	if (pid == 0)
	{
		execve(ms->path->str, ms->data->cmd, ms->env);
		printf("Command not found\n");
		rl_clear_history();
		ft_free_tab(ms->data->cmd);
		free(ms->path->str);
		free(ms->prompt);
		ft_free_list(&ms->lst);
		ft_free_tab(ms->env);
		exit(127);
	}
	waitpid(pid, NULL, 0);
	ft_free_tab(ms->data->cmd);
	ms->data->cmd = NULL;
	free(ms->path->str);
	ft_free_list(&ms->lst);
	free(ms->prompt);
	ms->prompt = get_prompt(ms);
}

int	is_builtin(char *command)
{
	return (!ft_strncmp(command, "cd", 3) || \
	!ft_strncmp(command, "pwd", 4) || \
	!ft_strncmp(command, "unset", 6) || \
	!ft_strncmp(command, "env", 4) || \
	!ft_strncmp(command, "echo", 5) || \
	!ft_strncmp(command, "export", 7) || \
	!ft_strncmp(command, "exit", 5));
}

int	choose_cmd(t_ms *ms)
{
	char	*str;

	if (is_builtin(ms->lst->content))
	{
		if (!ft_strncmp(ms->lst->content, "cd", 3))
			change_directory(ms);
		else if (!ft_strncmp(ms->lst->content, "pwd", 4))
		{
			str = cwdget();
			printf("%s\n", str);
			free(str);
		}
		else if (!ft_strncmp(ms->lst->content, "unset", 6))
			unset(ms, ms->lst->next->content);
		else if (!ft_strncmp(ms->lst->content, "env", 4))
			env(ms);
		else if (!ft_strncmp(ms->lst->content, "echo", 5))
			echo(ms);
		else if (!ft_strncmp(ms->lst->content, "export", 7))
			e_xport(ms);
		else if (!ft_strncmp(ms->lst->content, "exit", 5))
			return (42);
		ft_free_list(&ms->lst);
	}
	else
		exec(ms);
	return (0);
}
