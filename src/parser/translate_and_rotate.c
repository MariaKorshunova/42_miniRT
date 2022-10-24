/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_and_rotate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:22:41 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/24 15:30:15 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	translate_objects(t_scene *scene, t_coord *coord)
{
	t_objects	obj;

	obj = *scene->obj;
	while (obj.spheres)
	{
		vector_addition(&obj.spheres->point, &obj.spheres->point, coord);
		obj.spheres = obj.spheres->next;
	}
	while (obj.planes)
	{
		vector_addition(&obj.planes->point, &obj.planes->point, coord);
		obj.planes = obj.planes->next;
	}
	while (obj.cylinders)
	{
		vector_addition(&obj.cylinders->point, &obj.cylinders->point, coord);
		obj.cylinders = obj.cylinders->next;
	}
	while (obj.lights)
	{
		vector_addition(&obj.lights->point, &obj.lights->point, coord);
		obj.lights = obj.lights->next;
	}
}
