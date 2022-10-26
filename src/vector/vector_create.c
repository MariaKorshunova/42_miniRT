/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:19:51 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/26 17:23:39 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	vector_multiplication(t_coord *res, t_coord *vec1, t_coord *vec2)
{
	t_coord	res2;

	if (!res || !vec1 || !vec2)
		return ;
	res2.x = vec1->y * vec2->z - vec1->z * vec2->y;
	res2.y = vec1->x * vec2->z - vec1->z * vec2->x;
	res2.z = vec1->x * vec2->y - vec1->y * vec2->x;
	*res = res2;
}

/* 	fill value x, y, z in vector */
void	new_vector(t_coord *result, float x, float y, float z)
{
	if (result == NULL)
		return ;
	result->x = x;
	result->y = y;
	result->z = z;
}

/* 	fill value x, y, z in vector  by two points */
void	new_vector_by_two_points(t_coord *result, t_coord *a, t_coord *b)
{
	if (result == NULL || a == NULL || b == NULL)
		return ;
	result->x = b->x - a->x;
	result->y = b->y - a->y;
	result->z = b->z - a->z;
}
