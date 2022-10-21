/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readcylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:48:25 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/20 16:29:02 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parser.h"

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
