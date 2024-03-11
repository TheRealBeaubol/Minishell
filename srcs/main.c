/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:35:59 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/11 18:38:51 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	main(int ac, char **av, char **env)
{
	t_ms	ms;
	t_data	data;
	t_path	path;

	if (ac != 1)
		return (1);
	ms.ac = ac;
	ms.av = av;
	ms.env = env;
	ms.data = &data;
	ms.data->fd_in = 0;
	ms.data->fd_out = 0;
	ms.data->cmd = NULL;
	ms.path = &path;
	ms.lst = NULL;
	ms.prompt = get_prompt(&ms);
	get_input(&ms);
	return (0);
}
