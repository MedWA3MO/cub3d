/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:00:10 by moouaamm          #+#    #+#             */
/*   Updated: 2023/06/07 10:15:25 by moouaamm         ###   ########.fr       */
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
		return (printf("hi\n"), NULL);
	point_a[1] = floor(w->player->y / SIZE) * SIZE;
	if(ray->down)
		point_a[1] += SIZE;
	point_a[0] = w->player->x + ((w->player->y - point_a[1]) / tan(angle));
	// calculate the steps dx and dy:
	dy = SIZE;//1
	if (!ray->down)
		dy *= -1;
	dx = SIZE / tan(angle);
	if ((!ray->right && dx > 0 ) || (ray->right && dx < 0))
		dx *= -1;
	//increment from the point A and check every time for intersection
	while (!there_is_wall(w, point_a[0], point_a[1]))
	{
		point_a[0] += dx;
		point_a[1] += dy;
	}
	return(point_a);
}

int	*vertical_intersection(t_widget *w, t_ray *ray, double angle)
{
	int	*point_a;
	double dx;
	double dy;

	//find first intersection point A:
	point_a = malloc (2 * sizeof(int));
	if (!point_a)
		return (printf("hi\n"), NULL);
	point_a[0] = floor(w->player->x / SIZE) * SIZE;
	if(ray->right)
		point_a[0] += SIZE;
	point_a[1] = w->player->y + ((point_a[0] - w->player->x) / tan(angle));
	// calculate the steps dx and dy:
	dx = SIZE;//1
	if (!ray->right)
		dx *= -1;
	dy = SIZE / tan(angle);
	if ((!ray->down && dy > 0 ) || (ray->down && dy < 0))
		dy *= -1;
	//increment from the point A and check every time for intersection
	while (!there_is_wall(w, point_a[0], point_a[1]))
	{
		point_a[0] += dx;
		point_a[1] += dy;
	}
	return(point_a);
}

double protect_angle(t_ray *ray, double angle)
{
	angle = (int)angle % (int)(2 * PI);
	if (angle < 0 )
		angle += (2 * PI);
	if (ray)
	{
		ray->down = 0;
		ray->right = 0;
		if (angle > 0 && angle < PI)
			ray->down = 1;
		if (angle < (PI / 2) && angle < (3 * PI / 2))
			ray->right = 1;
	}
	return (angle);
}

void create_ray(t_widget *w, t_ray *ray, double angle)
{
	int *h_inter;
	int *v_inter;

	// ray->ray_angle = angle;
	h_inter = malloc (2 * sizeof(int));
	if (!h_inter)
		printf("nnnnn\n");
	angle = protect_angle(ray, angle);

	h_inter = horizontal_intersection(w, ray, angle);
	v_inter = vertical_intersection(w, ray, angle);
	//compare between two points and keep the closest
	ft_draw_line(w, w->player->x, w->player->y,
					 w->player->x + cos(angle) * RAY_SIZE,
					w->player->y + sin(angle) * RAY_SIZE, YELLOW);
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
	printf("%f\n",ray_angle);
	printf("%f\n",w->player->rotationAngle);
	i = 0;

	while (i < NUM_RAYS) // numrays
	{
		create_ray(w, &ray[i], ray_angle);
		// cast_one(w, &ray[i]);
		ray_angle = ray_angle + (FOV / NUM_RAYS) ;
		i++;
	}
}