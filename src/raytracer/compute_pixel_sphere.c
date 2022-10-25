/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_pixel_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:57:47 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/24 18:44:24 by bpoetess         ###   ########.fr       */
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

float	pixel_computing_sphere_diffusal_recflect_ratio(t_global *global,
	t_pixel *pixel)
{
	t_coord	light_direction;
	t_coord	normal;
	float	light_intensity;

	vector_subtraction(&normal, &pixel->intersection, &pixel->sphere->point);
	normalizing_vector(&normal, &normal);
	vector_subtraction(&light_direction, &global->scene->obj->lights->point,
		&pixel->intersection);
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

	ft_mlx_pixel_put_img(&global->img, pixel->x, pixel->y,
		pixel->sphere->color_ambient);
	if (!global->scene->obj->lights || check_for_shadow(global, pixel))
		return ;
	lightning_ratio = pixel_computing_sphere_diffusal_recflect_ratio
		(global, pixel);
	if (lightning_ratio <= 0)
		return ;
	light = color_diffusal(pixel->sphere->color_ambient, pixel->sphere->color,
			global->scene->obj->lights->color, lightning_ratio);
	ft_mlx_pixel_put_img(&global->img, pixel->x, pixel->y, light);
	return ;
}
