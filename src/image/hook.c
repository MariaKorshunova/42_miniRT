/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:50:13 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/27 17:44:52 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	key_hook(int keycode, t_global *data);
static int	ft_mouse(int mouse, int x, int y, t_global *data);
static void	translate_rotate_objects(int keycode, t_global *global);

int	hook(t_global *data)
{
	mlx_hook(data->window, ON_DESTROY, 0, minirt_close, data);
	mlx_hook(data->window, ON_KEYDOWN, 1L << 0, key_hook, data);
	mlx_mouse_hook(data->window, ft_mouse, data);
	return (0);
}

void	go_by_key(int keycode, t_global *global)
{
	t_coord	coord;

	if (keycode == W_KEYHOOK)
		new_vector(&coord, 0, 0, 1);
	if (keycode == S_KEYHOOK)
		new_vector(&coord, 0, 0, -1);
	if (keycode == A_KEYHOOK)
		new_vector(&coord, -1, 0, 0);
	if (keycode == D_KEYHOOK)
		new_vector(&coord, 1, 0, 0);
	translate_objects(global->scene, &coord);
	raytracer(global);
}

void	rotate_by_key(int keycode, t_global *global)
{
	t_coord	coord;

	if (keycode == LEFT)
		new_vector(&coord, -0.2, 0, 0.97979);
	if (keycode == RIGHT)
		new_vector(&coord, 0.2, 0, 0.97979);
	if (keycode == UP)
		new_vector(&coord, 0, -0.2, 0.97979);
	if (keycode == DOWN)
		new_vector(&coord, 0, 0.2, 0.97979);
	rotate_objects(global->scene, &coord);
	raytracer(global);
}

static int	key_hook(int keycode, t_global *global)
{
	if (keycode == ESC)
		minirt_close(global);
	else if (keycode == X_KEYHOOK)
		global->prev_keyhook = X_KEYHOOK;
	else if (keycode == Y_KEYHOOK)
		global->prev_keyhook = Y_KEYHOOK;
	else if (keycode == Z_KEYHOOK)
		global->prev_keyhook = Z_KEYHOOK;
	else if (keycode == H_KEYHOOK)
		global->prev_keyhook = H_KEYHOOK;
	if (global->nearest_obj != NULL)
	{
		if ((keycode == GREATER || keycode == LESS
				|| keycode == UP || keycode == DOWN)
			&& (global->prev_keyhook == X_KEYHOOK
				|| global->prev_keyhook == Y_KEYHOOK
				|| global->prev_keyhook == Z_KEYHOOK))
			translate_rotate_objects(keycode, global);
		else if (global->prev_keyhook == H_KEYHOOK
			&& global->nearest_type == CYLINDER
			&& (keycode == GREATER || keycode == LESS))
			change_height_cylinder(keycode, global);
	}
	else
	{
		if (keycode == W_KEYHOOK || keycode == S_KEYHOOK
			|| keycode == A_KEYHOOK || keycode == D_KEYHOOK)
			go_by_key(keycode, global);
		if (keycode == LEFT || keycode == RIGHT
			|| keycode == UP || keycode == DOWN)
			rotate_by_key(keycode, global);
	}
	return (0);
}

static void	translate_rotate_objects(int keycode, t_global *global)
{
	if (global->nearest_type == SPHERE)
		change_sphere(keycode, global);
	else if (global->nearest_type == CYLINDER)
		change_cylinder(keycode, global);
	else if (global->nearest_type == PLANE)
		change_plane(keycode, global);
	raytracer(global);
}

static int	ft_mouse(int mousecode, int x, int y, t_global *global)
{
	if (mousecode == 1)
		ft_search_objects(x, y, global);
	else if (mousecode == 4 || mousecode == 5)
		ft_resize_object(mousecode, global);
	else if (mousecode == 2)
	{
		global->nearest_obj = NULL;
		global->prev_keyhook = 0;
	}	
	return (0);
}
