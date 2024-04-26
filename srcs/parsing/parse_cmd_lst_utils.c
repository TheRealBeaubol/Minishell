/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_lst_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 06:07:04 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/26 14:15:21 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

static int	clean_redirlist(t_redirlst *redir, char **env)
{
	t_redirlst	*tmp;
	int			i;

	tmp = redir;
	while (tmp)
	{
		i = parse_env(&(tmp->file), env);
		if (i == 1)
			ft_dprintf(2, "minishell: env parsing error\n");
		if (i == 1)
			return (0);
		while (tmp->file[i])
		{
			if (tmp->file[i] == '"' || tmp->file[i] == '\'')
				i = parse_quote(&(tmp->file), i + 1, tmp->file[i]);
			else
				i++;
			if (i == -1)
				ft_dprintf(2, "minishell: unclosed quote\n");
			if (i == -1)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	replace_var(t_cmdlist *tmp, char **env, int *j, int *i)
{
	char	**tab;
	int		is_var;

	is_var = 0;
	if (tmp->param[*i][is_var] != '\'' && tmp->param[*i][is_var] != '"'\
		&& ft_strchr(tmp->param[*i], '$'))
		is_var = 1;
	*j = parse_env(&(tmp->param[*i]), env);
	if (*j == 1)
		return (0);
	if (is_var && ft_strchr(tmp->param[*i], ' '))
	{
		tab = ft_char_split(tmp->param[*i], ' ');
		tmp->param = ft_extend_tab(tmp->param, tab, i);
	}
	return (1);
}

static int	clean_param(t_cmdlist *tmp, char **env, int *j)
{
	int		i;

	i = 0;
	while (tmp->param[i])
	{
		if (!replace_var(tmp, env, j, &i))
			return (-1);
		if (tmp->param[i])
		{
			while (tmp->param[i][*j])
			{
				if (tmp->param[i][*j] == '"' || tmp->param[i][*j] == '\'')
					*j = parse_quote(&(tmp->param[i]), *j + 1, \
						tmp->param[i][*j]);
				else
					(*j)++;
				if (*j == -1)
					return (-2);
			}
			i++;
		}
	}
	return (0);
}

int	clean_cmdlist(t_ms *ms)
{
	t_cmdlist	*tmp;
	int			j;
	int			status;

	tmp = ms->cmdlist;
	while (tmp)
	{
		tmp->param = ft_remove_tab(tmp->param, '\0');
		if (!clean_redirlist(tmp->redir, ms->env))
			return (-1);
		status = clean_param(tmp, ms->env, &j);
		if (status < 0)
			return (status);
		tmp->param = ft_remove_tab(tmp->param, '\026');
		tmp = tmp->next;
	}
	return (0);
}
