/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:18:11 by lboiteux          #+#    #+#             */
/*   Updated: 2024/02/17 16:03:24 by mhervoch         ###   ########.fr       */
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
void		parse(t_ms *ms);

/* ******************** */
/*     parse_utils.c    */
/* ******************** */ 
char	**grep(char **env);

#endif
