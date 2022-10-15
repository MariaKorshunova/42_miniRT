/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 13:22:39 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/15 14:43:51 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*  ray.point[0] = global->scene->camera_point; Точка камеры (точка a)
    = координата луча на проецирумой плоскости
    Vector d = ray.point[0] -  ray.point[1] (вектор луча)
*/

/*  Формула пересечения t=\frac{((r - a), n)}{(d,n)}}
    r = plane->point (точка на плоскости)
    n = plane->orientation (вектор нормали к плоскости)
*/
float	check_intersection_plane(t_plane *plane, t_ray *ray, t_coord *d)
{
	float	t;
	float	dot_dn;
	t_coord	sub_ra;

	dot_dn = scalar_product_2_vectors(d, &(plane->orientation));
	if (dot_dn == 0)
		return (-1);
	vector_subtraction(&sub_ra, &(plane->point), &(ray->point[0]));
	t = scalar_product_2_vectors(&sub_ra, &(plane->orientation)) / dot_dn;
	if (t < 0)
		return (-1);
	return (t);
}

float	check_intersection_sphere(t_sphere *sphere, t_ray *ray)
{
	float	points[2];
	t_coord	d;
	t_coord	oc;

	vector_subtraction(&d, &ray->point[0], &(ray->point[1]));
	vector_subtraction(&oc, &sphere->point, &(ray->point[0]));
	if (!solve_quadratic_equation(
			scalar_product_2_vectors(&(d), &(d)),
			2 * scalar_product_2_vectors(&(d), &(oc)),
			scalar_product_2_vectors(&(oc), &(oc))
			- ((sphere->diameter / 2) * (sphere->diameter / 2)),
			points) || (points[0] < 0 && points[1] < 0))
		return (-1);
	if (points[0] < 0)
		points[0] = points[1];
	else if (points[1] < 0)
		points[1] = points[0];
	if (points[0] <= points[1] && points[0] > 0)
		return (points[0]);
	if (points[1] <= points[0] && points[1] > 0)
		return (points[1]);
	return (-1);
}
