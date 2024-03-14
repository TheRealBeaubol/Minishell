/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:55:30 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/14 01:24:05 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int	g_exit;

char	*get_cwd(void)
{
	char	cwd[65536];

	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(cwd));
	return (NULL);
}

char	*get_pwd(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->env[i] && strncmp(ms->env[i], "PWD=", 4))
		i++;
	return (ms->env[i] + 4);
}

static char	*join_custom_prompt(char *str, t_ms *ms)
{
	char	*prompt;

	prompt = get_env(ms->env, "USER=");
	prompt = ft_strjoin("\e[1;91m[", "]▸ \e[4;1m\e[3;1m", prompt, 0b100);
	prompt = ft_strjoin(prompt, str, NULL, 0b011);
	prompt = ft_strjoin(prompt, PROMPT, NULL, 0b001);
	prompt = ft_strjoin(prompt, "\e[0m", NULL, 0b001);
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
