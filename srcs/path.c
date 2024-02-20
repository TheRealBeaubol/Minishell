/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:12:05 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/20 22:08:21 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*char	*get_path(char *input, char **env)
{
	char	**all_path;
	char	*path;
	int		i;
	char	*commande;

	all_path = grep(env);
	commande = ft_strjoin("/", input);
	i = 0;
	while (all_path[i] && access(ft_strjoin(all_path[i], commande), X_OK) == -1)
		i++;
	path = ft_strjoin(all_path[i], commande);
	return (path);
}

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
}*/
