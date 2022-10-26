/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:26:09 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/26 14:35:51 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/* Возвращает результат скалярного умножения двух векторов */
float	scalar_product_2_vectors(t_coord *a, t_coord *b)
{
	float	result;

	result = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
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
