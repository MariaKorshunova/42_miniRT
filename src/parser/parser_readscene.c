/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readscene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:14:54 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/26 20:04:12 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parser.h"

void	parser_readambient(t_parser *p)
{
	if ((p->readelem) & 1)
		parser_error(1, p);
	p->readelem |= 1;
	(p->i)++;
	parser_skipspacesifnotspaceerror(p);
	p->scene->ambient_light_intensity = parser_readfloat(p);
	parser_skipspacesifnotspaceerror(p);
	if (p->scene->ambient_light_intensity > 1
		|| p->scene->ambient_light_intensity < 0 || !ft_isdigit(p->s[p->i]))
		parser_error(1, p);
	p->scene->ambient_light_rgb = parser_readcolor(p);
	parser_skipspaces(p->s, &(p->i));
	if (p->s[p->i])
		parser_error(1, p);
}

void	parser_readcamera(t_parser *p)
{
	if ((p->readelem) & 2)
		parser_error(1, p);
	p->readelem |= 2;
	(p->i)++;
	parser_skipspacesifnotspaceerror(p);
	p->scene->camera_point = parser_readcoord(p);
	parser_skipspacesifnotspaceerror(p);
	p->scene->camera_orientation = parser_readcoord(p);
	parser_check_isnotnormailzed(p, p->scene->camera_orientation);
	normalizing_vector(&p->scene->camera_orientation,
		&p->scene->camera_orientation);
	parser_skipspacesifnotspaceerror(p);
	p->scene->camera_fov = parser_readfloat(p);
	parser_skipspaces(p->s, &(p->i));
	if (p->s[p->i] || p->scene->camera_fov > 180 || p->scene->camera_fov < 0)
		parser_error(1, p);
}

static t_light	*parser_addlight(t_parser *p)
{
	t_light	*light;

	if (!p->scene->obj->lights)
	{
		p->scene->obj->lights = (t_light *) malloc (sizeof(t_light));
		if (!(p->scene->obj->lights))
			parser_error (12, p);
		p->scene->obj->lights->next = 0;
		return (p->scene->obj->lights);
	}
	light = p->scene->obj->lights;
	while (!light && !light->next)
		light = light->next;
	light->next = (t_light *) malloc (sizeof(t_light));
	if (!(light->next))
		parser_error (12, p);
	light->next->next = 0;
	return (light->next);
}

void	parser_readlight(t_parser *p)
{
	t_light	*light;

	if ((p->readelem) & 4)
		parser_error(1, p);
	p->readelem |= 4;
	light = parser_addlight(p);
	(p->i)++;
	parser_skipspacesifnotspaceerror(p);
	light->point = parser_readcoord (p);
	parser_skipspacesifnotspaceerror(p);
	light->lighting_ratio = parser_readfloat(p);
	parser_skipspacesifnotspaceerror(p);
	if (light->lighting_ratio > 1 || light->lighting_ratio < 0)
		parser_error(1, p);
	if (!p->s[p->i])
		return ;
	if (!ft_isdigit(p->s[p->i]))
		parser_error(1, p);
	light->color = parser_readcolor(p);
	parser_skipspaces(p->s, &(p->i));
	if (p->s[p->i])
		parser_error(1, p);
}

void	get_fov_angles(t_scene *scene)
{
	scene->camera_angles[0] = tan(scene->camera_fov * M_PI / 360);
	scene->camera_angles[1] = (scene->camera_angles[0]
			* (((float) HEIGHT) / ((float) WIDTH)));
}
