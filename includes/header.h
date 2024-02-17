/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:18:11 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/17 17:15:31 by lboiteux         ###   ########.fr       */
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
void	check_input(t_ms *ms);
void	get_input(t_ms *ms);

/* ********************* */
/*		  error.c		 */
/* ********************* */
void	free_and_exit(t_ms *ms);

/* ********************* */
/*		  parse.c		 */
/* ********************* */
void	parse(t_ms *ms);
void	print_list(t_list *lst);
void	parse_char(t_ms *ms, size_t *i, char c);

/* ******************** */
/*     parse_utils.c    */
/* ******************** */ 
char	**grep(char **env);

#endif
