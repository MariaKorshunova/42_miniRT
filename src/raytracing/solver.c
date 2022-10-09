/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:38:00 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/09 17:42:47 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	solve_quadratic_equation(float a, float b, float c, float roots[2])
{
	float	d_sqare;

	d_sqare = b * b - 4 * a * c;
	if (d_sqare < 0)
	{
		roots[0] = INFINITY;
		roots[1] = INFINITY;
		return (0);
	}
	if (d_sqare == 0)
	{
		roots[0] = (-b - sqrt(d_sqare)) / (2 * a);
		roots[1] = roots[0];
		return (1);
	}
	roots[0] = (-b - sqrt(d_sqare)) / (2 * a);
	roots[1] = (-b + sqrt(d_sqare)) / (2 * a);
	return (2);
}
