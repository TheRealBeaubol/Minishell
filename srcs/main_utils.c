/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:58:02 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/19 15:29:33 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_free_redir_list(t_redirlst *redir)
{
	t_redirlst	*tmp;
	t_redirlst	*next;

	tmp = redir;
	while (tmp)
	{
		free(tmp->file);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	free_cmdlist(t_cmdlist *cmdlist)
{
	t_cmdlist	*tmp;
	t_cmdlist	*next;

	tmp = cmdlist;
	while (tmp)
	{
		ft_free_redir_list(tmp->redir);
		ft_free_tab(tmp->param);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	free_and_exit(t_ms *ms)
{
	rl_clear_history();
	free(ms->input);
	free(ms->prompt);
	ft_free_list(ms->lst);
	free_cmdlist(ms->cmdlist);
	ft_free_tab(ms->env);
	ft_free_tab(ms->data->cmd);
	exit(g_exit);
}

char	**my_env(char **env)
{
	int		i;
	char	**envp;

	i = 0;
	while (env[i])
		i++;
	envp = ft_calloc(i + 1, sizeof(char *));
	if (!envp)
	{
		ft_dprintf(2, "ENV EMPTY ERROR\n");
		return (NULL);
	}
	i = -1;
	while (env[++i])
		envp[i] = ft_strdup(env[i]);
	return (envp);
}

int	is_skip(t_ms *ms)
{
	int	i;

	i = -1;
	if ((ms->input[0] == '!' || ms->input[0] == ':') \
		&& ms->input[1] == '\0')
		return (1);
	while ((9 <= ms->input[++i] && ms->input[i] <= 13) || ms->input[i] == 32)
		if (ms->input[i + 1] == '\0')
			return (1);
	return (0);
}
