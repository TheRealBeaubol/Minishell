/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:20:30 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/07 20:05:38 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	if (!check_pipeline(ms->input))
	{
		g_exit = 2;
		ft_dprintf(2, "bash: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (is_skip(ms) == 1)
		return (1);
	return (0);
}

void	get_input(t_ms *ms)
{
	while (1)
	{
		signal_state_manager(0);
		ms->lst = NULL;
		ms->input = readline(ms->prompt);
		if (check_input(ms) == 0)
		{
			if (parse(ms) == -1)
			{
				g_exit = 2;
				ft_dprintf(2, "Parsing Error\n");
			}
			else if (ms->input[0] != '\0')
			{
				signal_state_manager(1);
				print_tokens(ms->lst);
				choose_cmd(ms);
				signal_state_manager(0);
			}
		}
		free(ms->input);
	}
}

void	get_single_input(t_ms *ms, char *line)
{
	signal_state_manager(0);
	ms->lst = NULL;
	ms->input = line;
	if (check_input(ms) == 0)
	{
		parse(ms);
		if (ms->input[0] != '\0')
		{
			signal_state_manager(1);
			choose_cmd(ms);
			signal_state_manager(0);
		}
	}
	free(ms->input);
}
