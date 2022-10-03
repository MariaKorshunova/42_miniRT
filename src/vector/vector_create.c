/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:19:51 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/03 19:16:57 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

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
