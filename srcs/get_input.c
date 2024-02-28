/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:20:30 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/28 19:00:27 by lboiteux         ###   ########.fr       */
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
		free_and_exit(ms);
	add_history(ms->input);
	if (is_skip(ms) == 1)
		return (1);
	return (0);
}

void	handle_sigint(int sig)
{
	(void) sig;
	printf("\n");
	rl_on_new_line(); // Display readline on a new line
	rl_replace_line("", 0); // Display a clear line after the prompt
	rl_redisplay(); // Display Prompt on the new line
}

void	get_input(t_ms *ms)
{
	while (1)
	{
		signal(SIGINT, handle_sigint); // Handle Ctrl + C
		signal(SIGQUIT, SIG_IGN); // Handle Ctrl + '\'
		ms->lst = NULL;
		ms->input = readline(ms->prompt);
		if (check_input(ms) == 0)
		{
			parse(ms);
			if (ms->input[0] != '\0')
			{
				print_list(ms->lst);
				choose_cmd(ms);
				free(ms->input);
			}
			ft_free_list(&ms->lst);
		}
	}
}
