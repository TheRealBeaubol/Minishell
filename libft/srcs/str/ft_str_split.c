/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:14:58 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/24 14:46:43 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*str_split_strdup(char *src, int start, int end)
{
	int		i;
	int		j;
	char	*dest;

	dest = malloc(end - start + 1 * sizeof(*dest));
	if (dest == NULL)
		return (dest);
	i = start;
	j = 0;
	while (i < end)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = 0;
	return (dest);
}

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

static int	ft_count_malloc(char *str, char *sep)
{
	int	num_sep;
	int	i;
	int	verification;

	num_sep = 0;
	verification = 1;
	i = 0;
	while (str[i])
	{
		if (verification == 0 && char_finder(str[i], sep))
			verification = 1;
		if (verification == 1 && char_finder(str[i], sep) == 0)
			verification = 2;
		if (verification == 2 && (char_finder(str[i], sep)
				|| str[i + 1] == '\0'))
		{
			verification = 0;
			num_sep++;
		}
		else
			i++;
	}
	return (num_sep);
}

static void	ft_str_split_in_table(char **table, char *str, char *charset)
{
	int	i;
	int	start;
	int	end;
	int	tablei;

	i = 0;
	end = 0;
	start = -1;
	tablei = 0;
	while (str[i])
	{
		if (char_finder(str[i], charset) == 0 && start == -1)
			start = i;
		else if (char_finder(str[i], charset)
			&& start < i && start != -1)
		{
			end = i;
			table[tablei++] = str_split_strdup(str, start, end);
			start = -1;
		}
		i++;
	}
	if (start != -1)
		table[tablei++] = str_split_strdup(str, start, i);
	table[tablei] = 0;
}

char	**ft_str_split(char *str, char *charset)
{
	char	**table;
	int		n;

	if (!str)
	{
		table = malloc(sizeof(char *) * 1);
		table[0] = NULL;
		return (table);
	}
	n = 0;
	while (str[n] != '\0')
		++n;
	if (!charset)
	{
		table = malloc(sizeof(char *) * 2);
		table[0] = str_split_strdup(str, 0, n);
		table[1] = NULL;
		return (table);
	}
	table = malloc(sizeof(char *) * (ft_count_malloc(str, charset) + 1));
	if (table == 0)
		return (0);
	ft_str_split_in_table(table, str, charset);
	return (table);
}
