/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:35:35 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/02 20:07:33 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*format_arg(char *arg)
{
	char	*new_arg;
	int		i;

	i = 0;
	while (arg[i] == ' ')
		i++;
	if (!ft_isdigit(arg[i]) && arg[i] != '+' && arg[i] != '-')
		return ("a");
	new_arg = ft_strdup(arg + i);
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (arg[i] == '\0')
		return ("a");
	while (ft_isdigit(arg[i]))
		i++;
	if (arg[i] == '\0')
		return (new_arg);
	free(new_arg);
	return ("b");
}

int	get_boolean(char *arg)
{
	if (arg[0] == 'a')
		return (1);
	else if (arg[0] == 'b')
		return (2);
	return (0);
}

int	arg_len(char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (arg[i] == '+')
		i++;
	if (arg[i] == '-')
	{
		j++;
		i++;
	}
	while (arg[i])
	{
		i++;
		j++;
	}
	return (j);
}

void	print_msg_and_exit(char	*msg, t_ms *ms, char *arg, int exit_code)
{
	ft_dprintf(2, msg, arg);
	g_exit = exit_code;
	free_and_exit(ms);
}

void	exit_function(t_ms *ms)
{
	long long	nbr;
	char		*arg;
	int			boolean;

	ft_dprintf(2, "exit\n");
	if (!ms->lst->next)
		free_and_exit(ms);
	else
	{
		arg = format_arg(ms->lst->next->content);
		boolean = get_boolean(arg);
		if (boolean == 1)
			print_msg_and_exit(EXIT_MSG_1, ms, ms->lst->next->content, 2);
		if (boolean == 2)
			print_msg_and_exit(EXIT_MSG_2, ms, ms->lst->next->content, 2);
		nbr = ft_atoll(arg);
		if (ft_longlonglen(nbr) != arg_len(arg))
			print_msg_and_exit(EXIT_MSG_1, ms, arg, 2);
		if (ms->lst->next->next)
			print_msg_and_exit(EXIT_MSG_2, ms, arg, 1);
		g_exit = nbr % 256;
		free_and_exit(ms);
	}
}
