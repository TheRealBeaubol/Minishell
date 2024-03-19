/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:14:00 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/19 19:55:55 by mhervoch         ###   ########.fr       */
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

void	redirection(t_ms *ms)
{
	int	bool_in;
	int	bool_out;

	get_bool(ms, &bool_in, &bool_out);
}
