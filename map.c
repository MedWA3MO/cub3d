/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:34:31 by samjaabo          #+#    #+#             */
/*   Updated: 2023/06/03 15:02:45 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_count_cols(char **map)
{
	int	n;
	int	count;
	char *str;

	n = 0;
	count = 0;
	while (map[n])
	{
		str = ft_strrchr(map[n], 0);
		--str;
		while (*str == ' ')
			--str;
		++str;
		*str = 0;
		if ((int)ft_strlen(map[n]) > count)
			count = ft_strlen(map[n]);
		++n;
	}
	return (count);
}

static char	**ft_realloc(char **array, char *new)
{
	int		count;
	char	**strs;
	char	**arcpy;
	char	**cpy;

	count = 0;
	while (array && array[count])
		count++;
	strs = malloc((count + 2) * sizeof(char *));
	if (!strs || !new)
		ft_perror("malloc fail");
	cpy = strs;
	arcpy = array;
	while (array && *array)
		*strs++ = *array++;
	*strs++ = new;
	*strs = NULL;
	free(arcpy);
	return (cpy);
}

t_parsing	*ft_read_map(char *file)
{
	int					fd;
	char				**arr;
	char				*tmp;
	static t_parsing	data;

	arr = NULL;
	fd = open(file, O_RDONLY);
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		if (tmp[ft_strlen(tmp) - 1] == '\n')
			tmp[ft_strlen(tmp) - 1] = 0;
		arr = ft_realloc(arr, tmp);
	}
	if (!arr)
		ft_error("you passed an empty file");
	data.arr = arr;
	return (&data);
}
//================================================

static int	ft_array_length(char **arr)
{
	int		i;

	i = 0;
	while (arr && arr[i])
		++i;
	if (i == 0)
		return (0);
	return (i);
}

static char	*ft_get_content(char *str)
{
	int		i;
	char	*trim;

	i = 0;
	while (str[i] == ' ')
		++i;
	while (str[i] && str[i] != ' ')
		++i;
	trim = ft_strtrim(&str[i], " ");
	return (trim);
}

static int	ft_is_content(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		++i;
	if (!ft_strncmp(&str[i], "NO ", 3))
		return (NO);
	else if (!ft_strncmp(&str[i], "EA ", 3))
		return (EA);
	else if (!ft_strncmp(&str[i], "SO ", 3))
		return (SO);
	else if (!ft_strncmp(&str[i], "WE ", 3))
		return (WE);
	else if (!ft_strncmp(&str[i], "F ", 2))
		return (FF);
	else if (!ft_strncmp(&str[i], "C ", 2))
		return (CC);
	return (0);
}

static void	ft_add_content(t_parsing *data, int i, int type)
{
	if (type == NO)
		data->north = ft_get_content(data->arr[i]);
	else if (type == EA)
		data->east = ft_get_content(data->arr[i]);
	else if (type == SO)
		data->south = ft_get_content(data->arr[i]);
	else if (type == WE)
		data->weast = ft_get_content(data->arr[i]);
	else if (type == FF)
		data->floor = ft_get_content(data->arr[i]);
	else if (type == CC)
		data->roof = ft_get_content(data->arr[i]);
	if (type == NO && !ft_strlen(data->north))
		ft_exit(data, "invalid path of north texture");
	else if (type == EA && !ft_strlen(data->east))
		ft_exit(data, "invalid path of east texture");
	else if (type == SO && !ft_strlen(data->south))
		ft_exit(data, "invalid path of south texture");
	else if (type == WE && !ft_strlen(data->weast))
		ft_exit(data, "invalid path of weast texture");
	else if (type == FF && !ft_strlen(data->floor))
		ft_exit(data, "invalid floor data");
	else if (type == CC && !ft_strlen(data->roof))
		ft_exit(data, "invalid roof data");
}

static void	ft_is_duplicated(t_parsing *data, int type)
{
	if (type == NO && data->north)
		ft_exit(data, "duplicated path to north texture");
	else if (type == EA && data->east)
		ft_exit(data, "duplicated path to east texture");
	else if (type == SO && data->south)
		ft_exit(data, "duplicated path to south texture");
	else if (type == WE && data->weast)
		ft_exit(data, "duplicated path to weast texture");
	else if (type == FF && data->floor)
		ft_exit(data, "duplicated floor data");
	else if (type == CC && data->roof)
		ft_exit(data, "duplicated roof data");
}

static void	ft_is_missing_data(t_parsing *data)
{
	if (!data->north)
		ft_exit(data, "missing north texture");
	else if (!data->east)
		ft_exit(data, "missing to east texture");
	else if (!data->south)
		ft_exit(data, "missing to south texture");
	else if (!data->weast)
		ft_exit(data, "missing to weast texture");
	else if (!data->floor)
		ft_exit(data, "missing floor data");
	else if (!data->roof)
		ft_exit(data, "missing roof data");
}

static int	ft_argb_to_int(char *a, char *r, char *g, char *b)
{
	t_color	color;

	color.bytes.a = ft_atoi(a);
	color.bytes.r = ft_atoi(r);
	color.bytes.g = ft_atoi(g);
	color.bytes.b = ft_atoi(b);
	return (color.argb);
}

static int	ft_count_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			++count;
		++i;
	}
	return (count);
}

static int	ft_is_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		++i;
	while (ft_isdigit(str[i]))
		++i;
	while (str[i] == ' ')
		++i;
	if (str[i] == 0)
		return (1);
	return (0);
}

static void	ft_floor(t_parsing *data)
{
	char	**arr;
	int		i;

	arr = ft_split(data->floor, ',');
	if (!arr)
		ft_exit(data, "malloc fail");
	if (ft_array_length(arr) != 3 || ft_count_char(data->floor, ',') != 2)
		return (ft_clear(arr), ft_exit(data, "invalid floor data"));
	i = 0;
	while (arr[i])
	{
		if (!ft_is_digits(arr[i]) || ft_atoi(arr[i]) < 0
			|| ft_atoi(arr[i]) > 255)
			return (ft_clear(arr), ft_exit(data, "floor data should "
					"include only 3 integers between 0-255 separated by ','"));
		++i;
	}
	data->ifloor = ft_argb_to_int("0", arr[0], arr[1], arr[2]);
	free(data->floor);
	data->floor = NULL;
	ft_clear(arr);
}

static void	ft_roof(t_parsing *data)
{
	char	**arr;
	int		i;

	arr = ft_split(data->roof, ',');
	if (!arr)
		ft_exit(data, "malloc fail");
	if (ft_array_length(arr) != 3 || ft_count_char(data->roof, ',') != 2)
		return (ft_clear(arr), ft_exit(data, "invalid roof data"));
	i = 0;
	while (arr[i])
	{
		if (!ft_is_digits(arr[i]) || ft_atoi(arr[i]) < 0
			|| ft_atoi(arr[i]) > 255)
			return (ft_clear(arr), ft_exit(data, "roof data should "
					"only include 3 integers between 0-255 separated by ','"));
		++i;
	}
	data->iroof = ft_argb_to_int("0", arr[0], arr[1], arr[2]);
	free(data->roof);
	data->roof = NULL;
	ft_clear(arr);
}

void	ft_extract_data(t_parsing *data)
{
	int		i;
	int		type;
	int		count;

	i = 0;
	count = 0;
	while (data->arr && data->arr[i])
	{
		type = ft_is_content(data->arr[i]);
		if (type)
		{
			ft_is_duplicated(data, type);
			ft_add_content(data, i, type);
			++count;
			if (count == 6)
				data->index = i + 1;
		}
		else if (count < 6 && data->arr[i][0] != 0)
			ft_exit_invalid_data(data, i);
		++i;
	}
	ft_is_missing_data(data);
	ft_floor(data);
	ft_roof(data);
}
//=============real map===============

static int	ft_is_map(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		++i;
	if (str[i] == 0)
		return (0);
	while (str[i] == ' ' || str[i] == '0' || str[i] == '1' || str[i] == 'N'
		|| str[i] == 'E' || str[i] == 'S' || str[i] == 'W')
		++i;
	if (str[i] == 0)
		return (1);
	return (0);
}

static void	ft_inside_map_valid(t_parsing *data, int i, int o, int len)
{
	if ((i == 0 || i == len || o == 0
			|| o == ((int)ft_strlen(data->map[i]) - 1)))
	{
		if (data->map[i][o] != ' ' && data->map[i][o] != '1')
			ft_exit_invalid_data(data, data->index + i);
	}
	else if (data->map[i][o] == '0')
	{
		if (data->map[i][o - 1] == ' ' || data->map[i][o + 1] == ' ')
			ft_exit_invalid_data(data, data->index + i);
		if (data->map[i - 1][o] == ' ' || data->map[i + 1][o] == ' ')
			ft_exit_invalid_data(data, data->index + i );
	}
}

static void	ft_is_valid_map(t_parsing *data)
{
	int	i;
	int	o;
	int	len;

	i = 0;
	len = ft_array_length(data->map);
	if (len-- < 3)
		ft_exit(data, "inavlid map");
	while (data->map[i])
	{
		o = 0;
		while (data->map[i][o])
		{
			ft_inside_map_valid(data, i, o, len);
			++o;
		}
		++i;
	}
}

static void	ft_check_player_exists(t_parsing *data)
{
	int	i;
	int	o;
	int	count;

	i = 0;
	count = 0;
	while (data->map[i])
	{
		o = 0;
		while (data->map[i][o])
		{
			if (data->map[i][o] == 'N' || data->map[i][o] == 'E'
				|| data->map[i][o] == 'S' || data->map[i][o] == 'W')
				++count;
			++o;
		}
		++i;
	}
	if (count == 0)
		ft_exit(data, "player’s start position not found in the map");
	if (count > 1)
		ft_exit(data, "more than one player’s start position found in the map");
}

char	*ft_new_str(t_parsing *data, char *str, int cols)
{
	int i;
	char	*new;

	new = malloc(sizeof(char) * (cols + 1));
	if (!new)
		ft_exit(data, "malloc fail");
	ft_memset(new, ' ', cols);
	i = 0;
	while (str && str[i])
	{
		new[i] = str[i];
		++i;
	}
	new[cols] = 0;
	return (new);
}

void	ft_read_real_map(t_parsing *data)
{
	int		i;
	int 	cols;

	i = data->index;
	while (data->arr[i][0] == 0)
		++i;
	data->index = i;
	cols = ft_count_cols(&data->arr[i]);
	while (data->arr[i])
	{
		if (!ft_is_map(data->arr[i]))
			ft_exit_invalid_data(data, i);
		data->map = ft_realloc(data->map, ft_new_str(data, data->arr[i], cols));
		if (!data)
			ft_exit_invalid_data(data, -1);
		++i;
	}
	ft_clear(data->arr);
	data->arr = NULL;
	ft_is_valid_map(data);
	ft_check_player_exists(data);
}
