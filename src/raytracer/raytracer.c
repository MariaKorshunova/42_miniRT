/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:46:08 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/15 18:02:44 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		check_intersection(t_global *global, t_ray *ray,
					int *x, int *y);
static float	check_for_spheres(t_global *global, t_ray *ray, int *color);

void	raytracer(t_global *global)
{
	t_ray	ray;
	float	lambda;
	t_coord	camera_plane;
	int		x;
	int		y;

	ray.point[0] = global->scene->camera_point;
	vector_addition(&(camera_plane), &(ray.point[0]),
		&(global->scene->camera_orientation));
	lambda = 2 * global->scene->camera_angles[0] / WIDTH;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			new_vector(&(ray.point[1]),
				global->scene->camera_point.x
				+global->scene->camera_orientation.x
				-global->scene->camera_angles[0] + lambda * x,
				global->scene->camera_point.y
				+ global->scene->camera_orientation.y
				+ global->scene->camera_angles[1] - lambda * y,
				global->scene->camera_point.z
				+ global->scene->camera_orientation.z);
			check_intersection(global, &ray, &x, &y);
			x++;
		}
		y++;
	}
}

static void	check_intersection(t_global *global, t_ray *ray, int *x, int *y)
{
	float	dist;
	// float	nearest_dist;
	int		color;
	// int		nearest_color;

	color = 0;
	dist = check_for_spheres(global, ray, &color);
	if (dist != -1)
		mlx_pixel_put(global->mlx, global->window, *x, *y, color);
}

/* 	Сделать универсальной функцию
	Подсчет вектора луча вытащить наверх,
	чтобы не считать отдельно в каждом фигуре */
static float	check_for_spheres(t_global *global, t_ray *ray, int *color)
{
	t_sphere	*sphere;
	float		tmp;
	float		length;

	sphere = global->scene->obj->spheres;
	length = -1;
	while (sphere)
	{
		tmp = check_intersection_sphere(sphere, ray);
		if (tmp != -1 && (length == -1 || tmp < length))
		{
			length = tmp;
			*color = sphere->color;
		}
		sphere = sphere->next;
	}
	return (length);
}
