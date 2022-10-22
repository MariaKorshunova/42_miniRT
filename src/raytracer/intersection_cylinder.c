/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:59:15 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/22 21:02:01 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	intersection_cylinder_pipe(t_cylinder	*cylinder,
					t_coord *d, t_coord *oc, t_pixel *pixel);
static float	intersection_cylinder_plane(t_cylinder	*cylinder,
					t_plane *plane, t_ray *ray, t_coord *d_ray);
static void		define_cylinder_plane(t_cylinder *cyl, t_plane *plane,
					t_coord	*point);
static float	define_dist_type_intersection(t_pixel *pixel, float dist_plane,
					int type);

float	check_intersection_cylinder(t_cylinder	*cylinder, t_pixel *pixel)
{
	float	dist;
	float	dist_plane;
	t_coord	oc;
	t_coord	d;
	t_coord	point_end;

	pixel->cylinder_type = NO_INTERSECT;
	vector_subtraction(&oc, &(pixel->ray.point[0]), &(cylinder->point));
	scalar_multiplication(&d, &(pixel->d), -1);
	dist = intersection_cylinder_pipe(cylinder, &d, &oc, pixel);
	if (dist != -1)
		pixel->cylinder_type = PIPE;
	define_cylinder_plane(cylinder, &cylinder->plane_begin, &cylinder->point);
	dist_plane = intersection_cylinder_plane(cylinder,
			&cylinder->plane_begin, &(pixel->ray), &(pixel->d));
	if (dist_plane != -1 && (dist_plane < dist || dist == -1))
		dist = define_dist_type_intersection(pixel, dist_plane, PLANE_BEGIN);
	scalar_multiplication(&point_end, &cylinder->orientation, cylinder->height);
	vector_addition(&point_end, &cylinder->point, &point_end);
	define_cylinder_plane(cylinder, &cylinder->plane_end, &point_end);
	dist_plane = intersection_cylinder_plane(cylinder,
			&cylinder->plane_end, &(pixel->ray), &(pixel->d));
	if (dist_plane != -1 && (dist_plane < dist || dist == -1))
		dist = define_dist_type_intersection(pixel, dist_plane, PLANE_END);
	return (dist);
}

static float	define_dist_type_intersection(t_pixel *pixel, float dist_plane,
					int type)
{
	float	dist;

	dist = dist_plane;
	pixel->cylinder_type = type;
	return (dist);
}

static float	intersection_cylinder_pipe(t_cylinder	*cyl,
					t_coord *d, t_coord *oc, t_pixel *pixel)
{
	float	points[2];
	float	dot_dv;
	float	dot_ocv;
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
	pixel->cylinder_m = dot_dv * points[0] + dot_ocv;
	if (pixel->cylinder_m < 0 || pixel->cylinder_m > cyl->height)
		return (-1);
	return (points[0]);
}

static float	intersection_cylinder_plane(t_cylinder	*cylinder,
			t_plane *plane, t_ray *ray, t_coord *d_ray)
{
	float	dist_plane;
	t_coord	r;
	t_coord	p;
	t_coord	p_center;

	dist_plane = check_intersection_plane(plane, ray, d_ray);
	if (dist_plane == -1)
		return (-1);
	scalar_multiplication(&r, d_ray, -1 * dist_plane);
	vector_addition(&p, &(ray->point[0]), &r);
	vector_subtraction(&p_center, &p, &plane->point);
	if (vector_length(&p_center) <= cylinder->diameter / 2.0f)
		return (dist_plane);
	return (-1);
}

static void	define_cylinder_plane(t_cylinder *cyl, t_plane *plane,
				t_coord	*point)
{
	plane->point = *point;
	plane->orientation = cyl->orientation;
	plane->color = cyl->color;
	plane->color_ambient = cyl->color_ambient;
}
