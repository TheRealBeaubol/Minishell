/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:09:25 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/19 20:05:50 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	add_redir_out_and_append(t_ms *ms, int *i, int *old_i, int *is_pipe)
{
	int	is_double;

	is_double = 0;
	*is_pipe = 1;
	if (ms->input[*i + 1] == '>')
		is_double = 1;
	if (*old_i != *i)
	{
		fill_list(ms->input, &(ms->lst), *i, *old_i);
		*old_i = *i + 1;
	}
	if (is_double == 1)
	{
		addback_element(&(ms->lst), APPEND, ft_strdup(">>"));
		(*i)++;
	}
	else
		addback_element(&(ms->lst), REDIR_OUT, ft_strdup(">"));
	(*i)++;
	return (is_double);
}

static int	add_redir_in_and_heredoc(t_ms *ms, int *i, int *old_i, int *is_pipe)
{
	int	is_double;

	is_double = 0;
	*is_pipe = 1;
	if (ms->input[*i + 1] == '<')
		is_double = 1;
	if (*old_i != *i)
	{
		fill_list(ms->input, &(ms->lst), *i, *old_i);
		*old_i = *i + 1;
	}
	if (is_double == 1)
	{
		addback_element(&(ms->lst), HERE_DOC, ft_strdup("<<"));
		(*i)++;
	}
	else
		addback_element(&(ms->lst), REDIR_IN, ft_strdup("<"));
	(*i)++;
	return (is_double);
}

static int	parse_quote(t_ms *ms, int i, char c)
{
	char	*tmp;
	char	*unquote_str;
	int		j;
	int		k;

	tmp = ft_calloc(ft_strlen(ms->input) - 1, sizeof(char));
	if (!tmp)
		return (-1);
	unquote_str = tmp;
	j = 0;
	k = 0;
	while (j != i - 1)
		tmp[k++] = ms->input[j++];
	while (ms->input[i] != c)
	{
		if (ms->input[i] == '\0')
			return (-1);
		tmp[k++] = ms->input[i++];
	}
	j = i++;
	while (ms->input[i] != '\0')
		tmp[k++] = ms->input[i++];
	free(ms->input);
	ms->input = unquote_str;
	return (j - 1);
}

static int	parse_element(t_ms *ms, int i, int *old_i, int *is_pipe)
{
	while (ft_iswhitespace(ms->input[i]))
		i++;
	*old_i = i;
	while ((ms->input[i] != ' ') && ms->input[i] != '\0')
	{
		if (ms->input[i] == '"' || ms->input[i] == '\'')
			i = parse_quote(ms, i + 1, ms->input[i]);
		else if (ms->input[i] == '|' || ms->input[i] == '<' || \
	ms->input[i] == '>')
		{
			if (ms->input[i] == '|')
				add_pipe(ms, &i, old_i, is_pipe);
			else if (ms->input[i] == '<')
				add_redir_in_and_heredoc(ms, &i, old_i, is_pipe);
			else if (ms->input[i] == '>')
				add_redir_out_and_append(ms, &i, old_i, is_pipe);
			break ;
		}
		else
			i++;
		if (i == -1)
			return (-1);
		if (i >= (int)ft_strlen(ms->input))
			return ((int)ft_strlen(ms->input));
	}
	return (i);
}

int	parse(t_ms *ms)
{
	int		i;
	int		old_i;
	int		is_pipe;

	is_pipe = 0;
	i = 0;
	if (parse_env(ms) == 1)
		return (-1);
	while (ms->input[i] != '\0')
	{
		i = parse_element(ms, i, &old_i, &is_pipe);
		if (i == -1)
			return (-1);
		if (is_pipe == 1)
			is_pipe = 0;
		else
			fill_list(ms->input, &(ms->lst), i, old_i);
	}
	return (0);
}
