/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:45:49 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/14 01:25:58 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_list(t_list **stack)
{
	t_list	*current;
	t_list	*next;

	current = *stack;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}
