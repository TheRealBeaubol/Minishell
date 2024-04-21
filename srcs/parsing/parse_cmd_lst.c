/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:01:35 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/21 04:48:30 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_cmdlist	*cmd_list_init(t_ms *ms)
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

static int	get_redir_type(char *content)
{
	if (!ft_strncmp(content, "<", 2))
		return (REDIR_IN);
	else if (!ft_strncmp(content, ">", 2))
		return (REDIR_OUT);
	else if (!ft_strncmp(content, "<<", 3))
		return (HERE_DOC);
	else if (!ft_strncmp(content, ">>", 3))
		return (APPEND);
	return (EMPTY);
}

static t_redirlst	*ft_redir_list(t_redirlst *redir, char *type, char *file)
{
	t_redirlst	*tmp;
	t_redirlst	*new;

	if (!redir)
	{
		redir = ft_calloc(2, sizeof(t_redirlst));
		redir->type = get_redir_type(type);
		redir->file = ft_strdup(file);
		redir->next = NULL;
		return (redir);
	}
	new = ft_calloc(2, sizeof(t_redirlst));
	new->type = get_redir_type(type);
	new->file = ft_strdup(file);
	tmp = redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (redir);
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
		if ((!ft_strncmp(tmp->content, "<", 2) && tmp->type == REDIR_IN) \
	|| (!ft_strncmp(tmp->content, ">", 2) && tmp->type == REDIR_OUT) || \
	(!ft_strncmp(tmp->content, "<<", 3) && tmp->type == HERE_DOC) || \
	(!ft_strncmp(tmp->content, ">>", 3) && tmp->type == APPEND))
		{
			tmpcmdlist->redir = ft_redir_list(tmpcmdlist->redir, tmp->content, \
				tmp->next->content);
			tmp = tmp->next;
		}
		else if (!is_cmd++ && tmp->type == EMPTY)
			tmpcmdlist->param[0] = ft_strdup(tmp->content);
		else if (ft_strncmp(tmp->content, "|", 2) == 0 && tmp->type == PIPE)
		{
			tmpcmdlist->next = ft_calloc(2, sizeof(t_cmdlist));
			tmpcmdlist = tmpcmdlist->next;
			tmpcmdlist->param = ft_calloc(2, sizeof(char *));
			is_cmd = 0;
			tmpcmdlist->redir = NULL;
		}
		else
			tmpcmdlist->param = ft_join_tab(tmpcmdlist->param, tmp->content);
		tmp = tmp->next;
	}
}

static int	parse_quote(char **str, int i, char c)
{
	char	*tmp;
	char	*unquote_str;
	int		j;
	int		k;

	tmp = ft_calloc(ft_strlen(*str), sizeof(char));
	if (!tmp)
		return (-1);
	unquote_str = tmp;
	j = 0;
	k = 0;
	while (j != i - 1)
		tmp[k++] = (*str)[j++];
	while ((*str)[i] != c)
	{
		if ((*str)[i] == '\0')
			return (-1);
		tmp[k++] = (*str)[i++];
	}
	j = i++;
	while ((*str)[i] != '\0')
		tmp[k++] = (*str)[i++];
	free(*str);
	*str = unquote_str;
	return (j - 1);
}

int	clean_redirlist(t_redirlst *redir, char **env)
{
	t_redirlst	*tmp;
	int			i;

	tmp = redir;
	while (tmp)
	{
		if (parse_env(&(tmp->file), env))
		{
			ft_dprintf(2, "minishell: env parsing error\n");
			return (0);
		}
		i = 0;
		while (tmp->file[i])
		{
			if (tmp->file[i] == '"' || tmp->file[i] == '\'')
				i = parse_quote(&(tmp->file), i + 1, tmp->file[i]);
			else
				i++;
			if (i == -1)
			{
				ft_dprintf(2, "minishell: unclosed quote\n");
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

char **ft_remove_tab(char **tab, char c)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_calloc(2, sizeof(char *));
	while (tab[i])
	{
		if (*tab[i] != c)
			new = ft_join_tab(new, tab[i]);
		i++;
	}
	ft_free_tab(tab);
	return (new);
}

int	clean_cmdlist(t_ms *ms)
{
	t_cmdlist	*tmp;
	int			i;
	int			j;

	tmp = ms->cmdlist;
	while (tmp)
	{
		tmp->param = ft_remove_tab(tmp->param, '\0');
		if (!clean_redirlist(tmp->redir, ms->env))
			return (-1);
		i = 0;
		while (tmp->param[i])
		{
			if (parse_env(&(tmp->param[i]), ms->env))
			{
				ft_dprintf(2, "minishell: env parsing error\n");
				return (-1);
			}
			j = 0;
			while (tmp->param[i][j])
			{
				if (tmp->param[i][j] == '"' || tmp->param[i][j] == '\'')
					j = parse_quote(&(tmp->param[i]), j + 1, tmp->param[i][j]);
				else
					j++;
				if (j == -1)
				{
					ft_dprintf(2, "minishell: unclosed quote\n");
					return (-1);
				}
			}
			i++;
		}
		tmp->param = ft_remove_tab(tmp->param, '\026');
		tmp = tmp->next;
	}
	return (0);
}

