/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:35:59 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/20 20:56:14 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	main(int ac, char **av, char **env)
{
	t_ms	ms;

	if (ac != 1)
		return (1);
	ms.ac = ac;
	ms.av = av;
	ms.env = env;
	
	// int	i = 0;
	// while (env[i])
	// {
	// 	ft_printf("%s\n", env[i]);
	// 	i++;
	// }
	get_input(&ms);
	return (0);
}
