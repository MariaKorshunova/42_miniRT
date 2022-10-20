/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_computing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:33:17 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/19 18:16:44 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define MINIMAL_THRESHOLD 0.0001
#define MAXIMAL_THRESHOLD 0.9998

int	check_for_shadow_spheres(t_global *global, t_ray *ray, t_coord *d)
{
	t_sphere	*sphere;
	float		length;

	sphere = global->scene->obj->spheres;
	length = -1;
	while (sphere)
	{
		length = check_intersection_sphere(sphere, ray, d);
		if (length > MINIMAL_THRESHOLD && length < MAXIMAL_THRESHOLD)
			return (1);
		sphere = sphere->next;
	}
	return (0);
}

int	check_for_shadow_planes(t_global *global, t_ray *ray, t_coord *d)
{
	t_plane	*plane;
	float	dist;

	plane = global->scene->obj->planes;
	while (plane)
	{
		dist = check_intersection_plane(plane, ray, d);
		if (dist > MINIMAL_THRESHOLD && dist < MAXIMAL_THRESHOLD)
			return (1);
		plane = plane->next;
	}
	return (0);
}

int	check_for_shadow_cylinder(t_global *global, t_ray *ray, t_coord *d)
{
	t_cylinder	*cylinder;
	float		dist;

	cylinder = global->scene->obj->cylinders;
	while (cylinder)
	{
		dist = check_intersection_cylinder(cylinder, ray, d);
		if (dist > MINIMAL_THRESHOLD && dist < MAXIMAL_THRESHOLD)
			return (1);
		cylinder = cylinder->next;
	}
	return (0);
}

int	check_for_shadow(t_global *global, t_pixel *pixel_initial)
{
	float	dist;
	t_ray	ray;
	t_coord	d;

	dist = -1;
	ray.point[0] = pixel_initial->d;
	scalar_multiplication(&ray.point[0], -pixel_initial->length * 0.995);
	vector_addition(&ray.point[0], &pixel_initial->ray.point[0],
		&ray.point[0]);
	ray.point[1] = global->scene->obj->lights->point;
	vector_subtraction(&d, &(ray.point[0]), &(ray.point[1]));
	if (check_for_shadow_spheres(global, &ray, &d))
		return (1);
	if (check_for_shadow_planes(global, &ray, &d))
		return (1);
	if (check_for_shadow_cylinder(global, &ray, &d))
		return (1);
	return (0);
}

void	pixel_computing(t_global *global, t_pixel *pixel)
{
	if (pixel->length <= 0
		|| (!pixel->plane && !pixel->sphere && !pixel->cylinder))
	{
		mlx_pixel_put(global->mlx, global->window,
			pixel->x, pixel->y, BACKGROUND_COLOR);
		return ;
	}
	pixel->intersection = pixel->d;
	scalar_multiplication(&pixel->intersection, -pixel->length);
	vector_addition(&pixel->intersection, &pixel->ray.point[0],
		&pixel->intersection);
	if (pixel->plane)
		pixel_computing_plane(global, pixel);
	else if (pixel->sphere)
		pixel_computing_sphere(global, pixel);
	else if (pixel->cylinder)
		mlx_pixel_put(global->mlx, global->window,
			pixel->x, pixel->y, pixel->cylinder->color_ambient);
}
