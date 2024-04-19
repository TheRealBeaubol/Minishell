/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:34:04 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/19 19:32:52 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*join_custom_prompt(char *str, t_ms *ms)
{
	char	*prompt;

	prompt = get_env(ms->env, "USER=");
	prompt = ft_strjoin("\001\033[1;91m\002[", "]▸ \001\033[4;3;1m\002", \
prompt, 0b100);
	prompt = ft_strjoin(prompt, str, NULL, 0b011);
	prompt = ft_strjoin(prompt, PROMPT, NULL, 0b001);
	prompt = ft_strjoin(prompt, "\001\033[0m\002", NULL, 0b001);
	return (prompt);
}

char	*get_prompt(t_ms *ms)
{
	char	*prompt;
	char	*str;
	int		i;
	int		j;

	i = 0;
	prompt = getcwd(NULL, 0);
	while (prompt[i])
	{
		if (prompt[i] == '/')
			j = i;
		i++;
	}
	str = ft_calloc(i - j, sizeof(char));
	if (!str)
		return ("$> ");
	i = 0;
	while (prompt[++j])
		str[i++] = prompt[j];
	free(prompt);
	prompt = join_custom_prompt(str, ms);
	return (prompt);
}

char	**my_env(char **env)
{
	int		i;
	char	**envp;

	i = 0;
	while (env[i])
		i++;
	envp = ft_calloc(i + 1, sizeof(char *));
	if (!envp)
	{
		ft_dprintf(2, "ENV EMPTY ERROR\n");
		return (NULL);
	}
	i = -1;
	while (env[++i])
		envp[i] = ft_strdup(env[i]);
	return (envp);
}
