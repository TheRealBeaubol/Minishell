/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:24:28 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/18 17:44:45 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	sig_ignore(int sig)
{
	(void) sig;
}

static void	handle_sigint(int sig)
{
	(void) sig;
	if (sig == 2)
	{
		g_exit = 130;
		ft_dprintf (1, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == 3)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_printf("  \b\b");
	}
}

void	signal_state_manager(int state)
{
	static void	(*handlers[2])(int) = {handle_sigint, sig_ignore};

	signal(SIGINT, handlers[state]);
	signal(SIGQUIT, handlers[state]);
}
