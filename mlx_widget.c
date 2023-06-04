/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_widget.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:48:01 by samjaabo          #+#    #+#             */
/*   Updated: 2023/06/04 05:01:20 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#define ONE_COLOR 0x2baced
#define ZERO_COLOR 0xffffff
#define SPACE_COLOR 0xd671f0
#define PLAYER_COLOR 0xff0000
#define PADDING 1
#define SIZE 50
#define PLAYER_SIZE 10

static int	ft_count_rows(char **map)
{
	int	n;

	n = 0;
	while (*map++)
		++n;
	return (n);
}

void	ft_rectangle(t_widget *w, int x, int y, int color)
{
	int	row;
	int	col;

	row = 0;
	while (row < w->size - PADDING)
	{
		col = 0;
		while (col < w->size - PADDING)
		{
			mlx_pixel_put(w->self, w->window, x + col, y + row, color);
			++col;
		}
		++row;
	}
}

void	ft_player(t_widget *w, int x, int y, int color)
{
	int	row;
	int	col;
	int	padding;

	row = 0;
	padding = 1;
	while (row < PLAYER_SIZE)
	{
		col = 0;
		while (col < PLAYER_SIZE)
		{
			mlx_pixel_put(w->self, w->window, (x + col + (w->size / 2 - padding)) - (PLAYER_SIZE / 2),
				(y + row + (w->size / 2 - padding)) - (PLAYER_SIZE / 2), 0xffffff);
			++col;
		}
		++row;
	}
	row = 0;
	while (row < PLAYER_SIZE - (padding * 2))
	{
		col = 0;
		while (col < PLAYER_SIZE - (padding * 2))
		{
			mlx_pixel_put(w->self, w->window, (x + col + (w->size / 2 - padding)) - ((PLAYER_SIZE - (padding * 2)) / 2),
				(y + row + (w->size / 2 - padding)) - ((PLAYER_SIZE - (padding * 2)) / 2), color);
			++col;
		}
		++row;
	}
}

void ft_draw_line(t_widget *w, int x1, int y1, int x2, int y2, int color)
{
	//this function is from chatGPT
	int dx = x2 - x1;
	int dy = y2 - y1;
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	double xIncrement = dx / (double)steps;
	double yIncrement = dy / (double)steps;
	double x = x1, y = y1;
	int i = 0;

	while ( i <= steps )
	{
		mlx_pixel_put(w->self, w->window, round(x), round(y), color);
		x += xIncrement;
		y += yIncrement;
		i++;
	}
}


static void	self_show_widget(t_widget *w)
{
	w->row = 0;
	while (w->row < w->rows)
	{
		w->col = 0;
		while (w->col < w->cols)
		{
			if (w->col < (int)ft_strlen(w->map[w->row]) && w->map[w->row][w->col] == '1')
				ft_rectangle(w, w->size * w->col, w->size * w->row, ONE_COLOR);
			else if (w->col >= (int)ft_strlen(w->map[w->row]) || w->map[w->row][w->col] == ' ')
				ft_rectangle(w, w->size * w->col, w->size * w->row, SPACE_COLOR);
			else if (w->col < (int)ft_strlen(w->map[w->row]) && w->map[w->row][w->col] == '0')
				ft_rectangle(w, w->size * w->col, w->size * w->row, ZERO_COLOR);
			else
			{
				ft_rectangle(w, w->size * w->col, w->size * w->row, ZERO_COLOR);
				// ft_player(w, w->size * w->col, w->size * w->row, PLAYER_COLOR);
				// ft_draw_line(w, w->size * w->col, w->size * w->row, w->size * w->col + 50, w->size * w->row, PLAYER_COLOR);
			}
			w->col++;
		}
		w->row++;
	}
	ft_player(w, w->size * w->player->y, w->size * w->player->x, PLAYER_COLOR);
	ft_draw_line(w, w->size * w->player->y + 24, w->size * w->player->x + 24,
		(w->size * w->player->y) + cos(w->player->rotationAngle) * 40 , (w->size * w->player->x) + sin(w->player->rotationAngle) * 40, PLAYER_COLOR);
}

void	__init__(t_widget *widget, char **map, t_palyer *player)
{
	int	tmp;

	widget->map = map;
	// ft_map_rules(widget->map);
	widget->self = mlx_init();
	widget->player_img = mlx_xpm_file_to_image(widget->self,
			"./textures/image4.xpm", &tmp, &tmp);
	widget->exit_img = mlx_xpm_file_to_image(widget->self,
			"./textures/image3.xpm", &tmp, &tmp);
	widget->collect_img = mlx_xpm_file_to_image(widget->self,
			"./textures/collect-0.xpm", &tmp, &tmp);
	widget->ground_img = mlx_xpm_file_to_image(widget->self,
			"./textures/image1.xpm", &tmp, &tmp);
	widget->wall_img = mlx_xpm_file_to_image(widget->self,
			"./textures/image2.xpm", &tmp, &tmp);
	widget->cols = ft_count_cols(widget->map);
	widget->rows = ft_count_rows(widget->map);
	widget->row = 0;
	widget->col = 0;
	widget->size = SIZE;
	widget->window = mlx_new_window(widget->self, widget->cols * widget->size,
			widget->rows * widget->size, "so_long");
	widget->player = player;
	// ft_is_not_null(widget);
	self_show_widget(widget);
}

// int	ft_update(int key, t_widget *w)
// {
// 	int moves;

// 	// if (key == 13 || key == 126)
// 	// 	w->player->walkDirection = 1;
// 	// else if (key == 2 || key == 124)
// 	// 	w->player->turnDirection = 1;
// 	// else if (key == 0 || key == 123)
// 	// 	w->player->walkDirection = -1;
// 	// else if (key == 1 || key == 125)
// 	// 	w->player->turnDirection = -1;
// 	// w->player->rotationAngle += w->player->turnDirection * w->player->rotationSpeed;
// 	// moves = w->player->walkDirection * w->player->moveSpeed;
// 	// w->player->x = moves * cos(w->player->rotationAngle);
// 	// w->player->y = moves * sin(w->player->rotationAngle);
// 	// mlx_clear_window(w->self, w->window);
// 	// self_show_widget(w);
// 	printf("loop\n");
// 	return (0);
// }

// static int	ft_destroy(t_parsing *data)
// {
// 	// mlx_clear_window(wid->self, wid->window);
// 	// mlx_destroy_window(wid->self, wid->window);
// 	ft_exit_invalid_data(data, -1);
// 	return (0);
// }

void	ft_run_widget(t_parsing *data, t_palyer *player)
{
	t_widget	widget;

	// ft_is_true_args(argc, argv);
	__init__(&widget, data->map, player);
	// mlx_hook(widget.window, ON_KEYDOWN, USELESS, ft_exec_move, &widget);
	// mlx_hook(widget.window, ON_DESTROY, USELESS, ft_destroy, data);
	// mlx_hook(widget.self, 2, 0, ft_update, &widget);
	mlx_loop(widget.self);
}