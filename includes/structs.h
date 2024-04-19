/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:15:46 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/19 14:39:01 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_pipe
{
	char	*cmd;
	int		pipe_fd[2];
	int		pid[1024];
	int		stdin_dup;
	int		output_fd;
}	t_pipe;

typedef enum e_type
{
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND,
	EMPTY,
	PIPE
}	t_type;

typedef struct s_redirlst
{
	t_type				type;
	char				*file;
	struct s_redirlst	*prev;
	struct s_redirlst	*next;
}	t_redirlst;

typedef struct s_cmdlist
{
	int					fd_in;
	int					fd_out;
	char				**param;
	t_redirlst			*redir;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_list
{
	t_type			type;
	char			*content;
	struct s_list	*next;
}	t_list;

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
	char		**env;
	char		*input;
	char		*prompt;
	t_cmdlist	*cmdlist;
	t_list		*lst;
	t_data		*data;
	t_path		*path;
}	t_ms;

#endif
