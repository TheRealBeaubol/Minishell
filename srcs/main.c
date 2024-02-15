/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:35:59 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/16 00:27:09 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int main(int ac, char **av, char **env)
{
	t_ms	ms;

	if (ac != 1)
		return (1);
	ms.ac = ac;
	ms.av = av;
	ms.env = env;
	get_input(&ms);
	return (0);
}
