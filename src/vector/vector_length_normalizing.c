/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_length_normalizing.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:04:26 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/21 16:21:34 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/* return length of vector */
float	vector_length(t_coord *vector)
{
	float	length;

	if (!vector)
		return (0);
	length = sqrtf(vector->x * vector->x
			+ vector->y * vector->y + vector->z * vector->z);
	return (length);
}

/* return length of vector by two points*/
float	vector_length_by_two_points(t_coord *a, t_coord *b)
{
	float	length;

	length = sqrtf((b->x - a->x) * (b->x - a->x)
			+ (b->y - a->y) * (b->y - a->y) + (b->z - a->z) * (b->z - a->z));
	return (length);
}

/* record in result normilize vector */
void	normalizing_vector(t_coord *result, t_coord *vector)
{
	float	length;

	length = vector_length(vector);
	scalar_multiplication(result, result, 1 / length);
}
