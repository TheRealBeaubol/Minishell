/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:13:45 by lboiteux          #+#    #+#             */
/*   Updated: 2024/04/16 16:46:17 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <math.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>
# include "libft.h"
# include <errno.h>

# define PROMPT "\001\033[4;0m\002\001\033[1;37m\002 >"
# define EXIT_MSG_1 "minishell: exit: %s: numeric argument required\n"
# define EXIT_MSG_2 "minishell: exit: %s: too many arguments\n"
# define ENV_EXIT_MSG_1 "env: invalid option -- %c\n"
# define ENV_EXIT_MSG_2 "env: %s: No such file or directory\n"

#endif
