/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:35:59 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/07 15:31:46 by lboiteux         ###   ########.fr       */
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
	ms.prompt = get_prompt();
	get_input(&ms);
	return (0);
}
