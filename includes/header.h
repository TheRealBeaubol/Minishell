/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:18:11 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/06 18:04:31 by lboiteux         ###   ########.fr       */
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
int		change_directory(t_ms *ms);
void	unset(t_ms *ms, char *var);
void	echo(t_ms *ms);
void	env(t_ms *ms);
void	choose_cmd(t_ms *ms);
void	export(t_ms *ms);
void	exit_function(t_ms *ms);
int		check_export(char *var);

/* ********************* */
/*		  utils.c		 */
/* ********************* */
char	*get_cwd(int i);
char	*get_env(char **env, char *var_name);
int		get_env_indice(t_ms *ms, char *var);
void	free_exec(t_ms *ms, int is_fork, int err_code);

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
void	print_tokens(t_list *pipeline);
t_list	*get_pipeline(t_list *lst);
int		check_pipeline(char *content);
#endif
