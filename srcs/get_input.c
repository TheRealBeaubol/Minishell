/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:20:30 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/21 05:21:32 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	is_skip(t_ms *ms)
{
	int	i;

	i = -1;
	while (ms->input[++i])
	{
		while (ft_iswhitespace(ms->input[i]))
			i++;
		if (ms->input[i] == '|')
		{
			g_exit = 2;
			ft_dprintf(2, "bash: syntax error near unexpected token `|'\n");
			return (1);
		}
		else
			break ;
	}
	if ((ms->input[0] == '!' || ms->input[0] == ':') \
		&& ms->input[1] == '\0')
		return (1);
	i = -1;
	while (ft_iswhitespace(ms->input[++i]) || ms->input[i] == '|' || \
ms->input[i] == '>' || ms->input[i] == '<')
		if (ms->input[i + 1] == '\0')
			return (1);
	return (0);
}

static char	check_pipeline(char *content)
{
	int		i;
	char	c;

	i = 0;
	while (content[i])
	{
		if (content[i] == '"' || content[i] == '\'')
		{
			c = content[i++];
			while (content[i] && content[i] != c)
				i++;
			if (content[i] == '\0')
				return (c);
			i++;
		}
		else if (content[i] == '|')
		{
			i++;
			while (ft_iswhitespace(content[i]))
				i++;
			if (content[i] == '|' || !content[i])
				return (content[i]);
		}
		else if (content[i] == '>' || content[i] == '<')
		{
			i++;
			if ((content[i - 1] == '<' && content[i] == '<') || \
				(content[i - 1] == '>' && content[i] == '>'))
				i++;
			while (ft_iswhitespace(content[i]))
				i++;
			if (content[i] == '|' || content[i] == '>' || content[i] == '<'\
				|| !content[i])
				return (content[i]);
		}
		else
			i++;
	}
	return ('a');
}

static int	is_too_much_heredoc(t_ms *ms)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (ms->input[i])
	{
		if (ms->input[i] == '<')
		{
			i++;
			if (ms->input[i] == '<')
			{
				count++;
				i++;
			}
		}
		else
			i++;
	}
	if (count > 16)
	{
		ft_dprintf(2, "minishell: maximum here-document count exceeded\n");
		return (1);
	}
	return (0);
}

static int	check_input(t_ms *ms)
{
	char	c;

	if (!ms->input)
	{
		ft_dprintf (2, "exit\n");
		free_and_exit(ms);
	}
	if (ms->input[0] != '\0')
		add_history(ms->input);
	c = check_pipeline(ms->input);
	if (c == '"' || c == '\'')
	{
		ft_dprintf(2, "minishell: unclosed quote %c\n", c);
		return (1);
	}
	if (c == '|' || c == '>' || c == '<' || c == '\0')
	{
		g_exit = 2;
		if (c == '\0')
			ft_dprintf(2, "minishell: syntax error near unexpected token \
`newline'\n");
		else
			ft_dprintf(2, "minishell: syntax error near \
unexpected token `%c'\n", c);
		return (1);
	}
	if (is_too_much_heredoc(ms))
		return (1);
	if (is_skip(ms) == 1)
		return (1);
	return (0);
}

static void	init_and_launch_exec(t_ms *ms)
{
	do_cmd_list(ms);
	ft_free_list(ms->lst);
	ms->lst = NULL;
	if (!clean_cmdlist(ms))
	{
		signal_state_manager(1);
		do_pipe(ms);
		signal_state_manager(0);
	}
	free_cmdlist(ms->cmdlist);
	ms->cmdlist = NULL;
}

void	get_input(t_ms *ms)
{
	while (1)
	{
		signal_state_manager(0);
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
