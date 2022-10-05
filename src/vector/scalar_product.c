/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:26:09 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/05 14:35:26 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/* Возвращает  */
float	scalar_product_2_vectors(t_coord *a, t_coord *b)
{
	float	result;

	result = a->x * b->x + a->y * b->y + a->z * b->z;
	return (result);
}
