/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:50:50 by lboiteux          #+#    #+#             */
/*   Updated: 2023/11/23 22:43:09 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_strfind(const char *s1, const char *s2, size_t len)
{
	size_t	i;

	i = 0;
	while (s2[i] && s1[i] == s2[i] && i < len)
		i++;
	return (s2[i] == '\0');
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (!little[0])
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (big[i] && i < len)
	{
		if (big[i] == little[0] && ft_strfind(big + i, little, len - i))
			return ((char *)(big + i));
		i++;
	}
	return (0);
}
