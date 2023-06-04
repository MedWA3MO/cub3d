/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:56:11 by samjaabo          #+#    #+#             */
/*   Updated: 2023/06/04 03:40:02 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_parsing(int ac, char **av)
{
	write(1, "\033c", 3);//norm
	if (ac != 2)
		ft_error("Usage:1 ./cub3D *.cub");
	if (ft_strlen(av[1]) < 4)
		ft_error("Usage:2 ./cub3D *.cub");
	if (ft_strncmp((av[1] + ft_strlen(av[1]) - 4), ".cub", 5))
		ft_error("Usage:3 ./cub3D *.cub");
	if (open(av[1], O_RDONLY) == -1)
		return (ft_perror(av[1]), 1);
	return (0);
}

void	ft_leaks(void)
{
	//system("cd objs && leaks program");
}

void 	ft_initPlayer(t_palyer *player, char **map)
{
	int i;
	int j;
	int k;

	i = j = k = 0;
	while (map[i])
	{
		j= 0;
		while (map[i][j])
		{
			if (map[i][j]== 'N' || map[i][j] == 'S'
				||map[i][j] == 'W' || map[i][j] == 'E')
				{
					k= -1;
					break;
				}
			j++;
		}
		if (k == -1)
			break;
		i++;
	}
	player->x = i;
	player->y = j;
	player->turnDirection = 0; // -1 left, 1 right
	player->walkDirection = 0; // -1 back , 1 front
	player->rotationAngle = PI;
	player->moveSpeed = 2;
	player->rotationSpeed = 2 * (PI / 180);
}


int main(int ac, char **av)
{
	t_parsing *data;
	t_palyer player;

	// atexit(ft_leaks);
	// player = NULL;
	ft_parsing(ac, av);
	data = ft_read_map(av[1]);
	ft_extract_data(data);
	ft_read_real_map(data);
	// printf("north = %s\n", data->north);
	// printf("south = %s\n", data->south);
	// printf("east = %s\n", data->east);
	// printf("weast = %s\n", data->weast);
	// printf("floor = %s %d\n", data->floor, data->ifloor);
	// printf("roof = %s %d\n", data->roof, data->iroof);
	// printf("map len = %d\n", data->index);
	// ft_printar(data->map);
	ft_initPlayer(&player, data->map);
	// printf("%d %d %d %d\n", player.x, player.y , player.moveSpeed, player.walkDirection);
	ft_run_widget(data, &player);
	return (0);
}
