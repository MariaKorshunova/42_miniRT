/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:50:13 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/24 18:30:27 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	key_hook(int keycode, t_global *data);
static int	ft_mouse_hook(int mousecode, int x, int y, t_global *data);

void	hook(t_global *data)
{
	mlx_hook(data->window, ON_DESTROY, 0, minirt_close, data);
	mlx_hook(data->window, ON_KEYDOWN, 1L << 0, key_hook, data);
	mlx_mouse_hook(data->window, ft_mouse_hook, data);
}

static int	key_hook(int keycode, t_global *data)
{
	if (keycode == ESC)
		minirt_close(data);
	return (0);
}

static int	ft_mouse_hook(int mousecode, int x, int y, t_global *global)
{
	t_pixel	pixel;
	float	lambda;
	
	if (mousecode == 1)
	{
		global->nearest_obj = NULL;
		lambda = 2 * global->scene->camera_angles[0] / WIDTH;
		pixel_cleaning(&pixel);
		new_vector(&(pixel.ray.point[1]),
			+global->scene->camera_orientation.x
			-global->scene->camera_angles[0] + lambda * pixel.x,
			global->scene->camera_orientation.y
			+ global->scene->camera_angles[1] - lambda * pixel.y,
			0);
		check_intersection(global, &pixel);
		global->nearest_obj = pixel.sphere;
	}
	// printf("mouse_hook %d!\n", mousecode);
	// printf("x= %d!\n", x);
	// printf("y= %d!\n", y);
	return (0);
}

/*  additional function for finding int keyhook
	mlx_key_hook(data->window, key_print_hook, data); */
int	key_print_hook(int keycode, t_global *data)
{
	(void) data;
	printf("Hello from key_hook %d!\n", keycode);
	return (0);
}
