/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:06:58 by samjaabo          #+#    #+#             */
/*   Updated: 2023/06/06 03:14:11 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "./libft/libft.h"
# include "get_next_line.h"

# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <errno.h>

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# include <stdarg.h>
# include <stdint.h>
# include <limits.h>

# include <sys/time.h>
#include <signal.h>
#include <mlx.h>
#include <math.h>

#define PI 3.14159265359
#define YELLOW 0xFFFF00
#define STRP_THICK 1
#define FOV 60 * PI / 180 // 80 degree is choosed to be my field of view.
#define NUM_RAYS 1200 / STRP_THICK // resolution 320 x 200 (width x hight of my window)
#define ONE_COLOR 0x2baced
#define ZERO_COLOR 0xffffff
#define SPACE_COLOR 0xd671f0
#define PLAYER_COLOR 0xff0000
#define PADDING 1
#define SIZE 50
#define PLAYER_SIZE 3
#define RAY_SIZE 40


// ========== Point ====

typedef struct s_point
{
	int x;
	int y;
}t_point;


// ======== ray struct ====

typedef struct  s_ray
{
	double	ray_angle;
	int		down;
	int		right;
}t_ray;

//=======player struct=====

typedef struct s_player
{
	int		x;
	int		y;
	int		trnDir;
	int		walkDirection;
	double	rotationAngle;
	int		moveSpeed;
	double	rotationSpeed;
}	t_palyer;

// ======= Widget struct =======


typedef struct widget_s {
	int		mv_x;
	int		mv_y;
	char	**map;
	void	*mlx;
	void	*window;
	void	*ground_img;
	void	*wall_img;
	void	*player_img;
	void	*collect_img;
	void	*exit_img;
	int		rows;
	int		cols;
	int		row;
	int		col;
	int		size;
	int		a;
	int		b;
	t_palyer	*player;
	t_ray		*ray;
}			t_widget;

enum e_constant
{
	NO = -1,
	EA = -2,
	WE = -3,
	SO = -4,
	FF = -5,
	CC = -6,
	USELESS = 0,
	COL = 0,
	ROW = 1,
	ON_KEYDOWN = 2,
	ON_DESTROY = 17,
};

typedef union u_color
{
	int	argb;
	struct s_argb
	{
		int	a:8;
		int	r:8;
		int	g:8;
		int	b:8;
	} bytes;
}	t_color;

typedef struct s_parsing
{
	char	**arr;
	char	**map;
	char	*north;
	char	*south;
	char	*weast;
	char	*east;
	char	*floor;
	char	*roof;
	int		ifloor;
	int		iroof;
	int		index;
}	t_parsing;

// genral structe:
typedef struct s_gen
{
	t_palyer	*player;
	t_widget	*widget;
}t_gen;
//=============utils.c===============
void 		ft_printar(char **t);
void		ft_perror(const char *msg);
void		ft_error(const char *msg);
char		*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char		*ft_clear(char **ar);
void		ft_exit(t_parsing *data, char *err);
void		ft_exit_invalid_data(t_parsing *data, int line);

int	ft_update(int key, t_widget *w);
void	__init__(t_widget *widget, char **map, t_palyer *player, t_ray *ray);

//map.c
int			ft_count_cols(char **map);
t_parsing	*ft_read_map(char *file);
void		ft_extract_data(t_parsing *data);
void		ft_read_real_map(t_parsing *data);

//==========mlx=====
void	ft_run_widget(t_parsing *data, t_palyer *player);
void ft_draw_line(t_widget *w, int x1, int y1, int x2, int y2, int color);

//============= ray casting
void	ft_cast_rays(t_widget *w);
int	there_is_wall(t_widget *w, int x, int y);

#endif