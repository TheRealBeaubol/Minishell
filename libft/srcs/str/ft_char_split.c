/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 00:43:20 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/24 14:46:43 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_n_word(char *str, char charset)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != charset)
		i++;
	return (i);
}

int	ft_count_words(char *str, char charset)
{
	int	i;
	int	wc;

	i = 1;
	wc = 0;
	if (!*str)
		return (0);
	if (*str != charset)
		wc++;
	while (str[i])
	{
		if (*(str + i - 1) == charset)
		{
			if (*(str + i) != charset)
				wc++;
		}
		i++;
	}
	return (wc);
}

char	**ft_char_split(char *s, char c)
{
	char	**table;
	int		i;
	int		wc;
	int		wsize;

	i = -1;
	wsize = 0;
	if (!s)
		return (NULL);
	wc = ft_count_words((char *)s, c);
	table = malloc(sizeof(char *) * (wc + 1));
	if (!table)
		return (NULL);
	while (++i < wc)
	{
		while (wsize-- > 0 || *(char *)s == c)
			s++;
		wsize = ft_n_word((char *)s, c);
		table[i] = malloc(sizeof(char) * (wsize + 1));
		if (!table[i])
			return (NULL);
		ft_strlcpy(table[i], (char *)s, wsize + 1);
	}
	table[i] = 0;
	return (table);
}
