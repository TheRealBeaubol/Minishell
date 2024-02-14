/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 02:14:31 by lboiteux          #+#    #+#             */
/*   Updated: 2024/01/30 21:51:48 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = ft_calloc((len1 + len2 + 1), sizeof(char));
	if (str == NULL)
		return (str);
	ft_strlcat (str, s1, len1 + 1);
	if (!len1)
		ft_strlcat ((str + len1), s2, (len1 + len2 + 1));
	else
		ft_strlcat ((str + len1 - 1), s2, (len1 + len2 + 1));
	return (str);
}
