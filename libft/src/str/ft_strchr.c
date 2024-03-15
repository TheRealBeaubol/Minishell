/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:23:52 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/15 20:42:33 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	*cast;

	cast = (char *)s;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return (cast + i);
		else
			i++;
	}
	if (s[i] == c)
		return (cast + i);
	return (NULL);
}
