/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:50:25 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/08 15:17:14 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*grep(char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (strncmp(env[i], "PATH=", 5))
		i++;
	path = malloc(sizeof(char) * ft_strlen(env[i]) - 5);
	path = env[i] + 5;
	return (path);
}

char	*get_path(char *av, char **env)
{
	char	**dec_path;
	char	*path;
	char	*new_path;
	int		i;
	char	*commande;

	path = grep(env);
	dec_path = ft_char_split(av, ' ');
	commande = ft_strjoin("/", dec_path[0]);
	i = 0;
	dec_path = ft_char_split(path, ':');
	while (dec_path[i] && access(ft_strjoin(dec_path[i], commande), X_OK) == -1)
		i++;
	if (!dec_path[i])
		return (NULL);
	new_path = malloc(sizeof(char) * \
			ft_strlen(ft_strjoin(dec_path[i], commande)));
	new_path = ft_strjoin(dec_path[i], commande);
	return (new_path);
}

void	initialyse_data(t_ms *ms, t_data *data)
{
	int		len;
	int		i;
	t_list	*next;
	t_list	*tmp;

	data->fd_in = 0;
	data->fd_out = 0;
	tmp = ms->lst;
	i = 0;
	len = ft_lstsize(ms->lst);
	data->cmd = malloc(sizeof(char *) * (len + 1));
	data->cmd[0] = ft_strdup(tmp->content);
	tmp = tmp->next;
	i++;
	while (i < len)
	{
		next = tmp->next;
		if (tmp->content[0] == '-')
			data->cmd[i] = ft_strdup(tmp->content);
		else
		{
			i++;
			break ;
		}
		tmp = next;
		i++;
	}
	if (i++ < len)
		data->fd_in = open(tmp->content, O_RDONLY);
		//data->fd_in = open(ms->lst->next->content, O_RDONLY);
	if (i < len)
		data->fd_out = open(tmp->next->content, O_RDONLY | O_CREAT | O_TRUNC, 0777);
	//data->fd_out = open(ms->lst->next->next->content, O_RDONLY | O_CREAT | O_TRUNC, 0777);
	//if (data->fd_out)
		//data->fd_out = 1;
}

//a finir pour executer les commande

void	exec(t_ms *ms)
{
	char	*path;
	t_data	data;
	int		pid;

	initialyse_data(ms, &data);
	path = get_path(data.cmd[0], ms->env);
	pid = fork();
	if (pid == 0)
	{
		if (data.fd_in)
			dup2(data.fd_in, STDIN_FILENO);
		if (data.fd_out)
			dup2(data.fd_out, STDIN_FILENO);
		close(data.fd_in);
		close(data.fd_out);
		if (execve(path, data.cmd, ms->env) == -1)
			printf("Command not found\n");
			//perror("Command not found\n");
	}
	else
		waitpid(pid, NULL, 0);
}

int	choose_cmd(t_ms *ms)
{
	if (!ft_strncmp(ms->lst->content, "cd", 2))
		change_directory(ms);
	else if (!ft_strncmp(ms->lst->content, "pwd", 3))
		printf("%s\n", getcwd(NULL, 0));
	else if (!ft_strncmp(ms->lst->content, "unset", 5))
		unset(ms, ms->lst->next->content);
	else if (!ft_strncmp(ms->lst->content, "env", 3))
		env(ms);
	else if (!ft_strncmp(ms->lst->content, "echo", 4))
		echo(ms);
	else if (!ft_strncmp(ms->lst->content, "exit", 4))
		return (42);
	else
		exec(ms);
	return (0);
}
