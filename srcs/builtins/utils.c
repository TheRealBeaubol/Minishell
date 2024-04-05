/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:16:04 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/04 16:10:58 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_cwd(int i)
{
	char	cwd[65538];

	if (getcwd(cwd, sizeof(cwd)))
	{
		if (i == 1)
		{
			ft_dprintf(1, "%s\n", cwd);
			return (NULL);
		}
		return (ft_strdup(cwd));
	}
	return (NULL);
}

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

int	get_env_indice(t_ms *ms, char *var)
{
	int	i;

	i = 0;
	while (ms->env[i] && ft_strncmp(ms->env[i], var, ft_strlen(var)))
		i++;
	if (!ms->env[i])
		return (-1);
	return (i);
}

static int	get_exit_code(int err_code)
{
	if (!WIFEXITED(err_code) && WCOREDUMP(err_code))
	{
		ft_dprintf(2, "Quit (core dumped)\n");
		return (131);
	}
	if (WTERMSIG(err_code) == 2)
	{
		ft_dprintf(2, "\n");
		return (130);
	}
	return (WEXITSTATUS(err_code));
}

void	free_exec(t_ms *ms, int is_fork, int err_code)
{
	if (is_fork == 1)
	{
		ft_dprintf(2, "Command not found\n");
		rl_clear_history();
		free(ms->input);
		ms->input = NULL;
		free(ms->prompt);
		free(ms->path->str);
		ft_free_tab(ms->env);
		ft_free_tab(ms->data->cmd);
		ft_free_list(&ms->lst);
		g_exit = 127;
		exit(g_exit);
	}
	else if (!is_fork)
	{
		g_exit = get_exit_code(err_code);
		ft_free_tab(ms->data->cmd);
		ms->data->cmd = NULL;
		free(ms->path->str);
		ft_free_list(&ms->lst);
		free(ms->prompt);
		ms->prompt = get_prompt(ms);
	}
}
