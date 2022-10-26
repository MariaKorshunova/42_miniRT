/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:42:28 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/26 12:41:25 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rotate_cylinder(int keycode, t_global *global);
static void	rotate_plane(int keycode, t_global *global);

void	change_sphere(int keycode, t_global *global)
{
	if (global->prev_keyhook == X_KEYHOOK)
	{
		if (keycode == GREATER)
			((t_sphere *)(global->nearest_obj))->point.x += STEP_TRANSLATE;
		else if (keycode == LESS)
			((t_sphere *)(global->nearest_obj))->point.x -= STEP_TRANSLATE;
	}
	else if (global->prev_keyhook == Y_KEYHOOK)
	{
		if (keycode == GREATER)
			((t_sphere *)(global->nearest_obj))->point.y += STEP_TRANSLATE;
		else if (keycode == LESS)
			((t_sphere *)(global->nearest_obj))->point.y -= STEP_TRANSLATE;
	}
	else if (global->prev_keyhook == Z_KEYHOOK)
	{
		if (keycode == GREATER)
			((t_sphere *)(global->nearest_obj))->point.z += STEP_TRANSLATE;
		else if (keycode == LESS)
			((t_sphere *)(global->nearest_obj))->point.z -= STEP_TRANSLATE;
	}
}

void	change_cylinder(int keycode, t_global *global)
{
	if (keycode == UP || keycode == DOWN)
		rotate_cylinder(keycode, global);
	else if (global->prev_keyhook == X_KEYHOOK)
	{
		if (keycode == GREATER)
			((t_cylinder *)(global->nearest_obj))->point.x += STEP_TRANSLATE;
		else if (keycode == LESS)
			((t_cylinder *)(global->nearest_obj))->point.x -= STEP_TRANSLATE;
	}
	else if (global->prev_keyhook == Y_KEYHOOK)
	{
		if (keycode == GREATER)
			((t_cylinder *)(global->nearest_obj))->point.y += STEP_TRANSLATE;
		else if (keycode == LESS)
			((t_cylinder *)(global->nearest_obj))->point.y -= STEP_TRANSLATE;
	}
	else if (global->prev_keyhook == Z_KEYHOOK)
	{
		if (keycode == GREATER)
			((t_cylinder *)(global->nearest_obj))->point.z += STEP_TRANSLATE;
		else if (keycode == LESS)
			((t_cylinder *)(global->nearest_obj))->point.z -= STEP_TRANSLATE;
	}
}

static void	rotate_cylinder(int keycode, t_global *global)
{
	if (global->prev_keyhook == X_KEYHOOK)
	{
		if (keycode == UP)
			((t_cylinder *)(global->nearest_obj))->orientation.x += STEP_ROTATE;
		else if (keycode == DOWN)
			((t_cylinder *)(global->nearest_obj))->orientation.x -= STEP_ROTATE;
	}
	else if (global->prev_keyhook == Y_KEYHOOK)
	{
		if (keycode == UP)
			((t_cylinder *)(global->nearest_obj))->orientation.y += STEP_ROTATE;
		else if (keycode == DOWN)
			((t_cylinder *)(global->nearest_obj))->orientation.y -= STEP_ROTATE;
	}
	else if (global->prev_keyhook == Z_KEYHOOK)
	{
		if (keycode == UP)
			((t_cylinder *)(global->nearest_obj))->orientation.z += STEP_ROTATE;
		else if (keycode == DOWN)
			((t_cylinder *)(global->nearest_obj))->orientation.z -= STEP_ROTATE;
	}	
	normalizing_vector(&((t_cylinder *)(global->nearest_obj))->orientation,
		&((t_cylinder *)(global->nearest_obj))->orientation);
}

void	change_plane(int keycode, t_global *global)
{
	if (keycode == UP || keycode == DOWN)
		rotate_plane(keycode, global);
	if (global->prev_keyhook == X_KEYHOOK)
	{
		if (keycode == GREATER)
			((t_plane *)(global->nearest_obj))->point.x += STEP_TRANSLATE;
		else if (keycode == LESS)
			((t_plane *)(global->nearest_obj))->point.x -= STEP_TRANSLATE;
	}
	else if (global->prev_keyhook == Y_KEYHOOK)
	{
		if (keycode == GREATER)
			((t_plane *)(global->nearest_obj))->point.y += STEP_TRANSLATE;
		else if (keycode == LESS)
			((t_plane *)(global->nearest_obj))->point.y -= STEP_TRANSLATE;
	}
	else if (global->prev_keyhook == Z_KEYHOOK)
	{
		if (keycode == GREATER)
			((t_plane *)(global->nearest_obj))->point.z += STEP_TRANSLATE;
		else if (keycode == LESS)
			((t_plane *)(global->nearest_obj))->point.z -= STEP_TRANSLATE;
	}	
}

static void	rotate_plane(int keycode, t_global *global)
{
	if (global->prev_keyhook == X_KEYHOOK)
	{
		if (keycode == UP)
			((t_plane *)(global->nearest_obj))->orientation.x += STEP_ROTATE;
		else if (keycode == DOWN)
			((t_plane *)(global->nearest_obj))->orientation.x -= STEP_ROTATE;
	}
	else if (global->prev_keyhook == Y_KEYHOOK)
	{
		if (keycode == UP)
			((t_plane *)(global->nearest_obj))->orientation.y += STEP_ROTATE;
		else if (keycode == DOWN)
			((t_plane *)(global->nearest_obj))->orientation.y -= STEP_ROTATE;
	}
	else if (global->prev_keyhook == Z_KEYHOOK)
	{
		if (keycode == UP)
			((t_plane *)(global->nearest_obj))->orientation.z += STEP_ROTATE;
		else if (keycode == DOWN)
			((t_plane *)(global->nearest_obj))->orientation.z -= STEP_ROTATE;
	}	
	normalizing_vector(&((t_plane *)(global->nearest_obj))->orientation,
		&((t_plane *)(global->nearest_obj))->orientation);
}
