/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:50:13 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/25 21:16:54 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	key_hook(int keycode, t_global *data);
static int	ft_mouse(int mouse, int x, int y, t_global *data);

int	hook(t_global *data)
{
	mlx_hook(data->window, ON_DESTROY, 0, minirt_close, data);
	mlx_hook(data->window, ON_KEYDOWN, 1L << 0, key_hook, data);
	mlx_mouse_hook(data->window, ft_mouse, data);
	return (0);
}

static int	key_hook(int keycode, t_global *global)
{
	if (keycode == ESC)
		minirt_close(global);
	if (global->nearest_obj != NULL)
	{
		printf("keycode = %d, previos_keyhook = %d\n", keycode, global->prev_keyhook);
		if (keycode == X_KEYHOOK)
			global->prev_keyhook = X_KEYHOOK;
		else if (keycode == Y_KEYHOOK)
			global->prev_keyhook = Y_KEYHOOK;
		else
			global->prev_keyhook = Z_KEYHOOK;
		// if ((keycode == GREATER || keycode == LESS)
		// 	&& (global->prev_keyhook == X_KEYHOOK
		// 		|| global->prev_keyhook == Y_KEYHOOK
		// 		|| global->prev_keyhook == Z_KEYHOOK))
			// translate_objects_keyhook(keycode, global);
	}
	return (0);
}

int	ft_mouse(int mousecode, int x, int y, t_global *global)
{
	if (mousecode == 1)
		ft_search_objects(x, y, global);
	if (mousecode == 4 || mousecode == 5)
		ft_resize_object(mousecode, global);
	return (0);
}
