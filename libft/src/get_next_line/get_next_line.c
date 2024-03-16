/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:57:47 by lboiteux          #+#    #+#             */
/*   Updated: 2024/03/16 17:21:17 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_split_line(char *sline)
{
	int		i;
	char	*str;

	i = 0;
	if (!sline[i])
		return (NULL);
	while (sline[i] && sline[i] != '\n')
		i++;
	if (sline[i] == '\n')
		i++;
	str = ft_calloc((i + 2), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (sline[i] && sline[i] != '\n')
	{
		str[i] = sline[i];
		i++;
	}
	if (sline[i] == '\n')
		str[i] = sline[i];
	str[++i] = 0;
	return (str);
}

static char	*ft_get_line(int fd, char *line)
{
	char	*buffer;
	int		sizeread;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	sizeread = 1;
	while (!ft_gnl_strchr(buffer, '\n') && sizeread != 0)
	{
		sizeread = read(fd, buffer, BUFFER_SIZE);
		if (sizeread == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[sizeread] = '\0';
		line = ft_gnl_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

static char	*ft_new_sstring_implementation(char *sline, int i)
{
	char	*str;
	int		j;

	str = ft_calloc((ft_strlen(sline) - i + 1), sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	while (sline[++i] != 0)
		str[j++] = sline[i];
	str[j] = 0;
	free(sline);
	if (!*str)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

static char	*ft_new_sstring(char *sline)
{
	int		i;
	char	*str;

	i = 0;
	while (sline[i] && sline[i] != '\n')
		i++;
	if (!sline[i])
	{
		free(sline);
		return (NULL);
	}
	str = ft_new_sstring_implementation(sline, i);
	return (str);
}

char	*get_next_line(int fd, int free_static)
{
	char		*temp_line;
	static char	*sline;

	if (free_static == 1)
	{
		free(sline);
		sline = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	sline = ft_get_line(fd, sline);
	if (!sline || sline[0] == 0)
	{
		free(sline);
		sline = NULL;
		return (NULL);
	}
	temp_line = ft_split_line(sline);
	sline = ft_new_sstring(sline);
	return (temp_line);
}
