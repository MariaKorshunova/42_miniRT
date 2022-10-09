/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readplane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:29:05 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/09 17:39:12 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parser.h"

void	parser_check_isnotnormailzed(t_scene *scene, t_coord vect)
{
	float	vec_length;

	if (abs ((int) vect.x) > 1 || abs ((int) vect.y) > 1
		|| abs ((int) vect.z) > 1)
		parser_error(scene, 1);
	vec_length = vector_length (&vect);
	if (vec_length < 0.98 || vec_length > 1.02)
		parser_error(scene, 1);
}

static t_plane	*parser_addplane(t_scene *scene)
{
	t_plane	*plane;

	if (!scene->obj->planes)
	{
		scene->obj->planes = (t_plane *) malloc (sizeof(t_plane));
		if (!(scene->obj->planes))
			parser_error (scene, 12);
		scene->obj->planes->next = 0;
		return (scene->obj->planes);
	}
	plane = scene->obj->planes;
	while (plane && plane->next)
		plane = plane->next;
	plane->next = (t_plane *) malloc (sizeof(t_plane));
	if (!(plane->next))
		parser_error (scene, 12);
	plane->next->next = 0;
	return (plane->next);
}

void	parser_readplane(t_scene *scene, char *s, int *i)
{
	t_plane	*plane;

	plane = parser_addplane(scene);
	(*i) += 2;
	parser_skipspacesifnotspaceerror(scene, s, i);
	plane->point = parser_readcoord(scene, s, i);
	parser_skipspacesifnotspaceerror(scene, s, i);
	plane->orientation = parser_readcoord(scene, s, i);
	parser_check_isnotnormailzed(scene, plane->orientation);
	parser_skipspacesifnotspaceerror(scene, s, i);
	if (!ft_isdigit(s[*i]))
		parser_error(scene, 1);
	plane->color = parser_readcolor(scene, s, i);
	parser_skipspaces(s, i);
	if (s[*i])
		parser_error(scene, 1);
}
