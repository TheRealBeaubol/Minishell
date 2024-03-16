/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:09:25 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/16 16:28:14 by lboiteux         ###   ########.fr       */
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

void	parse(t_ms *ms)
{
	int		i;
	int		old_i;

	i = 0;
	if (parse_env(ms) == 1)
		return ;
	while (ms->input[i] != '\0')
	{
		while (ft_iswhitespace(ms->input[i]))
			i++;
		old_i = i;
		while ((ms->input[i] != ' ') && ms->input[i] != '\0')
		{
			if (ms->input[i] == '"' || ms->input[i] == '\'')
				i = parse_quote(ms, i + 1, ms->input[i]);
			else
				i++;
			if (i == -1)
			{
				ft_dprintf(2, "Parsing Error");
				return ;
			}
		}
		fill_list(ms->input, &(ms->lst), i, old_i);
	}
}
