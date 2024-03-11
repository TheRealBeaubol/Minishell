/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:45:44 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/11 21:32:17 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	char_finder(char character, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == character)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!set)
		return ((char *)s1);
	if (!s1)
		return (NULL);
	j = ft_strlen(s1) - 1;
	while (char_finder(s1[i], set) || char_finder(s1[j], set))
	{
		if (char_finder(s1[i], set))
			i++;
		if (char_finder(s1[j], set))
			j--;
	}
	if (j < i)
		return (ft_strdup(""));
	str = ft_calloc((j - i + 2), sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, (s1 + i), (j - i + 2));
	ft_strlcat(str, "\0", (j - i + 2));
	return (str);
}
