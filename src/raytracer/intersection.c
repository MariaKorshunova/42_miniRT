/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 13:22:39 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/19 22:49:11 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	intersection_cylinder_pipe(t_cylinder	*cylinder,
					t_coord *d, t_coord *oc);
static int		check_cylinder_height(float *dot_dv, float	*dot_ocv,
					float *t, float *height);

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
	float	dist;
	t_coord	oc;

	vector_subtraction(&oc, &(ray->point[0]), &(cylinder->point));
	// vector_subtraction(d, &(ray->point[1]), &(ray->point[0]));
	// vector_subtraction(&oc,&(cylinder->point), &(ray->point[0]));
	dist = intersection_cylinder_pipe(cylinder, d, &oc);
	return (dist);
}

static float	intersection_cylinder_pipe(t_cylinder	*cyl,
					t_coord *d, t_coord *oc)
{
	float	points[2];
	float	dot_dv;
	float	dot_ocv;
	t_coord	coef;

	normalizing_vector(d, d);
	dot_dv = scalar_product_2_vectors(d, &(cyl->orientation));
	dot_ocv = scalar_product_2_vectors(oc, &(cyl->orientation));
	coef.x = scalar_product_2_vectors(d, d) - dot_dv * dot_dv;
	coef.y = -2.0f * (scalar_product_2_vectors(d, oc)
			- dot_dv * scalar_product_2_vectors(oc, &(cyl->orientation)));
	coef.z = scalar_product_2_vectors(oc, oc) - dot_ocv * dot_ocv
		- (cyl->diameter / 2) * (cyl->diameter / 2);
	if (!solve_quadratic_equation(coef.x, coef.y, coef.z, points)
		|| (points[0] < 0 && points[1] < 0)
		|| check_cylinder_height(&dot_dv, &dot_ocv, &points[1], &cyl->height))
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

static int	check_cylinder_height(float *dot_dv, float	*dot_ocv, float *t,
				float *height)
{
	float	m;

	m = - (*dot_dv) * (*t) + (*dot_ocv);
	if (m < 0 || m > *height)
		return (1);
	return (0);
}
