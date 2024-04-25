/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:24:28 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/25 14:41:33 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	heredoc_handler(int sig)
{
	if (sig == 2)
	{
		ft_dprintf (1, "> ^C\n");
		rl_replace_line("", 0);
		g_exit = 130;
		close (0);
	}
}

void	sig_ignore(int sig)
{
	(void)sig;
}

static void	handle_sigint(int sig)
{
	if (sig == 2)
	{
		g_exit = 130;
		ft_dprintf (1, "^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_state_manager(int state)
{
	static struct termios	termios_data;
	static void				(*handlers[3])(int) = \
		{sig_ignore, handle_sigint, heredoc_handler};

	if (state)
		tcgetattr(0, &termios_data);
	if (!state)
		termios_data.c_lflag = termios_data.c_lflag & (~ECHOCTL);
	else if (state)
		termios_data.c_lflag = termios_data.c_lflag | ECHOCTL;
	tcsetattr(0, 0, &termios_data);
	signal(SIGINT, handlers[state]);
	signal(SIGQUIT, handlers[state]);
}
