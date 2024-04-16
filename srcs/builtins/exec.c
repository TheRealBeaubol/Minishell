/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:50:25 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/16 14:48:13 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_builtin(char *cmd)
{
	return (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "pwd", 4) || \
		!ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4) || \
		!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "export", 7) || \
		!ft_strncmp(cmd, "exit", 5));
}

void	exec_builtin(t_cmdlist *cmdlst, char *cmd, t_ms *ms)
{
	if (!ft_strncmp(cmd, "cd", 3))
		change_directory(cmdlst, ms);
	else if (!ft_strncmp(cmd, "pwd", 4))
		get_cwd(1);
	else if (!ft_strncmp(cmd, "unset", 6))
		unset(cmdlst, cmd, ms);
	else if (!ft_strncmp(cmd, "env", 4))
		env(cmdlst, ms);
	else if (!ft_strncmp(cmd, "echo", 5))
		echo(cmdlst);
	else if (!ft_strncmp(cmd, "export", 7) && !cmdlst->next)
		export(cmdlst, ms);
	else if (!ft_strncmp(cmd, "exit", 5))
		exit_function(cmdlst, ms);
}

void	init_and_launch_exec(t_ms *ms)
{
	do_cmd_list(ms);
	ft_free_list(&ms->lst);
	ms->lst = NULL;
	signal_state_manager(1);
	do_pipe(ms);
	signal_state_manager(0);
	free_cmdlist(ms->cmdlist);
	ms->cmdlist = NULL;
}
