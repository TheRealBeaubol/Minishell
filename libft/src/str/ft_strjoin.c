/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 02:14:31 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/15 01:37:56 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_manage_join(char *s1, char *s2, char *c, int tofree)
{
	if (tofree & 0b001)
		free(s1);
	if (tofree & 0b010)
		free(s2);
	if (tofree & 0b100)
		free(c);
}

char	*ft_strjoin(char *s1, char *s2, char *c, int tofree)
{
	char	*str;
	int		mask;

	mask = !s1 + (!s2 << 1) | tofree;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + ft_strlen(c) + 1) \
	* sizeof(char));
	*str = 0;
	if (!str)
		return (str);
	ft_strcat(str, s1);
	if (c)
		ft_strcat(str, c);
	ft_strcat (str, s2);
	ft_manage_join(s1, s2, c, mask);
	return (str);
}
