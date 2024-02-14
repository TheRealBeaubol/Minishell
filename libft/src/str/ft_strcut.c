/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:08:56 by lboiteux          #+#    #+#             */
/*   Updated: 2024/01/01 17:09:04 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strcut(char *str, char *cut)
{
	char	*cut_str;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!cut)
		return (str);
	cut_str = ft_calloc((ft_strlen(str) - ft_strlen(cut) + 1), sizeof(char));
	if (!cut_str)
		return (NULL);
	while (str[i] == cut[i] && i <= ft_strlen(cut) && i <= ft_strlen(str))
		i++;
	while (str[i] != '\0')
		cut_str[j++] = str[i++];
	cut_str[j] = '\0';
	return (cut_str);
}
