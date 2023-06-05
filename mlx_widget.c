/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_widget.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:48:01 by samjaabo          #+#    #+#             */
/*   Updated: 2023/06/05 06:21:42 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	while (row < SIZE - PADDING)
	{
		col = 0;
		while (col < SIZE - PADDING)
		{
			mlx_pixel_put(w->mlx, w->window, x + col, y + row, color);
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

	col = 0;
	padding = 1;
	while (col < w->col * SIZE)
	{
		row = 0;
		while ( row< w->row * SIZE)
		{
			if (col >= x - PLAYER_SIZE  && col <= x + PLAYER_SIZE && row <= y + PLAYER_SIZE && row >= y - PLAYER_SIZE)
				mlx_pixel_put(w->mlx, w->window, col, row, PLAYER_COLOR);
			++row;
		}
		++col;
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
		mlx_pixel_put(w->mlx, w->window, round(x), round(y), color);
		x += xIncrement;
		y += yIncrement;
		i++;
	}
}


static void	mlx_show_widget(t_widget *w)
{
	int a;
	int b;

	w->row = 0;
	while (w->row < w->rows)
	{
		w->col = 0;
		while (w->col < w->cols)
		{
			if (w->col < (int)ft_strlen(w->map[w->row]) && w->map[w->row][w->col] == '1')
				ft_rectangle(w, SIZE * w->col, SIZE * w->row, ONE_COLOR);
			else if (w->col >= (int)ft_strlen(w->map[w->row]) || w->map[w->row][w->col] == ' ')
				ft_rectangle(w, SIZE * w->col, SIZE * w->row, SPACE_COLOR);
			else if (w->col < (int)ft_strlen(w->map[w->row]) && w->map[w->row][w->col] == '0')
				ft_rectangle(w, SIZE * w->col, SIZE * w->row, ZERO_COLOR);
			else
				ft_rectangle(w, SIZE * w->col, SIZE * w->row, ZERO_COLOR);
			w->col++;
		}
		w->row++;
	}
	w->player->x += w->mv_x;
	w->player->y += w->mv_y;
	ft_draw_line(w, w->player->x , w->player->y ,(w->player->x) + (cos(w->player->rotationAngle) * RAY_SIZE) ,
		(w->player->y) + (sin(w->player->rotationAngle) * RAY_SIZE), PLAYER_COLOR);
	ft_player(w, w->player->x , w->player->y, PLAYER_COLOR);
}

void	__init__(t_widget *widget, char **map, t_palyer *player)
{
	int	tmp;

	widget->map = map;
	// ft_map_rules(widget->map);
	widget->mlx = mlx_init();
	widget->player_img = mlx_xpm_file_to_image(widget->mlx,
			"./textures/image4.xpm", &tmp, &tmp);
	widget->exit_img = mlx_xpm_file_to_image(widget->mlx,
			"./textures/image3.xpm", &tmp, &tmp);
	widget->collect_img = mlx_xpm_file_to_image(widget->mlx,
			"./textures/collect-0.xpm", &tmp, &tmp);
	widget->ground_img = mlx_xpm_file_to_image(widget->mlx,
			"./textures/image1.xpm", &tmp, &tmp);
	widget->wall_img = mlx_xpm_file_to_image(widget->mlx,
			"./textures/image2.xpm", &tmp, &tmp);
	widget->cols = ft_count_cols(widget->map);
	widget->rows = ft_count_rows(widget->map);
	widget->row = 0;
	widget->col = 0;
	widget->mv_x = 0;
	widget->mv_y = 0;
	widget->window = mlx_new_window(widget->mlx, widget->cols * SIZE,
			widget->rows * SIZE, "so_long");
	widget->player = player;
	// ft_is_not_null(widget);
	mlx_show_widget(widget);
}

int	ft_update2(int key, t_widget *w)
{
	int moves;

	moves = 0;
	mlx_clear_window(w->mlx, w->window);
	mlx_show_widget(w);

}

int	thre_isnt_wall(t_widget *w, int x, int y)
{
	double	pos_x;
	double	pos_y;
	int a;
	int b;

	a = floor( (w->player->x + x) / SIZE);
	b = floor((w->player->y + y) / SIZE);
	if(a < 0 || a > w->cols || b < 0 || b > w->rows)
		return (0);
	else if (w->map[b][a] == '1')
		return(0);
	return(1);
}

int	ft_update(int key, t_widget *w)
{
	int moves;

	moves = 0;
	w->mv_x = 0;
	w->mv_y = 0;
	w->player->trnDir = 0;
	w->player->walkDirection = 0;
	if (key == 2 || key == 124)  //right *********
		w->player->trnDir = 1;
	else if (key == 0 || key == 123) //left *******
		w->player->trnDir = -1;
	if (key == 1 || key == 125) //down **********
		w->player->walkDirection = -1;
	else if (key == 13 || key == 126) //up *******
		w->player->walkDirection = 1;
	if (w->player->trnDir)
		w->player->rotationAngle += w->player->trnDir * w->player->rotationSpeed;
	if (w->player->walkDirection)
		moves = w->player->walkDirection * w->player->moveSpeed;
	int a,b;
	a = moves * cos(w->player->rotationAngle);
	b = moves * sin(w->player->rotationAngle);
	if (thre_isnt_wall(w, a, b))
	{
		w->mv_x = moves * cos(w->player->rotationAngle);
		w->mv_y = moves * sin(w->player->rotationAngle);
	}
	mlx_clear_window(w->mlx, w->window);
	mlx_show_widget(w);
	return (0);
}

// static int	ft_destroy(t_parsing *data)
// {
// 	// mlx_clear_window(wid->mlx, wid->window);
// 	// mlx_destroy_window(wid->mlx, wid->window);
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
	mlx_hook(widget.window, 2, 0, ft_update, &widget);
	// mlx_loop_hook(widget.mlx, ft_update2, &widget);
	// mlx_hook(widget.window, 3, 0, ft_update2, &widget);
	mlx_loop(widget.mlx);
}