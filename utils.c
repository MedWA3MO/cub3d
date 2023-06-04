# include"header.h"

void ft_printar(char **t)
{
	if (!t)
	{
		printf("(null)");
		return ;
	}
	while(*t)
		printf(">%s<\n", *t++);
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	char	*ss;
	size_t	len;

	if (!s1 && !s2 && !s3)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (str);
	ss = str;
	while (s1 && *s1)
		*str++ = *s1++;
	while (s2 && *s2)
		*str++ = *s2++;
	while (s3 && *s3)
		*str++ = *s3++;
	*str = 0;
	return (ss);
}

void	ft_error(const char *msg)
{
	write(2, "ERROR\n", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

void	ft_perror(const char *msg)
{
	write(2, "ERROR\n", 7);
	perror(msg);
	exit(1);
}
void	ft_exit(t_parsing *data, char *err)
{
	write(2, "ERROR\n", 7);
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	ft_clear(data->arr);
	ft_clear(data->map);
	free(data->east);
	free(data->floor);
	free(data->north);
	free(data->roof);
	free(data->south);
	free(data->weast);
	exit(1);
}

void	ft_exit_invalid_data(t_parsing *data, int line)
{
	if (line >= 0)
	{
		write(2, "ERROR\ninvalid token on line [", 30);
		write(2, ft_itoa(line + 1), ft_strlen(ft_itoa(line + 1)));
		write(2, "]\n", 2);
	}
	ft_clear(data->arr);
	ft_clear(data->map);
	free(data->east);
	free(data->floor);
	free(data->north);
	free(data->roof);
	free(data->south);
	free(data->weast);
	exit(1);
}


char	*ft_clear(char **ar)
{
	char	**cp;

	if (!ar)
		return (NULL);
	cp = ar;
	while (*ar)
		free(*ar++);
	free(cp);
	return (NULL);
}