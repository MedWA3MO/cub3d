#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

size_t	ft_strlen(const char *str)
{
	if (!str)
		return 0;
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}


char	*ft_strdup(const char *src)
{
	char	*str;
	char	*p;
	int		len;

	len = 0;
	while (src[len])
		len++;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	p = str;
	while (*src)
		*p++ = *src++;
	*p = '\0';
	return (str);
}


char	*ft_strjoin(char *s1, char *s2)
{
	char	*chr;
	int		i;
	int		j;

	i = 0;
	chr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!chr)
		return (NULL);
	while (s1 && s1[i])
	{
		chr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		chr[i++] = s2[j++];
	chr[i] = '\0';
	free(s1);
	return (chr);
}

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return NULL;
	if ((char)c == '\0')
	{
		while (*str)
			str++;
		return ((char *)str);
	}
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)(str));
		str++;
	}
	return (0);
}


char *get_line(char *line)
{
	if (!line || *line == '\0')
		return NULL;
	while (ft_strchr(line, '\n'))
	{
		int len = ft_strchr(line, '\n') - line;
		char *line_2 = malloc(len + 1 + 1);
		line_2[len] = '\n';
		line_2[len + 1] = '\0';
		int i = 0;
		while (line[i] != '\n')
		{
			line_2[i] = line[i];
			i++;
		}
		return line_2;
	}
	return ft_strdup(line);
}

char *get_next(char *line)
{
	if (!line)
		return NULL;
	if (*line == '\0')
	{
		free(line);
		return NULL;
	}
	if (ft_strchr(line, '\n'))
	{
		int len = ft_strchr(line, '\n') - line;
		char *ret = ft_strdup(line + (len + 1));
		free(line);
		return ret;
	}
	free(line);
	return NULL;
}


char *get_next_line(int fd)
{
	if (BUFFER_SIZE <= 0)
		return NULL;

	char *buffer = malloc(BUFFER_SIZE  + 1);
	static char *lefts;

	while (!ft_strchr(lefts, '\n'))
	{
		int n = read(fd, buffer, BUFFER_SIZE);
		buffer[n] = '\0';
		if (n < 0)
		{
			free(lefts);
			free(buffer);
			return NULL;
		}
		if (n == 0)
			break;
		(void)n;
		lefts = ft_strjoin(lefts, buffer);
	}
	char *line = get_line(lefts);
	lefts = get_next(lefts);
	free(buffer);
	return line;
}
