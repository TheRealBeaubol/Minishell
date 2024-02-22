/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:49:13 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/22 20:50:05 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	cpy = malloc((ft_strlen(s) + 1) * (sizeof(char)));
	if (cpy == 0)
		return (cpy);
	while (s[i] != 0)
	{
		cpy[i] = s[i];
		++i;
	}
	cpy[i] = '\0';
	return (cpy);
}
