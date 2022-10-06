/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readcylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:48:25 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/06 20:10:37 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parser.h"

static t_cylinder	*parser_addcylinder(t_scene *scene)
{
	t_cylinder	*cylinder;

	if (!scene->obj->cylinders)
	{
		scene->obj->cylinders = (t_cylinder *) malloc (sizeof(t_cylinder));
		if (!(scene->obj->cylinders))
			parser_error (scene, 12);
		scene->obj->cylinders->next = 0;
		return (scene->obj->cylinders);
	}
	cylinder = scene->obj->cylinders;
	while (!cylinder && !cylinder->next)
		cylinder = cylinder->next;
	cylinder->next = (t_cylinder *) malloc (sizeof(t_cylinder));
	if (!(cylinder->next))
		parser_error (scene, 12);
	cylinder->next->next = 0;
	return (cylinder->next);
}

void	parser_readcylinder(t_scene *scene, char *s, int *i)
{
	t_cylinder	*cylinder;

	cylinder = parser_addcylinder(scene);
	(*i) += 2;
	parser_skipspaces(s, i);
	cylinder->point = parser_readcoord(scene, s, i);
	parser_skipspaces(s, i);
	cylinder->orientation = parser_readcoord(scene, s, i);
	parser_check_isnotnormailzed(scene, cylinder->orientation);
	parser_skipspaces(s, i);
	cylinder->diameter = parser_readfloat(scene, s, i);
	parser_skipspaces(s, i);
	cylinder->height = parser_readfloat(scene, s, i);
	parser_skipspaces(s, i);
	if (!ft_isdigit(s[*i]))
		parser_error(scene, 1);
	cylinder->color = parser_readcolor(scene, s, i);
	parser_skipspaces(s, i);
	if (s[*i])
		parser_error(scene, 1);
}
