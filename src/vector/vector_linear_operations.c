/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_linear_operations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:48:44 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/21 16:18:45 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	scalar_multiplication(t_coord *result, t_coord *vector, float lambda)
{
	result->x = vector->x * lambda;
	result->y = vector->y * lambda;
	result->z = vector->z * lambda;
}

void	vector_addition(t_coord *result, t_coord *a, t_coord *b)
{
	if (result == NULL || a == NULL || b == NULL)
		return ;
	result->x = a->x + b->x;
	result->y = a->y + b->y;
	result->z = a->z + b->z;
}

void	vector_subtraction(t_coord *result, t_coord *a, t_coord *b)
{
	if (result == NULL || a == NULL || b == NULL)
		return ;
	result->x = a->x - b->x;
	result->y = a->y - b->y;
	result->z = a->z - b->z;
}
