/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:20:30 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/23 15:56:55 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_pipeline(char *str)
{
	char	c;

	c = is_valid_pipeline(str);
	if (c == '"' || c == '\'')
		ft_dprintf(2, "minishell: unclosed quote %c\n", c);
	if (c == '"' || c == '\'')
		return (1);
	if (c == '|' || c == '>' || c == '<' || c == '\0')
	{
		g_exit = 2;
		if (c == '\0')
			ft_dprintf(2, SYNTAX_ERROR_1);
		else
			ft_dprintf(2, SYNTAX_ERROR_2, c);
		return (1);
	}
	return (0);
}

static int	check_input(t_ms *ms)
{
	if (!ms->input)
		ft_dprintf (2, "exit\n");
	if (!ms->input)
		free_and_exit(ms);
	if (ms->input[0] != '\0')
		add_history(ms->input);
	if (check_pipeline(ms->input))
		return (1);
	if (is_too_much_heredoc(ms))
		return (1);
	if (is_skip(ms) == 1)
		return (1);
	return (0);
}

static void	init_and_launch_exec(t_ms *ms)
{
	int	status;

	do_cmd_list(ms);
	ft_free_list(ms->lst);
	ms->lst = NULL;
	status = clean_cmdlist(ms);
	if (!status)
	{
		signal_state_manager(0);
		do_pipe(ms);
		signal_state_manager(1);
	}
	else if (status == -1)
		ft_dprintf(2, "minishell: env parsing error\n");
	else if (status == -2)
		ft_dprintf(2, "minishell: unclosed quote\n");
	free_cmdlist(ms->cmdlist);
	ms->cmdlist = NULL;
}

void	get_input(t_ms *ms)
{
	while (1)
	{
		signal_state_manager(1);
		ms->lst = NULL;
		ms->cmdlist = NULL;
		ms->input = readline(ms->prompt);
		if (check_input(ms) == 0)
		{
			if (parse(ms) == -1)
			{
				g_exit = 2;
				ft_dprintf(2, "Parsing Error\n");
			}
			else if (ms->input[0] != '\0')
				init_and_launch_exec(ms);
		}
		free(ms->input);
		ms->input = NULL;
	}
}
