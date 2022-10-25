/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:23:32 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/25 15:06:41 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	define_nearest_objects(t_global *global, t_pixel *pixel);

void	ft_search_objects(int x, int y, t_global *global)
{
	t_pixel	pixel;
	float	lambda;

	global->nearest_obj = NULL;
	lambda = 2 * global->scene->camera_angles[0] / WIDTH;
	pixel_cleaning(&pixel);
	new_vector(&pixel.ray.point[0], 0, 0, 0);
	new_vector(&(pixel.ray.point[1]),
		+global->scene->camera_orientation.x
		-global->scene->camera_angles[0] + lambda * x,
		global->scene->camera_orientation.y
		+ global->scene->camera_angles[1] - lambda * y,
		global->scene->camera_orientation.z);
	check_intersection(global, &pixel);
	define_nearest_objects(global, &pixel);
}

static void	define_nearest_objects(t_global *global, t_pixel *pixel)
{
	if (pixel->sphere != NULL)
	{
		global->nearest_obj = pixel->sphere;
		global->nearest_type = SPHERE;
		print_spheres((t_sphere *)global->nearest_obj, 'o');
	}
	else if (pixel->plane != NULL)
	{
		global->nearest_obj = pixel->plane;
		global->nearest_type = PLANE;
		print_planes((t_plane *)global->nearest_obj, 'o');
	}
	else if (pixel->cylinder != NULL)
	{
		global->nearest_obj = pixel->cylinder;
		global->nearest_type = CYLINDER;
		print_cylinders((t_cylinder *)global->nearest_obj, 'o');
	}
}
