/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:56:11 by samjaabo          #+#    #+#             */
/*   Updated: 2023/06/07 09:44:35 by moouaamm         ###   ########.fr       */
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

int	nami(t_palyer *player, char c)
{
	if (c == 'S')
	{
		player->rotationAngle = PI / 2;
		return (1);
	}
	else if(c  == 'N')
	{
		player->rotationAngle = PI + (PI / 2);
		return (1);
	}
	else if(c  == 'E')
	{
		player->rotationAngle = PI;
		return (1);
	}
	else if(c  == 'W')
	{
		player->rotationAngle = 0;
		return (1);
	}
	else
		return (0);
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
			if (nami(player, map[i][j]))
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
	player->x = (j + 1) * SIZE - (SIZE / 2);
	player->y = (i + 1) * SIZE - (SIZE / 2);
	player->trnDir = 0;
	player->walkDirection = 0;
	// player->rotationAngle = PI;
	player->moveSpeed = 10;
	player->rotationSpeed = 10 * (PI / 180);
}


int main(int ac, char **av)
{
	t_parsing *data;
	t_palyer *player;

	// atexit(ft_leaks);
	player = NULL;
	player = malloc (sizeof(t_palyer));
	if(!player)
		printf("player allocation\n");
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
	ft_initPlayer(player, data->map);
	// printf("%d %d %d %d\n", player.x, player.y , player.moveSpeed, player.walkDirection);
	ft_run_widget(data, player);
	return (0);
}
