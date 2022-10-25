/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traslate_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:42:28 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/25 21:15:08 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	translate_objects_keyhook(int keycode, t_global *global)
{
	printf("Translate! %d\n", global->nearest_type);
	if (global->nearest_type == SPHERE)
	{
		printf("SPHERE");
		if (global->prev_keyhook == 7)
		{
			printf("Translate x GREATER\n");
			if (keycode == GREATER)
			{
				printf("Translate sphere\n");
				((t_sphere *)(global->nearest_obj))->point.x += 1;
				raytracer(global);
			}
			else if (keycode == LESS)
			{
				printf("Translate x LESS\n");
				((t_sphere *)(global->nearest_obj))->point.x -= 1;
				raytracer(global);
			}
		}
	}
}

/*
	if (keycode == Y_KEYHOOK)
	{
		if (global->prev_keyhook == GREATER)
			((t_sphere *)(global->nearest_obj))->point.y += 0.1;
		else if (global->prev_keyhook == LESS)
			((t_sphere *)(global->nearest_obj))->point.y -= 0.1;
	}
	if (keycode == Z_KEYHOOK)
	{
		if (global->prev_keyhook == GREATER)
			((t_sphere *)(global->nearest_obj))->point.z += 0.1;
		else if (global->prev_keyhook == LESS)
			((t_sphere *)(global->nearest_obj))->point.z -= 0.1;
	}
*/