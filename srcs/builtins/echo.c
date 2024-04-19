/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:48:18 by mhervoch          #+#    #+#             */
/*   Updated: 2024/04/19 12:50:47 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	is_valid_flag(char *str)
{
	if (*str == '-')
	{
		str++;
		if (*str == '\0')
			return (1);
		str++;
		while (*str != '\0')
		{
			if (*str == 'n')
				str++;
			else
				return (1);
		}
		return (0);
	}
	else
		return (1);
}

static void	echo_printing(t_cmdlist *cmdlst, int n, int i)
{
	int	cpt;

	cpt = 0;
	while (cmdlst->param[i + 1])
	{
		if (cpt++ == 0)
			ft_printf("%s", cmdlst->param[i]);
		else
		{
			ft_printf(" ");
			ft_printf("%s", cmdlst->param[i]);
		}
		i++;
	}
	if (cpt != 0)
		ft_printf(" ");
	ft_dprintf(1, "%s", cmdlst->param[i]);
	if (n == 1)
		ft_printf("\n");
}

void	echo(t_cmdlist *cmdlst)
{
	int			n;
	int			i;

	i = 1;
	if (!cmdlst->param[i])
	{
		ft_printf("\n");
		g_exit = 0;
		return ;
	}
	n = 1;
	while (!is_valid_flag(cmdlst->param[i]))
	{
		n = 0;
		if (cmdlst->param[i + 1])
			i += 1;
		else
			return ;
	}
	echo_printing(cmdlst, n, i);
	g_exit = 0;
}
