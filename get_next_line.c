/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:30:58 by samjaabo          #+#    #+#             */
/*   Updated: 2023/06/02 18:53:50 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*split_data(char *data, char **_line)
{
	char	*line;
	char	*left;
	char	*dt;
	char	*tmp;

	dt = data;
	while (*dt && *dt++ != '\n')
		;
	line = malloc(ft_strlen(data) - ft_strlen(dt) + 1);
	left = malloc(ft_strlen(dt) + 1);
	if (!left || !line)
		return (free(line), free(left), free(data), NULL);
	*_line = line;
	tmp = left;
	while (*dt)
		*left++ = *dt++;
	*left = '\0';
	dt = data;
	while (*dt && *dt != '\n')
		*line++ = *dt++;
	if (*dt == '\n')
		*line++ = '\n';
	*line = '\0';
	return (free(data), tmp);
}

static char	*ft_read(int fd)
{
	char		*buff;
	char		*data;
	int			nbytes;

	data = NULL;
	while (!ft_strchr(data, '\n'))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return (ft_perror("malloc fail"), data);
		nbytes = read(fd, buff, BUFFER_SIZE);
		if (nbytes <= 0)
			return (free(buff), data);
		buff[nbytes] = 0;
		data = ft_strjoin(data, buff);
		if (!data)
			return (ft_perror("malloc fail"), data);
	}
	return (data);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*data;

	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (free(data), NULL);
	if (read(fd, 0, 0) < 0)
		return (free(data), data = NULL);
	if (!ft_strchr(data, '\n'))
	{
		line = ft_read(fd);
		if (!line && !data)
			return (NULL);
		if (!line && *data == '\0')
			return (free(data), data = NULL);
		data = ft_strjoin(data, line);
		if (!data)
			return (ft_perror("malloc fail"), NULL);
	}
	data = split_data(data, &line);
	if (!data)
		return (ft_perror("malloc fail"), NULL);
	if (*line == '\0' && *data == '\0')
		return (free(data), free(line), data = NULL);
	return (line);
}
