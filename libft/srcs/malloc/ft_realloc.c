/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 00:55:30 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/24 14:46:43 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(char *ptr, int size)
{
	char	*new;
	int		i;	

	i = 0;
	if (ptr == NULL)
		return (NULL);
	new = malloc(size * sizeof(char));
	if (new == NULL)
		return (NULL);
	while (ptr[i])
	{
		new[i] = ptr[i];
		i++;
	}
	return (new);
}
