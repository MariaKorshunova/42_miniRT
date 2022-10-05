/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readscene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:14:54 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/05 07:30:48 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	parser_readambient(t_scene *scene, char *s, int *i, int *readelem)
{
	if ((*readelem) & 1)
		parser_error(scene, 1);
	*readelem |= 1;
	(*i)++;
	parser_skipspaces(s, i);
	scene->ambient_light_intensity = parser_readfloat(scene, s, i);
	parser_skipspaces(s, i);
	if (scene->ambient_light_intensity > 1
		|| scene->ambient_light_intensity < 0 || !ft_isdigit(s[*i]))
		parser_error(scene, 1);
	scene->ambient_light_rgb = parser_readcolor(scene, s, i);
	parser_skipspaces(s, i);
	if (s[*i])
		parser_error(scene, 1);
}

void	parser_readcamera(t_scene *scene, char *s, int *i, int *readelem)
{
	if ((*readelem) & 2)
		parser_error(scene, 1);
	*readelem |= 2;
	(*i)++;
	parser_skipspaces(s, i);
	scene->camera_point = parser_readcoord(scene, s, i);
	parser_skipspaces(s, i);
	scene->camera_orientation = parser_readcoord(scene, s, i);
	parser_skipspaces(s, i);
	scene->camera_fov = parser_readfloat(scene, s, i);
	parser_skipspaces(s, i);
	if (s[*i])
		parser_error(scene, 1);
}

static t_light	*parser_addlight(t_scene *scene)
{
	t_light	*light;

	if (!scene->obj->lights)
	{
		scene->obj->lights = (t_light *) malloc (sizeof(t_light));
		if (!(scene->obj->lights))
			exit (12);
		scene->obj->lights->next = 0;
		return (scene->obj->lights);
	}
	light = scene->obj->lights;
	while (!light && !light->next)
		light = light->next;
	light->next = (t_light *) malloc (sizeof(t_light));
	if (!(light->next))
		exit (12);
	light->next->next = 0;
	return (light->next);
}

void	parser_readlight(t_scene *scene, char *s, int *i, int *readelem)
{
	t_light	*light;

	if ((*readelem) & 4)
		parser_error(scene, 1);
	*readelem |= 4;
	light = parser_addlight(scene);
	(*i)++;
	parser_skipspaces(s, i);
	light->point = parser_readcoord(scene, s, i);
	parser_skipspaces(s, i);
	light->lighting_ratio = parser_readfloat(scene, s, i);
	parser_skipspaces(s, i);
	if (!s[*i])
		return ;
	if (!ft_isdigit(s[*i]))
		parser_error(scene, 1);
	light->color = parser_readcolor(scene, s, i);
	parser_skipspaces(s, i);
	if (s[*i])
		parser_error(scene, 1);
}
