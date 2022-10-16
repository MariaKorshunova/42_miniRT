/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:46:08 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/16 09:19:12 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_pixel
{
	int			x;
	int			y;
	t_ray		ray;
	t_coord		d;
	float		length;
	t_coord		intersection;
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
}	t_pixel;

static void			check_intersection(t_global *global, t_pixel *pixel);
static t_sphere		*check_for_spheres(t_global *global, t_ray *ray,
						t_coord *d, float *dist);
static t_plane		*check_for_planes(t_global *global, t_ray *ray,
						t_coord *d, float *dist);

void	pixel_cleaning(t_pixel *pixel)
{
	pixel->ray.point[1].x = 0;
	pixel->ray.point[1].y = 0;
	pixel->ray.point[1].z = 0;
	pixel->length = 0;
	pixel->intersection.x = 0;
	pixel->intersection.y = 0;
	pixel->intersection.z = 0;
	pixel->plane = 0;
	pixel->sphere = 0;
	pixel->cylinder = 0;
}

void	pixel_computing(t_global *global, t_pixel *pixel)
{
	if (!pixel->plane && !pixel->sphere && !pixel->cylinder)
		mlx_pixel_put(global->mlx, global->window, pixel->x, pixel->y, 0);
	else if (pixel->plane)
		mlx_pixel_put(global->mlx, global->window,
			pixel->x, pixel->y, pixel->plane->color_ambient);
	else if (pixel->sphere)
		mlx_pixel_put(global->mlx, global->window,
			pixel->x, pixel->y, pixel->sphere->color_ambient);
}

void	raytracer(t_global *global)
{
	float	lambda;
	t_pixel	pixel;
	t_coord	camera_plane;

	pixel.ray.point[0] = global->scene->camera_point;
	vector_addition(&(camera_plane), &(pixel.ray.point[0]),
		&(global->scene->camera_orientation));
	lambda = 2 * global->scene->camera_angles[0] / WIDTH;
	pixel.y = 0;
	while (pixel.y < HEIGHT)
	{
		pixel.x = 0;
		while (pixel.x < WIDTH)
		{
			pixel_cleaning(&pixel);
			new_vector(&(pixel.ray.point[1]),
				global->scene->camera_point.x
				+global->scene->camera_orientation.x
				-global->scene->camera_angles[0] + lambda * pixel.x,
				global->scene->camera_point.y
				+ global->scene->camera_orientation.y
				+ global->scene->camera_angles[1] - lambda * pixel.y,
				global->scene->camera_point.z
				+ global->scene->camera_orientation.z);
			check_intersection(global, &pixel);
			pixel_computing(global, &pixel);
			pixel.x++;
		}
		pixel.y++;
	}
}

static void	check_intersection(t_global *global, t_pixel *pixel)
{
	float		dist;

	pixel->plane = 0;
	pixel->sphere = 0;
	pixel->cylinder = 0;
	pixel->length = -1;
	vector_subtraction(&(pixel->d),
		&(pixel->ray.point[0]), &(pixel->ray.point[1]));
	pixel->plane = check_for_planes(global, &pixel->ray, &(pixel->d), &dist);
	if (dist != -1)
		pixel->length = dist;
	pixel->sphere = check_for_spheres(global, &pixel->ray, &pixel->d, &dist);
	if (dist != -1 && dist < pixel->length)
	{
		pixel->length = dist;
		pixel->plane = 0;
	}
}

static t_sphere	*check_for_spheres(t_global *global, t_ray *ray,
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
		if (tmp != -1 && (length == -1 || tmp < length))
		{
			length = tmp;
			closest_sphere = sphere;
		}
		sphere = sphere->next;
	}
	*dist = length;
	return (closest_sphere);
}

static t_plane	*check_for_planes(t_global *global, t_ray *ray,
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
