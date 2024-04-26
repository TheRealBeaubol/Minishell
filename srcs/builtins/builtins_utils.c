/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:27:50 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/26 14:30:09 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_and_close_exit_function(t_ms *ms)
{
	free(ms->pipe->cmd);
	close(ms->pipe->stdin_dup);
	close(ms->pipe->stdout_dup);
	free(ms->pipe);
	free_and_exit(ms);
}
