/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:18:04 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/19 17:27:12 by lboiteux         ###   ########.fr       */
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
