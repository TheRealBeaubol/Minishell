/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:09:25 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/14 13:05:43 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

static void	fill_list(char *input, t_list **lst, int i, int old_i)
{
	char	*str;

	str = ft_strdup_range(input, old_i, i);
	if (*lst == NULL)
	{
		*lst = ft_lstnew(str);
		return ;
	}
	ft_lstadd_back(lst, ft_lstnew(str));
}

int	parse_element(t_ms *ms, int i, int *old_i, int *is_pipe)
{
	while (ft_iswhitespace(ms->input[i]))
		i++;
	*old_i = i;
	while ((ms->input[i] != ' ') && ms->input[i] != '\0')
	{
		if (ms->input[i] == '"' || ms->input[i] == '\'')
			i = parse_quote(ms, i + 1, ms->input[i]);
		else if (ms->input[i] == '|')
		{
			*is_pipe = 1;
			if (*old_i != i)
			{
				fill_list(ms->input, &(ms->lst), i, *old_i);
				*old_i = i + 1;
			}
			ft_lstadd_back(&(ms->lst), ft_lstnew(ft_strdup("|")));
			i++;
			break ;
		}
		else
			i++;
		if (i == -1)
			return (-1);
	}
	return (i);
}

t_cmdlist	*cmd_list_init(t_ms *ms)
{
	t_cmdlist	*cmdlist;

	ms->cmdlist = ft_calloc(2, sizeof(t_cmdlist));
	if (!ms->cmdlist)
		return (NULL);
	cmdlist = ms->cmdlist;
	cmdlist->param = ft_calloc(2, sizeof(char *));
	if (!cmdlist->param)
		return (NULL);
	cmdlist->next = NULL;
	return (cmdlist);
}

void	do_cmd_list(t_ms *ms)
{
	t_cmdlist	*tmpcmdlist;
	t_list		*tmp;
	int			is_cmd;

	is_cmd = 0;
	tmp = ms->lst;
	tmpcmdlist = cmd_list_init(ms);
	while (tmp)
	{
		if (!is_cmd)
			tmpcmdlist->cmd = ft_strdup(tmp->content);
		if (!is_cmd++)
			tmpcmdlist->param[0] = ft_strdup(tmp->content);
		else if (ft_strncmp(tmp->content, "|", 2) == 0)
		{
			tmpcmdlist->next = ft_calloc(2, sizeof(t_cmdlist));
			tmpcmdlist = tmpcmdlist->next;
			tmpcmdlist->param = ft_calloc(2, sizeof(char *));
			is_cmd = 0;
		}
		else
			tmpcmdlist->param = ft_join_tab(tmpcmdlist->param, tmp->content);
		tmp = tmp->next;
	}
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
