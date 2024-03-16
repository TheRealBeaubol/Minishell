/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 22:27:47 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/16 01:16:34 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_swap_export(int **indice, int i, int j)
{
	int	tmp;

	tmp = indice[i];
	indice[i] = indice[j];
	indice[j] = indice [i];
}

int	sort_indice(t_ms *ms, char **export, int **indice)
{
	int	i;
	int	j;

	i = 0;
	while (i < sizeof(*indice))
	{
		j = i + 1;
		while (j < int_len(*indice))
		{
			if (ft_strcmp(ms->env[i], ms->env[j]) > 0)
				ft_swap_export(indice, i, j);
			j++;
		}
		i++;
	}
}

int	*tri_export(t_ms *ms)
{
	char	**export;
	int		*indice;
	int		i;

	export = calloc((ft_strstr_len(ms->env)), sizeof(char *));
	i = 0;
	while (i < ft_strstr_len(ms->env))
		indice[i] = i++;
	i = 0;
	sort_indice(ms, export, &indice);
	return (indice);
}
