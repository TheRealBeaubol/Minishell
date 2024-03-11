/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:55:30 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/11 16:29:11 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	pwd(t_ms *ms)
{
	char	*pwd;

	(void) ms;
	pwd = getcwd(NULL, 0);
	ft_dprintf(1, "%s", pwd);
	return (0);
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
	char	*user;
	char	*tmp;

	user = get_env(ms->env, "USER=");
	tmp = ft_strjoin("\e[1;91m[", user);
	free(user);
	user = ft_strjoin(tmp, "]▸ \e[4;1m\e[3;1m");
	free(tmp);
	tmp = ft_strjoin(user, str);
	free(user);
	free(str);
	prompt = ft_strjoin(tmp, PROMPT);
	free(tmp);
	str = ft_strjoin(prompt, "\e[0m");
	free(prompt);
	return (str);
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
