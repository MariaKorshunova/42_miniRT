/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readcylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:48:25 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/26 13:46:21 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parser.h"

t_scene	*parser_createscene(t_parser *p)
{
	t_scene	*scene;

	scene = (t_scene *) malloc (sizeof(t_scene));
	if (!scene)
		parser_error (12, 0);
	scene->obj = (t_objects *) malloc (sizeof(t_objects));
	if (!(scene->obj))
		parser_error (12, p);
	new_vector(&scene->camera_point, 0, 0, 0);
	new_vector(&scene->camera_orientation, 0, 0, 1);
	scene->camera_fov = 90;
	scene->ambient_light_intensity = 1;
	scene->ambient_light_rgb = 0xffffff;
	scene->obj->cylinders = 0;
	scene->obj->lights = 0;
	scene->obj->planes = 0;
	scene->obj->spheres = 0;
	return (scene);
}

static t_cylinder	*parser_addcylinder(t_parser *p)
{
	t_cylinder	*cylinder;

	if (!p->scene->obj->cylinders)
	{
		p->scene->obj->cylinders = (t_cylinder *) malloc (sizeof(t_cylinder));
		if (!(p->scene->obj->cylinders))
			parser_error (12, p);
		p->scene->obj->cylinders->next = 0;
		return (p->scene->obj->cylinders);
	}
	cylinder = p->scene->obj->cylinders;
	while (cylinder && cylinder->next)
		cylinder = cylinder->next;
	cylinder->next = (t_cylinder *) malloc (sizeof(t_cylinder));
	if (!(cylinder->next))
		parser_error (12, p);
	cylinder->next->next = 0;
	return (cylinder->next);
}

void	parser_readcylinder(t_parser *p)
{
	t_cylinder	*cylinder;

	cylinder = parser_addcylinder(p);
	(p->i) += 2;
	parser_skipspacesifnotspaceerror(p);
	cylinder->point = parser_readcoord(p);
	parser_skipspacesifnotspaceerror(p);
	cylinder->orientation = parser_readcoord(p);
	parser_check_isnotnormailzed(p, cylinder->orientation);
	normalizing_vector(&cylinder->orientation, &cylinder->orientation);
	parser_skipspacesifnotspaceerror(p);
	cylinder->diameter = parser_readfloat(p);
	parser_skipspacesifnotspaceerror(p);
	cylinder->height = parser_readfloat(p);
	parser_skipspacesifnotspaceerror(p);
	if (!ft_isdigit(p->s[p->i]))
		parser_error(1, p);
	cylinder->color = parser_readcolor(p);
	parser_skipspaces(p->s, &(p->i));
	if (p->s[p->i])
		parser_error(1, p);
}
