/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:15:46 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/18 17:45:45 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_data
{
	char	**cmd;
	int		fd_in;
	int		fd_out;
}	t_data;

typedef struct s_path
{
	char	**dec_path;
	char	*path_str;
	char	*commande;
	char	*str;
}	t_path;

typedef struct s_ms
{
	char	**env;
	char	*input;
	char	*prompt;
	t_list	*lst;
	t_data	*data;
	t_path	*path;
}	t_ms;

#endif
