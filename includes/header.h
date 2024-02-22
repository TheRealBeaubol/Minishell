/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:18:11 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/22 23:17:56 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "define.h"
# include "structs.h"

/* ********************* */
/*	     get_input.c	 */
/* ********************* */
int		is_skip(t_ms *ms);
int		check_input(t_ms *ms);
void	get_input(t_ms *ms);

/* ********************* */
/*		  error.c		 */
/* ********************* */
void	free_and_exit(t_ms *ms);

/* ********************* */
/*		  parse.c		 */
/* ********************* */
void	parse(t_ms *ms);
void	fill_list(t_ms *ms, int i, int old_i);

/* ********************* */
/*   	parse_utils.c	 */
/* ********************* */
void	print_list(t_list *lst);

/* ******************** */
/*        quote.c       */
/* ******************** */
int		parse_quote(t_ms *ms, int i, char c);
char	*clear_quotes(char *content, int i, char c);
void	rm_quote(t_ms *ms);

/* ******************** */
/*         exec.c       */
/* ******************** */
void	exec(t_ms *ms);
char	*grep(char **env);
char	*get_path(char *av, char **env);
int		choose_cmd(t_ms *ms);

/* ******************** */
/*         cd.c         */
/* ******************** */
int		change_directory(t_ms *ms);

/* ******************** */
/*         pwd.c        */
/* ******************** */
char	*get_pwd(t_ms *ms);
int		pwd(t_ms *ms);
char	*get_prompt(t_ms *ms);

/* ******************** */
/*       getenv.c       */
/* ******************** */
int		parse_env(t_ms *ms);
void	replace_var(t_ms *ms, int *i);

/* ********************* */
/*     getenv_utils.c	 */
/* ********************* */
char	*get_new_input(t_ms *ms, int i, char *end_str, char *var_name);
char	*get_end_str(t_ms *ms, char *var_name, int i);
char	*get_var_name(t_ms *ms, int i);
char	*get_env(char **env, char *var_name);
char	*wrong_var(t_ms *ms, int i);
#endif
