/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:59:15 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/22 17:04:57 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	intersection_cylinder_pipe(t_cylinder	*cylinder,
					t_coord *d, t_coord *oc);
static float	nearest_distance(float	*points);
static void		define_cylinder_plane(t_cylinder *cyl, t_plane *plane);

float	check_intersection_cylinder(t_cylinder	*cylinder,
			t_ray *ray, t_coord *d_ray)
{
	float	dist_pipe;
	float	dist_plane[2];
	t_coord	oc;
	t_coord	d;

	vector_subtraction(&oc, &(ray->point[0]), &(cylinder->point));
	scalar_multiplication(&d, d_ray, -1);
	dist_pipe = intersection_cylinder_pipe(cylinder, &d, &oc);
	define_cylinder_plane(cylinder, &cylinder->plane_begin);
	dist_plane[0] = intersection_cylinder_plane(cylinder,
			&cylinder->plane_begin, ray, d_ray);
	return (dist_pipe);
}

static float	intersection_cylinder_plane(t_cylinder	*cylinder,
			t_plane *plane, t_ray *ray, t_coord *d_ray)
{
	float	dist_plane;
	t_coord	ray;

	dist_plane = check_intersection_plane(plane, ray, d_ray);
	if (dist_plane == 0)
		return (-1);
	return (dist_plane);
}

static float	intersection_cylinder_pipe(t_cylinder	*cyl,
					t_coord *d, t_coord *oc)
{
	float	points[2];
	float	dot_dv;
	float	dot_ocv;
	float	m;
	t_coord	coef;

	dot_dv = scalar_product_2_vectors(d, &(cyl->orientation));
	dot_ocv = scalar_product_2_vectors(oc, &(cyl->orientation));
	coef.x = 1 - dot_dv * dot_dv;
	coef.y = 2.0f * (scalar_product_2_vectors(d, oc)
			- dot_dv * scalar_product_2_vectors(oc, &(cyl->orientation)));
	coef.z = scalar_product_2_vectors(oc, oc) - dot_ocv * dot_ocv
		- (cyl->diameter / 2) * (cyl->diameter / 2);
	if (!solve_quadratic_equation(coef.x, coef.y, coef.z, points))
		return (-1);
	points[0] = nearest_distance(points);
	if (points[0] == -1)
		return (-1);
	m = dot_dv * points[0] + dot_ocv;
	if (m < 0 || m > cyl->height)
		return (-1);
	return (points[0]);
}

static float	nearest_distance(float	*points)
{
	if (points[0] < 0 && points[1] < 0)
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

static void	define_cylinder_plane(t_cylinder *cyl, t_plane *plane)
{
	plane->point = cyl->point;
	plane->orientation = cyl->orientation;
	plane->color = cyl->color;
	plane->color_ambient = cyl->color_ambient;
}
