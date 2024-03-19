/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:35:35 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/19 19:26:12 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long long	ft_atoll(char *nbr)
{
	int			i;
	long long	stock;
	long long	sign;

	sign = 1;
	i = 0;
	stock = 0;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nbr[i] != 0 && nbr[i] >= '0' && nbr[i] <= '9')
		stock = (stock * 10) + (nbr[i++] - 48);
	return (stock * sign);
}

void	exit_check(t_ms *ms, char *arg)
{
	int		i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (arg[i] == '\0')
	{
		g_exit = 2;
		ft_dprintf(2, "bash: exit: %c: numeric argument required\n", \
arg[i - 1]);
		free_and_exit(ms);
	}
	while (arg[i])
	{
		if (ft_isdigit(arg[i]))
			i++;
		else
		{
			ft_dprintf(2, "minishell: line 1: exit: %s: \
numeric argument required\n", arg);
			g_exit = 2;
			rl_clear_history();
			free_and_exit(ms);
		}
	}
}

void	exit_function(t_ms *ms)
{
	ft_dprintf(2, "exit\n");
	if (!ms->lst->next)
		free_and_exit(ms);
	else
	{
		exit_check(ms, ms->lst->next->content);
		if (ms->lst->next->next)
		{
			ft_dprintf(2, "minishell: exit: too many arguments\n");
			g_exit = 1;
			return ;
		}
		if (ft_strncmp(ms->lst->next->content, "9223372036854775807", \
ft_strlen(ms->lst->next->content)) > 0)
		{
			g_exit = 2;
			free_and_exit(ms);
		}
		g_exit = ft_atoll(ms->lst->next->content) % 256;
		free_and_exit(ms);
	}
}
