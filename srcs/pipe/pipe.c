/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:35:16 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/06 20:06:52 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	get_pipe(char *content, int i, t_list **pipeline)
{
	char	*tmp;
	int		j;

	j = i;
	if (!content)
		return (0);
	while (content[j] && content[j] != '|')
		j++;
	tmp = ft_calloc(j + 2, sizeof(char));
	if (!tmp)
		return (0);
	j = 0;
	while (content[i] && content[i] != '|')
		tmp[j++] = content[i++];
	ft_lstadd_back(pipeline, ft_lstnew(ft_strdup(tmp)));
	return (i);
}

int	handle_pipe_quote(char *content, int i, char c, t_list **pipeline)
{
	char	*tmp;
	int		j;

	j = i + 1;
	if (!content)
		return (0);
	while (content[j] && content[j] != c)
		j++;
	tmp = ft_calloc(j + 2, sizeof(char));
	if (!tmp)
		return (0);
	j = 0;
	while (content[i] && content[i] != c)
		tmp[j++] = content[i++];
	tmp[j] = content[i++];
	ft_lstadd_back(pipeline, ft_lstnew(ft_strdup(tmp)));
	return (i);
}

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

char	*init_pipeline(char *content)
{
	int		i;
	char	*tmp;

	i = 0;
	while (content[i] && content[i] != '|')
		i++;
	tmp = ft_calloc(i + 2, sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (content[i] && content[i] != '|')
	{
		tmp[i] = content[i];
		i++;
	}
	return (tmp);
}

t_list	*get_pipeline(t_list *lst)
{
	t_list	*pipeline;
	t_list	*tmp;
	int		i;
	int		start;
	char	*str;

	start = 0;
	if (!lst)
		return (NULL);
	tmp = lst;
	str = init_pipeline(tmp->content);
	if (!str)
		return (NULL);
	pipeline = ft_lstnew(str);
	while (tmp)
	{
		i = 0;
		if (!start++)
			i = ft_strlen(pipeline->content);
		while (tmp->content[i])
		{
			if (tmp->content[i] == '"' || tmp->content[i] == '\'')
				i = handle_pipe_quote(tmp->content, i, \
					tmp->content[i], &pipeline);
			else if (tmp->content[i] == '|')
			{
				ft_lstadd_back(&pipeline, ft_lstnew(ft_strdup("|")));
				i++;
			}
			else
				i = get_pipe(tmp->content, i, &pipeline);
		}
		tmp = tmp->next;
	}
	return (pipeline);
}

// void	print_tokens(t_list *pipeline)
// {
// 	t_list	*tmp;
// 	int		i;

// 	i = 1;
// 	tmp = pipeline;
// 	while (tmp)
// 	{
// 		ft_printf("Element number : {%d}\n	-->[%s]\n", i, tmp->content);
// 		tmp = tmp->next;
// 		i++;
// 	}
// }

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