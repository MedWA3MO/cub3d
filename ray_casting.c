/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:00:10 by moouaamm          #+#    #+#             */
/*   Updated: 2023/06/06 03:48:27 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_ray(t_ray *ray)

{

}

int	*horizontal_intersection(t_widget *w, t_ray *ray, double angle)
{
	int	*point_a;
	double dx;
	double dy;

	//find first intersection point A:
	point_a = malloc (2 * sizeof(int));
	if (!point_a)
		return (NULL);
	point_a[1] = floor(w->player->y / SIZE) * SIZE;
	if(ray->down)
		point_a[1] += SIZE;
	point_a[0] = w->player->x + ((w->player->y - point_a[1]) / tan(angle));
	// calculate the steps dx and dy:
	dy = SIZE;//1
	if (!ray->down)
		dy *= -1;
	dx = dy / tan(angle);
	if ((!ray->right && dx > 0 ) || (ray->right && dx < 0))
		dx *= -1;
	//increment from the point A and check every time for intersection
	while (!there_is_wall(w, point_a[0], point_a[1]))
	{
		point_a[0] += dx;
		point_a[1] += dy;
	}
	ft_draw_line(w, w->player->x, w->player->y, point_a[0], point_a[1], YELLOW);
	return(point_a);
}

double protect_angle(t_ray *ray, double angle)
{
	ray->down = 0;
	ray->right = 0;
	angle = (int)angle % (int)(2 * PI);
	if (angle < 0 )
		angle += (2 * PI);
	if (angle > 0 && angle < PI)
		ray->down = 1;
	if (angle < (PI / 2) && angle < (3 * PI / 2))
		ray->right = 1;
	return (angle);
}

void create_ray(t_widget *w, t_ray *ray, double angle)
{
	int *h_inter;

	ray->ray_angle = angle;
	h_inter = malloc (2 * sizeof(int));
	if (!h_inter)
		printf("nnnnn\n");
	angle = protect_angle(ray, angle);

	h_inter = horizontal_intersection(w, ray, angle);
	ft_draw_line(w, w->player->x, w->player->y, w->player->x + h_inter[0],
					w->player->y + h_inter[1], PLAYER_COLOR);
}
void	 cast_one(t_widget *w, t_ray *ray)
{

}

void	ft_cast_rays(t_widget *w)
{
	double	ray_angle;
	int i;
	t_ray	*ray;

	ray = malloc(sizeof(ray) * NUM_RAYS);
	ray_angle = w->player->rotationAngle - (FOV / 2);
	i = 0;

	while (i < 1) // numrays
	{
		create_ray(w, &ray[i], ray_angle);
		// cast_one(w, &ray[i]);
		ray_angle = ray_angle + (FOV / NUM_RAYS) ;
		i++;
	}
}