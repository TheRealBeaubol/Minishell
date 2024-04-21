/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:18:11 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/21 05:23:48 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "define.h"
# include "structs.h"

extern int	g_exit;

/* ********************* */
/*	       main.c		 */
/* ********************* */
void	get_input(t_ms *ms);
char	**my_env(char **env);
char	*get_prompt(t_ms *ms);
void	free_cmdlist(t_cmdlist *cmdlist);
void	free_and_exit(t_ms *ms);
void	signal_state_manager(int state);

/* ********************* */
/*       builtins.c      */
/* ********************* */
int		change_directory(t_cmdlist *cmdlst, t_ms *ms);
void	echo(t_cmdlist *cmdlst);
void	env(t_cmdlist *cmdlst, t_ms *ms);
int		is_builtin(char *cmd);
void	exec_builtin(t_cmdlist *cmdlist, char *cmd, t_ms *ms);
int		is_in_env(char *var, t_ms *ms);
char	*get_name(char *var, int *is_add);
void	exit_function(t_cmdlist *cmdlst, t_ms *ms);
void	export(t_cmdlist *cmdlst, t_ms *ms);
int		get_env_indice(t_ms *ms, char *var);
char	*get_env(char **env, char *var_name);
void	unset(t_cmdlist *cmdlst, char *var, t_ms *ms);
char	*get_cwd(int i);

/* ********************* */
/*	      envvar.c		 */
/* ********************* */
int		parse_env(char **str, char **env);
char	*get_var_name(char **str, int i);
char	*get_new_input(char **str, char **env, int i, char *var_name);
int		handle_squote_envvar(char **str, int i);
char	*get_end_str(char **str, char *var_name, int i);

/* ********************* */
/*	     parsing.c		 */
/* ********************* */
void	do_cmd_list(t_ms *ms);
void	fill_list(char *input, t_list **lst, int i, int old_i);
int		parse(t_ms *ms);
void	add_pipe(t_ms *ms, int *i, int *old_i, int *is_pipe);
void	fill_list(char *input, t_list **lst, int i, int old_i);
void	addback_element(t_list **lst, t_type type, char *content);
t_list	*new_element(t_type type, char *content);
int		clean_cmdlist(t_ms *ms);

/* ********************* */
/*	       pipe.c		 */
/* ********************* */
void	do_pipe(t_ms *ms);
int		get_exit_code(int err_code);
char	**grep(char **env);
char	*get_cmd_path(char **path, char *cmd);
void	free_exec(t_ms *ms, t_pipe *data, int is_free_type);

/* ********************* */
/*     redirection.c     */
/* ********************* */
void	redirection(t_cmdlist *cmdlst, t_ms *ms);
int		here_doc(t_cmdlist *cmdlst, t_redirlst *redir, t_ms *ms);
#endif