/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:17:05 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/14 01:25:29 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int	g_exit;

void	print_list(t_list *lst)
{
	t_list	*next;
	int		i;

	i = 0;
	while (lst)
	{
		next = lst->next;
		ft_dprintf(1, "lst->content : [%s]\n	   i : [%d]\n", \
		lst->content, i);
		i++;
		lst = next;
	}
}
