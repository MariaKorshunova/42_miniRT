/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:46:08 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/15 20:54:55 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		check_intersection(t_global *global, t_ray *ray,
					int *x, int *y);
static float	check_for_spheres(t_global *global, t_ray *ray,
					t_coord *d, int *color);
static float	check_for_planes(t_global *global, t_ray *ray,
					t_coord *d, int *color);

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
	float	nearest_dist;
	int		color;
	t_coord	d;

	color = 0;
	nearest_dist = -1;
	vector_subtraction(&d, &ray->point[0], &(ray->point[1]));
	dist = check_for_planes(global, ray, &d, &color);
	if (dist != -1)
		nearest_dist = dist;
	dist = check_for_spheres(global, ray, &d, &color);
	if (dist != -1 && dist < nearest_dist)
		nearest_dist = dist;
	if (nearest_dist != -1)
		mlx_pixel_put(global->mlx, global->window, *x, *y, color);
}

static float	check_for_spheres(t_global *global, t_ray *ray,
					t_coord *d, int *color)
{
	t_sphere	*sphere;
	float		tmp;
	float		length;

	sphere = global->scene->obj->spheres;
	length = -1;
	while (sphere)
	{
		tmp = check_intersection_sphere(sphere, ray, d);
		if (tmp != -1 && (length == -1 || tmp < length))
		{
			length = tmp;
			*color = sphere->color;
		}
		sphere = sphere->next;
	}
	return (length);
}

static float	check_for_planes(t_global *global, t_ray *ray,
					t_coord *d, int *color)
{
	t_plane	*plane;
	float	dist;
	float	nearest_dist;

	plane = global->scene->obj->planes;
	nearest_dist = -1;
	while (plane)
	{
		dist = check_intersection_plane(plane, ray, d);
		if (dist != -1 && (nearest_dist == -1 || dist < nearest_dist))
		{
			nearest_dist = dist;
			*color = plane->color;
		}
		plane = plane->next;
	}
	return (nearest_dist);
}
