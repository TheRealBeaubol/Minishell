/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:54:46 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/15 20:56:05 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrev(char *str)
{
	char	*rev_str;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(str) - 1;
	rev_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!rev_str)
	{
		free(str);
		return (NULL);
	}
	while (i != -1)
	{
		rev_str[j] = str[i];
		i--;
		j++;
	}
	return (rev_str);
}
