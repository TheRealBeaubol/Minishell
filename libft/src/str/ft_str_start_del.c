/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_start_del.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:01:39 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/07 15:26:32 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_malloc(char *str, char *del)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (del[j])
		{
			if (str[i] == del[j])
				break ;
			else
				j++;
		}
		if (del[j] != str[i])
			return (i);
		i++;
	}
	return (i);
}

char	*ft_str_start_del(char *str, char *del)
{
	char	*return_val;
	int		i;
	int		j;

	j = count_malloc(str, del);
	return_val = ft_calloc(ft_strlen(str) - j + 1, sizeof(char));
	if (!return_val)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[j])
	{
		return_val[i] = str[j];
		i++;
		j++;
	}
	free(str);
	return (return_val);
}
