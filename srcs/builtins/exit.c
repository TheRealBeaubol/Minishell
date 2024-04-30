/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:35:35 by lboiteux          #+#    #+#             */
/*   Updated: 2024/05/01 00:16:28 by lboiteux         ###   ########.fr       */
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
	new_arg = ft_strtrim(arg, "\t\n\v\f\r ");
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (arg[i] == '\0')
		return ("a");
	while (ft_isdigit(arg[i]))
		i++;
	while (ft_iswhitespace(arg[i]))
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

static int	print_msg_and_exit(\
	int boolean, t_ms *ms, char *param, int exit_code)
{
	char	*arg;

	g_exit = exit_code;
	if (boolean == 0)
	{
		arg = format_arg(param);
		if (exit_code == 1)
		{
			ft_dprintf(2, EXIT_MSG_2, arg);
			free(arg);
			return (0);
		}
		ft_dprintf(2, EXIT_MSG_1, arg);
		free(arg);
	}
	if (boolean == 1)
		ft_dprintf(2, EXIT_MSG_1, param);
	if (boolean == 2)
		ft_dprintf(2, EXIT_MSG_2, param);
	free(ms->pipe->cmd);
	close(ms->pipe->stdin_dup);
	close(ms->pipe->stdout_dup);
	free(ms->pipe);
	free_and_exit(ms);
	return (1);
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
		g_exit = nbr % 256;
		if (ft_strncmp(arg, "a", 2) && ft_strncmp(arg, "b", 2))
			free(arg);
		if (ft_longlonglen(nbr) != i)
			i = print_msg_and_exit(boolean, ms, cmdlst->param[1], 2);
		if (boolean == 1 || boolean == 2)
			i = print_msg_and_exit(boolean, ms, cmdlst->param[1], 2);
		if (cmdlst->param[2])
			i = print_msg_and_exit(boolean, ms, cmdlst->param[1], 1);
	}
	if (status != 2 && i)
		free_and_close_exit_function(ms);
}
