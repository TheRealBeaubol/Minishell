/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:49:13 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/11 21:30:55 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(char *s)
{
	char	*cpy;
	char	*tmp;
	char	*tmp_cpy;

	cpy = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	tmp = s;
	tmp_cpy = cpy;
	while (*tmp)
		*(tmp_cpy++) = *(tmp++);
	*tmp_cpy = 0;
	return (cpy);
}
