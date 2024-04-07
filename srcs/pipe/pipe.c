/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:35:16 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/07 20:07:54 by lboiteux         ###   ########.fr       */
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

/*
PIPEX BONUS A IMPLEMENTER

int	process(char **env, t_data *data)
{
	int		pid;
	char	**split_cmd;

	pipe(data->pipe_fd);
	pid = fork();
	split_cmd = ft_char_split(data->cmd, ' ');
	data->cmd = get_cmd(grep(env), data);
	if (pid == 0)
		do_dup_and_execve(data, split_cmd, env);
	else
	{
		close(data->pipe_fd[1]);
		dup2(data->pipe_fd[0], STDIN_FILENO);
		close(data->pipe_fd[0]);
		dup2(data->output_fd, STDOUT_FILENO);
		close(data->output_fd);
	}
	free(data->cmd);
	ft_free_tab(split_cmd);
	return (pid);
}

void	do_pipe(int ac, char **av, char **env, t_data *data)
{
	char	*path;
	char	**split_cmd;
	int		pid[1024];
	int		i;

	i = 0;
	while (data->i < ac - 2)
	{
		data->cmd = av[data->i++];
		pid[i++] = process(env, data);
	}
	data->cmd = av[ac - 2];
	path = get_cmd(grep(env), data);
	split_cmd = ft_char_split(av[ac - 2], ' ');
	if (execve(path, split_cmd, env) == -1)
	{
		free(path);
		ft_free_tab(split_cmd);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (pid[++i])
		waitpid(pid[i], NULL, 0);
	free(path);
	ft_free_tab(split_cmd);
}
*/