/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:39:17 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/10 18:44:14 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int	check_pipeline(char *content)
{
	int		i;
	char	c;

	i = 0;
	while (content[i])
	{
		if (content[i] == '"' || content[i] == '\'')
		{
			c = content[i++];
			while (content[i] && content[i] != c)
				i++;
			if (content[i] == '\0')
				return (1);
		}
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

void	free_cmdlist(t_cmdlist *cmdlist)
{
	t_cmdlist	*tmp;
	t_cmdlist	*next;

	tmp =  cmdlist;
	while (tmp)
	{
		free(tmp->cmd);
		ft_free_tab(tmp->param);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
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