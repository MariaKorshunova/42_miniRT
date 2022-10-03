/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_linear_operations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:48:44 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/03 19:09:49 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	scalar_multiplication(t_coord *vector, float lambda)
{
	vector->x = vector->x * lambda;
	vector->y = vector->y * lambda;
	vector->z = vector->z * lambda;
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
