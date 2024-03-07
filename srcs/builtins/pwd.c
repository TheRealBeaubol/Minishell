/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:55:30 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/07 15:25:35 by lboiteux         ###   ########.fr       */
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

char	*get_prompt(void)
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
	prompt = ft_strjoin(str, "\e[4;0m \e[1;37m> \e[0m");
	prompt = ft_strjoin("\e[4;1m\e[3;1m\e[1;91m", prompt);
	return (prompt);
}
