/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_and_rotate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:22:41 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/24 19:48:56 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	fill_rotation_matrix(float rotation_matrix[3][3], t_coord *coord)
{
	t_coord	r_cos;
	t_coord	r_sin;

	r_cos = *coord;
	r_sin.x = sin(acos(r_cos.x));
	r_sin.y = sin(acos(r_cos.y));
	r_sin.z = sin(acos(r_cos.z));
	rotation_matrix[0][0] = r_cos.x * r_cos.z - r_cos.y * r_sin.x * r_sin.z;
	rotation_matrix[0][1] = -r_cos.z * r_sin.x - r_cos.x * r_cos.y * r_sin.z;
	rotation_matrix[0][2] = r_sin.y * r_sin.z;
	rotation_matrix[1][0] = r_cos.y * r_cos.z * r_sin.x + r_cos.x * r_sin.z;
	rotation_matrix[1][1] = r_cos.x * r_cos.y * r_cos.z - r_sin.x * r_sin.z;
	rotation_matrix[1][2] = -r_cos.z * r_sin.y;
	rotation_matrix[2][0] = r_sin.x * r_sin.y;
	rotation_matrix[2][1] = r_cos.x * r_sin.y;
	rotation_matrix[2][2] = r_cos.y;
}

static void	rotate_vector_with_mtx(t_coord *res,
	t_coord *vec, float rotation_mtx[3][3])
{
	t_coord	vec_copy;

	if (!res || !vec || !rotation_mtx)
		return ;
	vec_copy = *vec;
	res->x = vec_copy.x * rotation_mtx[0][0] + vec_copy.y * rotation_mtx[0][1]
		+ vec_copy.z * rotation_mtx[0][2];
	res->y = vec_copy.x * rotation_mtx[1][0] + vec_copy.y * rotation_mtx[1][1]
		+ vec_copy.z * rotation_mtx[1][2];
	res->z = vec_copy.x * rotation_mtx[2][0] + vec_copy.y * rotation_mtx[2][1]
		+ vec_copy.z * rotation_mtx[2][2];
}

void	rotate_objects(t_scene *scene, t_coord *coord)
{
	t_objects	obj;
	float		rotation_matrix[3][3];

	fill_rotation_matrix(rotation_matrix, coord);
	obj = *scene->obj;
	while (obj.spheres)
	{
		rotate_vector_with_mtx(&obj.spheres->point,
			&obj.spheres->point, rotation_matrix);
		obj.spheres = obj.spheres->next;
	}
	while (obj.planes)
	{
		rotate_vector_with_mtx(&obj.planes->point,
			&obj.planes->point, rotation_matrix);
		rotate_vector_with_mtx(&obj.planes->orientation,
			&obj.planes->orientation, rotation_matrix);
		normalizing_vector(&obj.planes->orientation,
			&obj.planes->orientation);
		obj.planes = obj.planes->next;
	}
	while (obj.cylinders)
	{
		rotate_vector_with_mtx(&obj.cylinders->point,
			&obj.cylinders->point, rotation_matrix);
		rotate_vector_with_mtx(&obj.cylinders->orientation,
			&obj.cylinders->orientation, rotation_matrix);
		normalizing_vector(&obj.cylinders->orientation,
			&obj.cylinders->orientation);
		obj.cylinders = obj.cylinders->next;
	}
	while (obj.lights)
	{
		rotate_vector_with_mtx(&obj.lights->point,
			&obj.lights->point, rotation_matrix);
		obj.lights = obj.lights->next;
	}
}

void	translate_objects(t_scene *scene, t_coord *coord)
{
	t_objects	obj;

	obj = *scene->obj;
	while (obj.spheres)
	{
		vector_addition(&obj.spheres->point, &obj.spheres->point, coord);
		obj.spheres = obj.spheres->next;
	}
	while (obj.planes)
	{
		vector_addition(&obj.planes->point, &obj.planes->point, coord);
		obj.planes = obj.planes->next;
	}
	while (obj.cylinders)
	{
		vector_addition(&obj.cylinders->point, &obj.cylinders->point, coord);
		obj.cylinders = obj.cylinders->next;
	}
	while (obj.lights)
	{
		vector_addition(&obj.lights->point, &obj.lights->point, coord);
		obj.lights = obj.lights->next;
	}
}
