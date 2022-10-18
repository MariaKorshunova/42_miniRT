/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:46:08 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/18 15:04:18 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

float	pixel_computing_sphere_diffusal_reclect_ratio(t_global *global,
	t_pixel *pixel)
{
	t_coord	intersection;
	t_coord	light_direction;
	t_coord	normal;
	float	light_intensity;

	intersection = pixel->d;
	scalar_multiplication(&intersection, -pixel->length);
	vector_addition(&intersection, &pixel->ray.point[0], &intersection);
	vector_subtraction(&normal, &intersection, &pixel->sphere->point);
	normalizing_vector(&normal, &normal);
	vector_subtraction(&light_direction, &global->scene->obj->lights->point,
		&intersection);
	normalizing_vector(&light_direction, &light_direction);
	light_intensity = scalar_product_2_vectors(&light_direction, &normal)
		* global->scene->obj->lights->lighting_ratio;
	if (light_intensity > 0)
		return (light_intensity);
	return (0);
}

int	color_diffusal(int color_sum, int color1, int color2, float intensity)
{
	int	res;
	int	tmp;

	intensity /= (float) 255;
	tmp = (color_sum >> 16 & 0xff)
		+ (int)(intensity * ((float)(color1 >> 16 & 255)
				*((float)(color2 >> 16 & 255))));
	if (tmp > 255)
		res = 0xff0000;
	else
		res = tmp << 16;
	tmp = (color_sum >> 8 & 0xff)
		+ (int)(intensity * ((float)(color1 >> 8 & 255)
				*((float)(color2 >> 8 & 255))));
	if (tmp > 255)
		res |= 0xff00;
	else
		res |= tmp << 8;
	tmp = (color_sum & 0xff)
		+ (int)(intensity * (((float)(color1 & 255) *((float)(color2 & 255)))));
	if (tmp > 255)
		res |= 0xff;
	else
		res |= tmp;
	return (res);
}

void	pixel_computing_sphere(t_global *global, t_pixel *pixel)
{
	int		light;
	float	lightning_ratio;

	mlx_pixel_put(global->mlx, global->window,
		pixel->x, pixel->y, pixel->sphere->color_ambient);
	if (!global->scene->obj->lights)
		return ;
	lightning_ratio = pixel_computing_sphere_diffusal_reclect_ratio
		(global, pixel);
	if (lightning_ratio <= 0)
		return ;
	light = color_diffusal(pixel->sphere->color_ambient, pixel->sphere->color,
			global->scene->obj->lights->color, lightning_ratio);
	mlx_pixel_put(global->mlx, global->window,
		pixel->x, pixel->y, light);
	return ;
}

void	pixel_computing(t_global *global, t_pixel *pixel)
{
	if (!pixel->length || (!pixel->plane && !pixel->sphere && !pixel->cylinder))
		mlx_pixel_put(global->mlx, global->window,
			pixel->x, pixel->y, BACKGROUND_COLOR);
	else if (pixel->plane)
		mlx_pixel_put(global->mlx, global->window,
			pixel->x, pixel->y, pixel->plane->color_ambient);
	else if (pixel->sphere)
		pixel_computing_sphere(global, pixel);
	else if (pixel->cylinder)
		mlx_pixel_put(global->mlx, global->window,
			pixel->x, pixel->y, pixel->cylinder->color_ambient);
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
