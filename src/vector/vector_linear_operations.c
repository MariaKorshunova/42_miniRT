/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_linear_operations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:48:44 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/03 17:14:11 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	scalar_multiplication(t_coord *vector, float lambda)
{
	vector->x = vector->x * lambda;
	vector->y = vector->y * lambda;
	vector->z = vector->z * lambda;
}
