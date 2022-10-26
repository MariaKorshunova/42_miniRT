/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_pixel_cylinder.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:52:33 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/26 14:54:18 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_coord	normal_cylinder(t_pixel *pixel)
{
	t_coord	v;
	t_coord	res;

	if (pixel->cylinder_type == PIPE)
	{
		scalar_multiplication(&v, &pixel->cylinder->orientation,
			pixel->cylinder_m);
		vector_subtraction(&res, &pixel->intersection, &pixel->cylinder->point);
		vector_subtraction(&res, &res, &v);
	}
	else if (pixel->cylinder_type == PLANE_BEGIN)
		res = pixel->cylinder->plane_begin.orientation;
	else
		res = pixel->cylinder->plane_end.orientation;
	normalizing_vector(&res, &res);
	return (res);
}

static float	pixel_computing_cyliner_diffusal_recflect_ratio(
	t_global *global, t_pixel *pixel)
{
	t_coord	light_direction;
	t_coord	normal;
	float	light_intensity;

	normal = normal_cylinder(pixel);
	vector_subtraction(&light_direction, &global->scene->obj->lights->point,
		&pixel->intersection);
	normalizing_vector(&light_direction, &light_direction);
	light_intensity = angle_between_2_vectors(&light_direction, &normal)
		* global->scene->obj->lights->lighting_ratio;
	if (light_intensity > 0)
		return (light_intensity);
	return (0);
}

void	pixel_computing_cylinder(t_global *global, t_pixel *pixel)
{
	int		light;
	float	lightning_ratio;

	ft_mlx_pixel_put_img(&global->img, pixel->x, pixel->y,
		pixel->cylinder->color_ambient);
	if (!global->scene->obj->lights || check_for_shadow(global, pixel))
		return ;
	lightning_ratio = pixel_computing_cyliner_diffusal_recflect_ratio
		(global, pixel);
	if (lightning_ratio <= 0)
		return ;
	light = color_diffusal(pixel->cylinder->color_ambient,
			pixel->cylinder->color, global->scene->obj->lights->color,
			lightning_ratio);
	ft_mlx_pixel_put_img(&global->img, pixel->x, pixel->y, light);
	return ;
}
