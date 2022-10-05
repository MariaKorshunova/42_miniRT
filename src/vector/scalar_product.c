/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:26:09 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/05 15:46:02 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/* Возвращает результат скалярного умножения двух векторов */
float	scalar_product_2_vectors(t_coord *a, t_coord *b)
{
	float	result;

	result = a->x * b->x + a->y * b->y + a->z * b->z;
	return (result);
}

/* Возвращает угол между двумя векторами */
float	angle_between_2_vectors(t_coord *a, t_coord *b)
{
	float	angle;

	angle = scalar_product_2_vectors(a, b)
		/ (vector_length(a) * vector_length(b));
	return (angle);
}
