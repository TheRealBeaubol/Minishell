/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:20:30 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/14 17:51:25 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	is_skip(t_ms *ms)
{
	int	i;

	i = -1;
	if ((ms->input[0] == '!' || ms->input[0] == ':') \
		&& ms->input[1] == '\0')
		return (1);
	while ((9 <= ms->input[++i] && ms->input[i] <= 13) || ms->input[i] == 32)
		if (ms->input[i + 1] == '\0')
			return (1);
	return (0);
}

int	check_input(t_ms *ms)
{
	if (!ms->input)
	{
		rl_clear_history();
		ft_dprintf (2, "exit\n");
		free_and_exit(ms);
	}
	if (ms->input[0] != '\0')
		add_history(ms->input);
	if (is_skip(ms) == 1)
		return (1);
	return (0);
}

void	handle_sigint(int sig)
{
	(void) sig;
	ft_dprintf (1, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	get_input(t_ms *ms)
{
	int	i;

	i = 0;
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		ms->lst = NULL;
		ms->input = readline(ms->prompt);
		if (check_input(ms) == 0)
		{
			ms->quote = 0;
			parse(ms);
			if (ms->input[0] != '\0')
			{
				i = choose_cmd(ms);
				if (i == 42)
				{
					rl_clear_history();
					free_and_exit(ms);
				}
			}
		}
		free(ms->input);
	}
}
