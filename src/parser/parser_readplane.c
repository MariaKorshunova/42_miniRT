/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readplane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:29:05 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/24 15:26:38 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parser.h"

void	parser_check_isnotnormailzed(t_parser *p, t_coord vect)
{
	float	vec_length;

	if (abs ((int) vect.x) > 1 || abs ((int) vect.y) > 1
		|| abs ((int) vect.z) > 1)
		parser_error(1, p);
	vec_length = vector_length (&vect);
	if (vec_length < 0.98 || vec_length > 1.02)
		parser_error(1, p);
}

static t_plane	*parser_addplane(t_parser *p)
{
	t_plane	*plane;

	if (!p->scene->obj->planes)
	{
		p->scene->obj->planes = (t_plane *) malloc (sizeof(t_plane));
		if (!(p->scene->obj->planes))
			parser_error (12, p);
		p->scene->obj->planes->next = 0;
		return (p->scene->obj->planes);
	}
	plane = p->scene->obj->planes;
	while (plane && plane->next)
		plane = plane->next;
	plane->next = (t_plane *) malloc (sizeof(t_plane));
	if (!(plane->next))
		parser_error (12, p);
	plane->next->next = 0;
	return (plane->next);
}

void	parser_readplane(t_parser *p)
{
	t_plane	*plane;

	plane = parser_addplane(p);
	(p->i) += 2;
	parser_skipspacesifnotspaceerror(p);
	plane->point = parser_readcoord (p);
	parser_skipspacesifnotspaceerror(p);
	plane->orientation = parser_readcoord(p);
	parser_check_isnotnormailzed(p, plane->orientation);
	normalizing_vector(&plane->orientation, &plane->orientation);
	parser_skipspacesifnotspaceerror(p);
	if (!ft_isdigit(p->s[p->i]))
		parser_error(1, p);
	plane->color = parser_readcolor(p);
	parser_skipspaces(p->s, &(p->i));
	if (p->s[p->i])
		parser_error(1, p);
}
