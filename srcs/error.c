/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:56:26 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/14 00:06:44 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	free_and_exit(t_ms *ms)
{
	free(ms->input);
	free(ms->prompt);
	ft_free_list(&(ms->lst));
	ft_free_tab(ms->env);
	ft_free_tab(ms->data->cmd);
	exit(g_exit);
}
