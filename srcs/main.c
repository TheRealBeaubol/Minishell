/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:35:59 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/15 22:38:32 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	g_exit;

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

int	main(int ac, char **av, char **env)
{
	t_ms	ms;
	t_data	data;
	t_path	path;

	g_exit = 0;
	ms.ac = ac;
	ms.av = av;
	ms.env = my_env(env);
	ms.data = &data;
	ms.data->fd_in = 0;
	ms.data->fd_out = 0;
	ms.data->cmd = NULL;
	ms.path = &path;
	ms.lst = NULL;
	ms.prompt = get_prompt(&ms);
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		get_single_input(&ms, ft_strdup(av[2]));
		exit(g_exit);
	}
	get_input(&ms);
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_ms	ms;
// 	t_data	data;
// 	t_path	path;

// 	if (ac != 1)
// 		return (1);
// 	g_exit = 0;
// 	ms.ac = ac;
// 	ms.av = av;
// 	ms.env = my_env(env);
// 	ms.data = &data;
// 	ms.data->fd_in = 0;
// 	ms.data->fd_out = 0;
// 	ms.data->cmd = NULL;
// 	ms.path = &path;
// 	ms.lst = NULL;
// 	ms.prompt = get_prompt(&ms);
// 	get_input(&ms);
// 	return (0);
// }
