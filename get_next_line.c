/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpastran <jpastran@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:10:40 by jpastran          #+#    #+#             */
/*   Updated: 2024/03/30 13:10:28 by jpastran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *stat)
{
	int		bnumber;
	char	*buff;

	bnumber = 1;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (bnumber != 0 && !ft_strchr(stat, '\n'))
	{
		bnumber = read(fd, buff, BUFFER_SIZE);
		if (bnumber == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bnumber] = '\0';
		stat = ft_strjoin(stat, buff);
	}
	free(buff);
	return (stat);
}

char	*ft_line(char *stat)
{
	char	*line;
	int		i;

	i = 0;
	if (!*stat)
		return (NULL);
	while (stat[i] != '\n' && stat[i])
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stat[i] != '\n' && stat[i])
	{
		line[i] = stat[i];
		i++;
	}
	if (stat[i] == '\n')
	{
		line[i] = stat[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_update_stat(char *stat)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	while (stat[i] != '\n' && stat[i])
		i++;
	if (!stat[i])
	{
		free(stat);
		return (NULL);
	}
	ptr = malloc(sizeof(char) * (ft_strlen(stat) + 1 - i));
	if (!ptr)
		return (NULL);
	i++;
	j = 0;
	while (stat[i])
		ptr[j++] = stat[i++];
	ptr[j] = '\0';
	free(stat);
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*stat;
	char		*next_line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	stat = ft_read(fd, stat);
	if (!stat)
		return (NULL);
	next_line = ft_line(stat);
	stat = ft_update_stat(stat);
	return (next_line);
}
