/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:14:00 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/22 16:12:04 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	get_bool(t_ms *ms, int *bool_in, int *bool_out)
{
	t_list	tmp;

	tmp = lst;
	while (ms->tmp)
	{
		if (!ft_strncmp(ms->tmp->content, ">", 1))
			*bool_out++;
		if (!ft_strncmp(ms->tmp->content, "<", 1))
			*bool_in++;
	}
	return (1);
}

char	**parse_redirection(t_ms *ms, int bool_in, int bool_out)
{
	char	**cmd;
	int		len;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = ms->lst;
	len = ft_lstsize(ms->lst) - bool_in - bool_out;
	cmd = calloc(sizeof(char *), 1 + len);
	/*while (tmp)
	{
		if (ft_strncmp(tmp->content, "<", ft_strlen(tmp->content)) \
				&& ft_strncmp(tmp->content, ">". ft_strlen(tmp->content)))
			cmd[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}*/
	while (!ft_strncmp(tmp->next->content, "<", ft_strlen(tmp->next->content)) &&\ 
			!ft_strncmp(tmp->next->content, ">", ft_strlen(tmp->next->content)))
		tmp = tmp->next;
	if (!ft_strncmp(tmp->next->content, "<", ft_strlen(tmp->next->content)))
	{
		if (exist(tmp->content))
			cmd[0] = ft_strdup(tmp->content);
		else if (exist(tmp->next->next->next->content))
			cmd [0] = ft_strdup(tmp->next->next->next->content);
		else
			return (NULL);
			//gestion invalid cmd
		if (!open(tmp->next->next->content, O_RDONLY))
			cmd[1] = ft_strdup(tmp->next->next->content);
		else
			return (NULL);
			//gestion invalid file name
	}	
	if (!ft_strncmp(tmp->next->content, ">", ft_strlen(tmp->next->content)))
	{
	}
}

void	redirection(t_ms *ms)
{
	int		bool_in;
	int		bool_out;
	char	**cmd;

	get_bool(ms, &bool_in, &bool_out);
	cmd = parse_redirection(ms, boll_in. bool_out);
}
