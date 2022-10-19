/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 13:22:39 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/19 18:13:29 by bpoetess         ###   ########.fr       */
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
	vector_subtraction(&sub_ra, &(ray->point[0]), &(plane->point));
	t = scalar_product_2_vectors(&sub_ra, &(plane->orientation)) / dot_dn;
	if (t < 0)
		return (-1);
	return (t);
}

float	check_intersection_sphere(t_sphere *sphere, t_ray *ray, t_coord *d)
{
	float	points[2];
	t_coord	oc;

	vector_subtraction(&oc, &sphere->point, &(ray->point[0]));
	if (!solve_quadratic_equation(
			scalar_product_2_vectors(d, d),
			2 * scalar_product_2_vectors(d, &oc),
			scalar_product_2_vectors(&oc, &oc)
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

float	check_intersection_cylinder(t_cylinder	*cylinder,
			t_ray *ray, t_coord *d)
{
	float	points[2];
	float	dot_dv;
	float	dot_ocv;
	t_coord	oc;
	t_coord	coef;

	vector_subtraction(&oc, &(ray->point[0]), &(cylinder->point));
	dot_dv = scalar_product_2_vectors(d, &(cylinder->orientation));
	dot_ocv = scalar_product_2_vectors(&oc, &(cylinder->orientation));
	coef.x = scalar_product_2_vectors(d, d) - dot_dv * dot_dv;
	coef.y = -2 * (scalar_product_2_vectors(d, &oc)
			- dot_dv * scalar_product_2_vectors(&oc, &(cylinder->orientation)));
	coef.z = scalar_product_2_vectors(&oc, &oc) - dot_ocv * dot_ocv
		- (cylinder->diameter / 2) * (cylinder->diameter / 2);
	if (!solve_quadratic_equation(coef.x, coef.y, coef.z, points)
		|| (points[0] < 0 && points[1] < 0))
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
