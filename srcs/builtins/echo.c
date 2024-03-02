/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 20:48:18 by mhervoch          #+#    #+#             */
/*   Updated: 2024/03/02 01:37:45 by mhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"
#include <string.h>

void	echo(t_ms *ms)
{
	char	*content;

	content = ms->lst->next->content;
	if (!strncmp(content, "-n", 2))
	{
		content = ms->lst->next->next->content;
		write(1, content, ft_strlen(content));
	}
	else
		write(1, ft_strjoin(content, "\n"), ft_strlen(content) + 1);
}
