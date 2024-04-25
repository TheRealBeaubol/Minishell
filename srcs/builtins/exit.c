/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:35:35 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/25 16:16:00 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*format_arg(char *arg)
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

static int	get_boolean(char *arg)
{
	if (arg[0] == 'a')
		return (1);
	else if (arg[0] == 'b')
		return (2);
	return (0);
}

static int	arg_len(char *arg)
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

static void	print_msg_and_exit(\
	int boolean, t_ms *ms, char *param, int exit_code)
{
	char	*arg;

	g_exit = exit_code;
	if (boolean == 0)
	{
		arg = format_arg(param);
		if (exit_code == 1)
			ft_dprintf(2, EXIT_MSG_2, arg);
		else
			ft_dprintf(2, EXIT_MSG_1, arg);
		free(arg);
	}
	if (boolean == 1)
		ft_dprintf(2, EXIT_MSG_1, param);
	if (boolean == 2)
		ft_dprintf(2, EXIT_MSG_2, param);
	free_and_exit(ms);
}

void	exit_function(t_cmdlist *cmdlst, t_ms *ms, int status)
{
	long long	nbr;
	char		*arg;
	int			boolean;
	int			i;

	if (!status)
		ft_dprintf(2, "exit\n");
	if ((!status || status == 1) && cmdlst->param[1])
	{
		arg = format_arg(cmdlst->param[1]);
		boolean = get_boolean(arg);
		nbr = ft_atoll(arg);
		i = arg_len(arg);
		if (ft_strncmp(arg, "a", 2) && ft_strncmp(arg, "b", 2))
			free(arg);
		if (boolean == 1 || boolean == 2)
			print_msg_and_exit(boolean, ms, cmdlst->param[1], 2);
		if (ft_longlonglen(nbr) != i)
			print_msg_and_exit(boolean, ms, cmdlst->param[1], 2);
		if (cmdlst->param[2])
			print_msg_and_exit(boolean, ms, cmdlst->param[1], 1);
		g_exit = nbr % 256;
	}
	if (status != 2)
	{
		free(ms->pipe->cmd);
		close(ms->pipe->stdin_dup);
		close(ms->pipe->stdout_dup);
		free(ms->pipe);
		free_and_exit(ms);
	}
}
