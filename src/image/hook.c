/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:50:13 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/25 13:50:56 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	key_hook(int keycode, t_global *data);
static int	ft_mouse(int mouse, int x, int y, t_global *data);
static void	ft_search_objects(int x, int y, t_global *global);
static void	change_objects(t_global *global, t_pixel *pixel);

int	hook(t_global *data)
{
	mlx_hook(data->window, ON_DESTROY, 0, minirt_close, data);
	mlx_hook(data->window, ON_KEYDOWN, 1L << 0, key_hook, data);
	mlx_mouse_hook(data->window, ft_mouse, data);
	return (0);
}

static int	key_hook(int keycode, t_global *data)
{
	if (keycode == ESC)
		minirt_close(data);
	return (0);
}

int	ft_mouse(int mousecode, int x, int y, t_global *global)
{
	printf("You pressed %d\n", mousecode);
	if (mousecode == 1)
		ft_search_objects(x, y, global);
	return (0);
}

static void	ft_search_objects(int x, int y, t_global *global)
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
	change_objects(global, &pixel);
}

static void	change_objects(t_global *global, t_pixel *pixel)
{
	if (pixel->sphere != NULL)
	{
		global->nearest_obj = pixel->sphere;
		print_spheres((t_sphere *)global->nearest_obj, 'o');
	}
	else if (pixel->plane != NULL)
	{
		global->nearest_obj = pixel->plane;
		print_planes((t_plane *)global->nearest_obj, 'o');
	}
	else if (pixel->cylinder != NULL)
	{
		global->nearest_obj = pixel->cylinder;
		print_cylinders((t_cylinder *)global->nearest_obj, 'o');
	}
}
