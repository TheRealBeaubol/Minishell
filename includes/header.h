/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:18:11 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/20 19:59:42 by lboiteux         ###   ########.fr       */
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
/*         path.c       */
/* ******************** */
char	**grep(char **env);
char	*get_path(char *input, char **env);

/* ******************** */
/*        quote.c       */
/* ******************** */
int		parse_quote(t_ms *ms, int i, char c);
char	*clear_quotes(char *content, int i, char c);
void	rm_quote(t_ms *ms);
#endif
