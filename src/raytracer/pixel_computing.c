/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_computing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:33:17 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/19 17:51:32 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define MINIMAL_THRESHOLD 0.0001
#define MAXIMAL_THRESHOLD 0.9998

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
	check_for_planes(global, &ray, &d, &dist);
	if (dist > MINIMAL_THRESHOLD && dist < MAXIMAL_THRESHOLD)
		return (1);
	check_for_spheres(global, &ray, &d, &dist);
	if (dist > MINIMAL_THRESHOLD && dist < MAXIMAL_THRESHOLD)
		return (1);
	check_for_cylinder(global, &ray, &d, &dist);
	if (dist > MINIMAL_THRESHOLD && dist < MAXIMAL_THRESHOLD)
		return (1);
	return (0);
}

void	pixel_computing(t_global *global, t_pixel *pixel)
{
	if (!pixel->length || pixel->length == -1
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
