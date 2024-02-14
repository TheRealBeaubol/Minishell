/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:58:15 by lboiteux          #+#    #+#             */
/*   Updated: 2023/11/23 22:44:28 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*var;

	var = malloc (sizeof(t_list));
	if (var == NULL)
		return (NULL);
	var->content = content;
	var->next = NULL;
	return (var);
}
