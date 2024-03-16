/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 22:27:47 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/16 01:37:57 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_export(char *var)
{
	int	i;

	i = 1;
	if (var[i - 1] == '-')
		return (-1);
	if (!ft_isalpha(var[i - 1]) && var[i - 1] != '_')
		return (0);
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_' || var[i] == '\\'))
	{
		if (var[i] == '\\' && var[i + 1] && (ft_isalnum(var[i + 1]) \
			|| var[i + 1] == '_'))
			i++;
		else if (var[i] != '\\')
			i++;
		else
			return (0);
	}
	if (((int)ft_strlen(var) != i + 1) && var[i] == '+' && var[i + 1] == '=')
		return (2);
	if (var[i] != '\0' && var[i] != '=')
		return (0);
	return (1);
}
