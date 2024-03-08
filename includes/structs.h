/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:15:46 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/08 22:06:29 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_type
{
	COMMAND,
	PARAMETERS,
}	t_type;

typedef struct s_ms
{
	int		ac;
	char	**av;
	char	**env;
	char	*input;
	t_list	*lst;
	char	*prompt;
	int		quote;
}	t_ms;

typedef struct s_data
{
	char	**cmd;
	int		fd_in;
	int		fd_out;
	char	**av;
}	t_data;

#endif
