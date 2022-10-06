/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readsphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:20:46 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/06 20:10:29 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parser.h"

static t_sphere	*parser_addsphere(t_scene *scene)
{
	t_sphere	*sphere;

	if (!scene->obj->spheres)
	{
		scene->obj->spheres = (t_sphere *) malloc (sizeof(t_sphere));
		if (!(scene->obj->spheres))
			parser_error (scene, 12);
		scene->obj->spheres->next = 0;
		return (scene->obj->spheres);
	}
	sphere = scene->obj->spheres;
	while (!sphere && !sphere->next)
		sphere = sphere->next;
	sphere->next = (t_sphere *) malloc (sizeof(t_sphere));
	if (!(sphere->next))
		parser_error (scene, 12);
	sphere->next->next = 0;
	return (sphere->next);
}

void	parser_readsphere(t_scene *scene, char *s, int *i)
{
	t_sphere	*sphere;

	sphere = parser_addsphere(scene);
	(*i) += 2;
	parser_skipspaces(s, i);
	sphere->point = parser_readcoord(scene, s, i);
	parser_skipspaces(s, i);
	sphere->diameter = parser_readfloat(scene, s, i);
	parser_skipspaces(s, i);
	if (!ft_isdigit(s[*i]))
		parser_error(scene, 1);
	sphere->color = parser_readcolor(scene, s, i);
	parser_skipspaces(s, i);
	if (s[*i])
		parser_error(scene, 1);
}
