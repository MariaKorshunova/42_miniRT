/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traslate_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:42:28 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/25 21:53:33 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	translate_sphere(int keycode, t_global *global);
static void	translate_cylinder(int keycode, t_global *global);
static void	translate_plane(int keycode, t_global *global);

void	translate_objects_keyhook(int keycode, t_global *global)
{
	if (global->nearest_type == SPHERE)
		translate_sphere(keycode, global);
	else if (global->nearest_type == CYLINDER)
		translate_cylinder(keycode, global);
	else if (global->nearest_type == PLANE)
		translate_plane(keycode, global);
	raytracer(global);
}

static void	translate_sphere(int keycode, t_global *global)
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

static void	translate_cylinder(int keycode, t_global *global)
{
	if (global->prev_keyhook == X_KEYHOOK)
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

static void	translate_plane(int keycode, t_global *global)
{
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
