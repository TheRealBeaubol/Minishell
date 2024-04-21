/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 06:01:59 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/21 06:06:07 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_skip(t_ms *ms)
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

static char	check_token(char *content, int *i)
{
	if (content[*i] == '|')
	{
		(*i)++;
		while (ft_iswhitespace(content[*i]))
			(*i)++;
		if (content[*i] == '|' || !content[*i])
			return (content[*i]);
	}
	else if (content[*i] == '>' || content[*i] == '<')
	{
		(*i)++;
		if ((content[*i - 1] == '<' && content[*i] == '<') || \
			(content[*i - 1] == '>' && content[*i] == '>'))
			(*i)++;
		while (ft_iswhitespace(content[*i]))
			(*i)++;
		if (content[*i] == '|' || content[*i] == '>' || content[*i] == '<'\
			|| !content[*i])
			return (content[*i]);
	}
	return ('a');
}

char	is_valid_pipeline(char *content)
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
		else if (content[i] == '|' || content[i] == '>' || content[i] == '<')
		{
			c = check_token(content, &i);
			if (c != 'a')
				return (c);
		}
		else
			i++;
	}
	return ('a');
}

int	is_too_much_heredoc(t_ms *ms)
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
