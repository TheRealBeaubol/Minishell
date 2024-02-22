/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:50:25 by mhervoch          #+#    #+#             */
/*   Updated: 2024/02/22 20:34:28 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"
#include <unistd.h>

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

	i = 0;
	len = ft_lstsize(ms->lst);
	data->cmd = malloc (sizeof(char *) * (len + 1));
	while (ms->lst)
	{
		next = ms->lst->next;
		if (ms->lst->content[0] == '-')
			data->cmd[i] = ft_strdup(ms->lst->content);
		ms->lst = next;
		i++;
	}
	data->fd_in = open(ms->lst->next->content, O_RDONLY, 0777);
	//data->fd_out =
}

//a finir pour executer les commande

void	exec(t_ms *ms)
{
	char	*path;
	t_data	data;
	int		pid;

	initialyse_data(ms, &data);
	path = get_path(data.cmd[0], ms->env);
	dup2(data.fd_in, STDIN_FILENO);
	//dup2(data.fd_out, STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
		execve(path, data.cmd, ms->env);
}

int	choose_cmd(t_ms *ms)
{
	if (!ft_strncmp(ms->lst->content, "cd", ft_strlen(ms->lst->content)))
		change_directory(ms);
	else if (!ft_strncmp(ms->lst->content, "pwd", ft_strlen(ms->lst->content)))
		printf("%s\n", getcwd(NULL, 0));
		// pwd(ms);
	else
		exec(ms);
	return (0);
}
