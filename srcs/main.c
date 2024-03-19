/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:35:59 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/19 16:46:28 by lboiteux         ###   ########.fr       */
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
	ms.env = my_env(env);
	ms.data = &data;
	ms.data->fd_in = 0;
	ms.data->fd_out = 0;
	ms.data->cmd = NULL;
	ms.path = &path;
	ms.lst = NULL;
	ms.prompt = get_prompt(&ms);
	rl_catch_signals = 0;
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		get_single_input(&ms, ft_strdup(av[2]));
		exit(g_exit);
	}
	get_input(&ms);
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_ms	ms;
// 	t_data	data;
// 	t_path	path;

// 	if (ac != 1)
// 		return (1);
// 	g_exit = 0;
// 	ms.ac = ac;
// 	ms.av = av;
// 	ms.env = my_env(env);
// 	ms.data = &data;
// 	ms.data->fd_in = 0;
// 	ms.data->fd_out = 0;
// 	ms.data->cmd = NULL;
// 	ms.path = &path;
// 	ms.lst = NULL;
// 	ms.prompt = get_prompt(&ms);
// 	get_input(&ms);
// 	return (0);
// }
