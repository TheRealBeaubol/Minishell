/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:35:59 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/19 19:59:09 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	g_exit;

int	main(int ac, char **av, char **env)
{
	t_ms	ms;
	t_data	data;
	t_path	path;

	g_exit = 0;
	(void)ac;
	(void)av;
	ms.env = my_env(env);
	ms.data = &data;
	ms.data->fd_in = 0;
	ms.data->fd_out = 0;
	ms.data->cmd = NULL;
	ms.path = &path;
	ms.lst = NULL;
	ms.prompt = get_prompt(&ms);
	rl_catch_signals = 0;
	get_input(&ms);
	return (0);
}
