/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:58:09 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/19 15:19:26 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*  ray.point[0] = global->scene->camera_point; Точка камеры (точка a)
    = координата луча на проецирумой плоскости
    Vector d = ray.point[0] -  ray.point[1] (вектор луча)
*/

void	check_intersection(t_global *global, t_pixel *pixel)
{
	float		dist;

	pixel->plane = 0;
	pixel->sphere = 0;
	pixel->cylinder = 0;
	dist = -1;
	pixel->length = -1;
	vector_subtraction(&(pixel->d),
		&(pixel->ray.point[0]), &(pixel->ray.point[1]));
	pixel->plane = check_for_planes(global, &pixel->ray, &(pixel->d), &dist);
	if (dist != -1)
		pixel->length = dist;
	pixel->sphere = check_for_spheres(global, &pixel->ray, &pixel->d, &dist);
	if (dist > 0 && (pixel->length == -1 || dist < pixel->length))
	{
		pixel->length = dist;
		pixel->plane = 0;
	}
	pixel->cylinder = check_for_cylinder(global, &pixel->ray, &pixel->d, &dist);
	if (dist != -1 && dist < pixel->length)
	{
		pixel->length = dist;
		pixel->plane = 0;
		pixel->sphere = 0;
	}
}

t_sphere	*check_for_spheres(t_global *global, t_ray *ray,
					t_coord *d, float *dist)
{
	t_sphere	*sphere;
	t_sphere	*closest_sphere;
	float		tmp;
	float		length;

	sphere = global->scene->obj->spheres;
	closest_sphere = 0;
	length = -1;
	while (sphere)
	{
		tmp = check_intersection_sphere(sphere, ray, d);
		if (tmp > 0 && (length == -1 || tmp < length))
		{
			length = tmp;
			closest_sphere = sphere;
		}
		sphere = sphere->next;
	}
	*dist = length;
	return (closest_sphere);
}

t_plane	*check_for_planes(t_global *global, t_ray *ray,
					t_coord *d, float *dist)
{
	t_plane	*plane;
	t_plane	*nearest_plane;
	float	nearest_dist;

	plane = global->scene->obj->planes;
	nearest_dist = -1;
	nearest_plane = 0;
	while (plane)
	{
		*dist = check_intersection_plane(plane, ray, d);
		if (*dist != -1 && (nearest_dist == -1 || *dist < nearest_dist))
		{
			nearest_dist = *dist;
			nearest_plane = plane;
		}
		plane = plane->next;
	}
	*dist = nearest_dist;
	return (nearest_plane);
}

t_cylinder	*check_for_cylinder(t_global *global, t_ray *ray,
						t_coord *d, float *dist)
{
	t_cylinder	*cylinder;
	t_cylinder	*nearest_cylinder;
	float		nearest_dist;

	cylinder = global->scene->obj->cylinders;
	nearest_dist = -1;
	nearest_cylinder = 0;
	while (cylinder)
	{
		*dist = check_intersection_cylinder(cylinder, ray, d);
		if (*dist != -1 && (nearest_dist == -1 || *dist < nearest_dist))
		{
			nearest_dist = *dist;
			nearest_cylinder = cylinder;
		}
		cylinder = cylinder->next;
	}
	*dist = nearest_dist;
	return (nearest_cylinder);
}
