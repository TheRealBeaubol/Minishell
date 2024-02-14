/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:55:29 by lboiteux          #+#    #+#             */
/*   Updated: 2023/11/23 22:43:00 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	i = 0;
	while (*(char *)(s + start + i) != 0 && i < len)
		i ++;
	str = malloc((i + 1) * sizeof(char));
	if (str == NULL)
		return (str);
	ft_strlcpy(str, (char *)(s + start), len + 1);
	return (str);
}
