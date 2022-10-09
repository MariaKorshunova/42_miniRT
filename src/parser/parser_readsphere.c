/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readsphere.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:20:46 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/09 18:50:01 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parser.h"

static t_sphere	*parser_addsphere(t_parser *p)
{
	t_sphere	*sphere;

	if (!p->scene->obj->spheres)
	{
		p->scene->obj->spheres = (t_sphere *) malloc (sizeof(t_sphere));
		if (!(p->scene->obj->spheres))
			parser_error (12, p);
		p->scene->obj->spheres->next = 0;
		return (p->scene->obj->spheres);
	}
	sphere = p->scene->obj->spheres;
	while (sphere && sphere->next)
		sphere = sphere->next;
	sphere->next = (t_sphere *) malloc (sizeof(t_sphere));
	if (!(sphere->next))
		parser_error (12, p);
	sphere->next->next = 0;
	return (sphere->next);
}

void	parser_readsphere(t_parser *p)
{
	t_sphere	*sphere;

	sphere = parser_addsphere(p);
	(p->i) += 2;
	parser_skipspacesifnotspaceerror(p);
	sphere->point = parser_readcoord(p);
	parser_skipspacesifnotspaceerror(p);
	sphere->diameter = parser_readfloat(p);
	parser_skipspacesifnotspaceerror(p);
	if (!ft_isdigit(p->s[p->i]))
		parser_error(1, p);
	sphere->color = parser_readcolor(p);
	parser_skipspaces(p->s, &(p->i));
	if (p->s[p->i])
		parser_error(1, p);
}
