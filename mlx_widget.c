/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_widget.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:48:01 by samjaabo          #+#    #+#             */
/*   Updated: 2023/06/08 13:38:08 by moouaamm         ###   ########.fr       */
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
	//this function is from chatGPT

void ft_draw_line(t_widget *w, int x1, int y1, int x2, int y2, int color)
{
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
void draw_map(t_widget *w)
{
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
}

static void	mlx_show_widget(t_widget *w)
{
	int a;
	int b;

	draw_map(w);
	w->player->x += w->mv_x;
	w->player->y += w->mv_y;
	ft_draw_line(w, w->player->x , w->player->y ,(w->player->x) + (cos(w->player->rotationAngle) * RAY_SIZE) ,
		(w->player->y) + (sin(w->player->rotationAngle) * RAY_SIZE), PLAYER_COLOR);
	ft_player(w, w->player->x , w->player->y, PLAYER_COLOR);
	w->mv_x = 0;
	w->mv_y = 0;
	ft_cast_rays(w);
	// printf("%f\n",w->ray * 180 / PI);
}

void	__init__(t_widget *widget, char **map, t_palyer *player, t_ray *ray)
{
	int	tmp;

	widget->map = map;
	// ft_map_rules(widget->map);
	widget->mlx = mlx_init();
	widget->cols = ft_count_cols(widget->map);
	widget->rows = ft_count_rows(widget->map);
	widget->row = 0;
	widget->col = 0;
	widget->mv_x = 0;
	widget->mv_y = 0;
	widget->window = mlx_new_window(widget->mlx, widget->cols * SIZE,
			widget->rows * SIZE, "Cub3d");
	widget->player = player;
	widget->ray = ray;
	widget->size = SIZE;
	// ft_is_not_null(widget);
	mlx_show_widget(widget);
}

int	ft_update2(t_widget *w)
{
	int moves;

	moves = 0;
	mlx_clear_window(w->mlx, w->window);
	mlx_show_widget(w);

}

int	there_is_wall(t_widget *w, int x, int y)
{
	double	pos_x;
	double	pos_y;
	int a;
	int b;

	if (!w)
		printf("hello mf\n");
	if (!w->player)
		printf("here it collapses\n");
	a = (int)(w->player->x + x) / SIZE;
	b = (int)(w->player->y + y) / SIZE;
	// printf("%d\n%d\n//////////////////\n",w->player->x, w->player->y);
	// printf("%d\n%d\n",a,b);
	// printf("*************\n");
	if(a < 0 || a > w->cols || b < 0 || b > w->rows)
		return (1);
	if (w->map[b][a] && w->map[b][a] == '1')
		return(1);
	return(0);
		// printf("##############\n")
}

int	ft_release(int key, t_widget *w)
{
	int moves;

	if (key == 2 || key == 124 || key == 0 || key == 123 || key == 1 ||
		key == 125 || key == 13 || key == 126) //up *******
	{
		moves = 0;
		w->mv_x = 0;
		w->mv_y = 0;
		w->player->trnDir = 0;
		w->player->walkDirection = 0;
	}
}
int	ft_press(int key, t_widget *w)
{
	int a,b;

	if (key == 2 || key == 124)  //right *********
		w->player->trnDir = 1;
	else if (key == 0 || key == 123) //left *******
		w->player->trnDir = -1;
	if (key == 1 || key == 125) //down **********
		w->player->walkDirection = -1;
	else if (key == 13 || key == 126) //up *******
		w->player->walkDirection = 1;
	// if (w->player->trnDir)
	// 	w->player->rotationAngle += w->player->trnDir * w->player->rotationSpeed;
	// if (w->player->walkDirection)
	// 	w->player->walkDirection *= w->player->moveSpeed;
	// a = w->player->walkDirection * cos(w->player->rotationAngle);
	// b = w->player->walkDirection * sin(w->player->rotationAngle);
	// if (there_is_wall(w, a, b))
	// 	return (0);
	// else
	// {
	// 	w->mv_x = a;
	// 	w->mv_y = b;
	// 	mlx_clear_window(w->mlx, w->window);
	// 	mlx_show_widget(w);
	// }
	return (0);
}
int	next_frame(t_widget *w)
{
	int a, b;

	if (w->player->trnDir)
		w->player->rotationAngle += w->player->trnDir * w->player->rotationSpeed;
	if (w->player->walkDirection)
		w->player->walkDirection *= w->player->moveSpeed;
	a = w->player->walkDirection * cos(w->player->rotationAngle);
	b = w->player->walkDirection * sin(w->player->rotationAngle);
	if (there_is_wall(w, a, b))
		return (0);
	else
	{
		w->mv_x = a;
		w->mv_y = b;
		mlx_clear_window(w->mlx, w->window);
		mlx_show_widget(w);
	}
	return (0);
}
// static int	ft_destroy(t_parsing *data)
// {
// 	// mlx_clear_window(wid->mlx, wid->window);
// 	// mlx_destroy_window(wid->mlx, wid->window);
// 	ft_exit_invalid_data(data, -1);
// 	return (0);
// }

// void	_init_ray(t_widget *w, t_ray *ray)
// {
// 	ray->ray_angle = w->player->rotationAngle - (FOV / 2) ;//- (PI / 2)
// }

void	ft_run_widget(t_parsing *data, t_palyer *player)
{
	t_widget	*widget;
	t_ray		ray;

	// ft_is_true_args(argc, argv);
	// _init_ray(&widget, &ray);
	widget = NULL;
	widget = malloc (sizeof(t_widget));
	if (!widget)
		printf("errror allocate to widget\n");
	__init__(widget, data->map, player, &ray);
	// mlx_hook(widget.window, ON_KEYDOWN, USELESS, ft_exec_move, &widget);
	// mlx_hook(widget.window, ON_DESTROY, USELESS, ft_destroy, data);
	mlx_hook(widget->window, 3, 0, ft_release, widget);
	mlx_hook(widget->window, 2, 0, ft_press, widget);
	mlx_loop_hook(widget->mlx, next_frame, widget);
	// mlx_hook(widget.window, 3, 0, ft_update2, &widget);
	mlx_loop(widget->mlx);
}