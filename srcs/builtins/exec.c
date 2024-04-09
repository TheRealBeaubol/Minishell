/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:50:25 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/09 14:00:43 by lboiteux         ###   ########.fr       */
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
	else if (!ft_strncmp(cmd, "export", 7))
		export(cmdlst, ms);
	else if (!ft_strncmp(cmd, "exit", 5))
		exit_function(cmdlst, ms);
}
