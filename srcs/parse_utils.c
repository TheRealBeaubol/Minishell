/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:12:05 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/16 23:12:49 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	**grep(char **env)
{
	int		i;
	char	*cut_split;
	char	**splited_path;

	i = 0;
	if (!env || !*env)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env || !env[i])
		return (NULL);
	cut_split = ft_strcut(env[i], "PATH=");
	splited_path = ft_char_split(cut_split, ':');
	free(cut_split);
	return (splited_path);
}
