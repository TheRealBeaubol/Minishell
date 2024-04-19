/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:24:08 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/19 20:06:02 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	ft_free_redir_list(t_redirlst *redir)
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
