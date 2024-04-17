/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:18:11 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/17 20:20:15 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "define.h"
# include "structs.h"

extern int	g_exit;

/* ******************** */
/*      builtins.c      */
/* ******************** */
int		change_directory(t_cmdlist *cmdlst, t_ms *ms);
void	unset(t_cmdlist *cmdlst, char *var, t_ms *ms);
void	echo(t_cmdlist *cmdlst);
void	env(t_cmdlist *cmdlst, t_ms *ms);
void	exec_builtin(t_cmdlist *cmdlist, char *cmd, t_ms *ms);
void	export(t_cmdlist *cmdlst, t_ms *ms);
void	exit_function(t_cmdlist *cmdlst, t_ms *ms);
int		check_export(char *var);
int		is_in_env(char *var, t_ms *ms);
char	*get_name(char *var, int *is_add);
void	init_and_launch_exec(t_ms *ms);

/* ********************* */
/*		  utils.c		 */
/* ********************* */
char	*get_cwd(int i);
char	*get_env(char **env, char *var_name);
int		get_env_indice(t_ms *ms, char *var);

/* ********************* */
/*	     get_input.c	 */
/* ********************* */
int		is_skip(t_ms *ms);
int		check_input(t_ms *ms);
void	get_input(t_ms *ms);
void	get_single_input(t_ms *ms, char *line);

/* ********************* */
/*		main_utils.c	 */
/* ********************* */
void	free_and_exit(t_ms *ms);
int		is_skip(t_ms *ms);
char	**my_env(char **env);

/* ********************* */
/*		  parse.c		 */
/* ********************* */
int		parse(t_ms *ms);
void	add_pipe(t_ms *ms, int *i, int *old_i, int *is_pipe);
int		add_redir_in_and_heredoc(t_ms *ms, int *i, int *old_i, int *is_pipe);
int		add_redir_out_and_append(t_ms *ms, int *i, int *old_i, int *is_pipe);
void	fill_list(char *input, t_list **lst, int i, int old_i);

/* ********************* */
/*		  signal.c		 */
/* ********************* */
void	signal_state_manager(int state);

/* ********************* */
/*		  prompt.c		 */
/* ********************* */
char	*get_prompt(t_ms *ms);

/* ******************** */
/*       getenv.c       */
/* ******************** */
int		parse_env(t_ms *ms);
int		replace_var(t_ms *ms, int i);
char	*get_var_name(t_ms *ms, int i);
int		handle_dquote_envvar(t_ms *ms, int i);
int		handle_squote_envvar(t_ms *ms, int i);
void	handle_exit_envvar(t_ms *ms, int *i);

/* ******************** */
/*        pipe.c        */
/* ******************** */
int		check_pipeline(char *content);
void	do_cmd_list(t_ms *ms);
void	do_pipe(t_ms *ms);
int		get_exit_code(int err_code);
int		is_builtin(char *cmd);
void	free_exec(t_ms *ms, t_pipe *data, int is_free_type);
int		check_pipeline(char *content);
void	free_cmdlist(t_cmdlist *cmdlist);
char	*get_cmd_path(char **path, char *cmd);
char	**grep(char **env);
int		check_file(char *cmd);

int		redirection(t_cmdlist *cmdlst);
int		append(t_redirlst *redir, int fd_out);
int	    check_outfile(char *file, int fd, int b);


#endif