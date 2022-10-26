/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:44:53 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/26 21:53:06 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

static void	set_cos_to_mtx(t_coord *r_cos, t_coord *cam)
{
	t_coord	tmp;

	if (!r_cos || !cam)
		return ;
	new_vector(&tmp, 1, 0, 0);
	r_cos->x = angle_between_2_vectors(&tmp, cam);
	new_vector(&tmp, 0, 1, 0);
	r_cos->y = angle_between_2_vectors(&tmp, cam);
	new_vector(&tmp, 0, 0, 1);
	r_cos->z = angle_between_2_vectors(&tmp, cam);
	// if (cam->x < 0)
	// 	r_cos->x *= -1;
	// if (cam->y < 0)
	// 	r_cos->y *= -1;
	// if (cam->z < 0)
	// 	r_cos->z *= -1;
}

static void	fill_rotation_matrix(float rotation_matrix[3][3], t_coord *coord)
{
	t_coord	r_cos;
	t_coord	r_sin;

	r_sin = *coord;
	new_vector(&r_cos, 0, 0, 1);
	vector_multiplication(&r_sin, &r_cos, &r_sin);
	set_cos_to_mtx(&r_cos, coord);
	r_cos.x = cos(asin(r_sin.x));
	r_cos.y = cos(asin(r_sin.y));
	r_cos.z = cos(asin(r_sin.z));
	rotation_matrix[0][0] = r_cos.y * r_cos.z;
	rotation_matrix[0][1] = -r_sin.z * r_cos.y;
	rotation_matrix[0][2] = r_sin.y;
	rotation_matrix[1][0] = r_sin.x * r_sin.y * r_cos.z + r_sin.z * r_cos.x;
	rotation_matrix[1][1] = -r_sin.x * r_sin.y * r_sin.z + r_cos.x * r_cos.z;
	rotation_matrix[1][2] = -r_sin.x * r_cos.y;
	rotation_matrix[2][0] = r_sin.x * r_sin.z - r_sin.y * r_cos.x * r_cos.z;
	rotation_matrix[2][1] = r_sin.x * r_cos.z + r_sin.y * r_sin.z * r_cos.x;
	rotation_matrix[2][2] = r_cos.x * r_cos.y;
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

static void	rotate_objects_speres_planes(t_objects *obj,
	float rotation_matrix[3][3])
{
	while (obj->spheres)
	{
		rotate_vector_with_mtx(&obj->spheres->point,
			&obj->spheres->point, rotation_matrix);
		obj->spheres = obj->spheres->next;
	}
	while (obj->planes)
	{
		rotate_vector_with_mtx(&obj->planes->point,
			&obj->planes->point, rotation_matrix);
		rotate_vector_with_mtx(&obj->planes->orientation,
			&obj->planes->orientation, rotation_matrix);
		normalizing_vector(&obj->planes->orientation,
			&obj->planes->orientation);
		obj->planes = obj->planes->next;
	}
}

void	rotate_objects(t_scene *scene, t_coord *coord)
{
	t_objects	obj;
	float		rotation_matrix[3][3];

	fill_rotation_matrix(rotation_matrix, coord);
	obj = *scene->obj;
	rotate_objects_speres_planes(&obj, rotation_matrix);
	rotate_vector_with_mtx(&scene->camera_orientation,
		&scene->camera_orientation, rotation_matrix);
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

/*	rotation_matrix[0][0] = r_cos.x * r_cos.z - r_cos.y * r_sin.x * r_sin.z;
	rotation_matrix[0][1] = -r_cos.z * r_sin.x - r_cos.x * r_cos.y * r_sin.z;
	rotation_matrix[0][2] = r_sin.y * r_sin.z;
	rotation_matrix[1][0] = r_cos.y * r_cos.z * r_sin.x + r_cos.x * r_sin.z;
	rotation_matrix[1][1] = r_cos.x * r_cos.y * r_cos.z - r_sin.x * r_sin.z;
	rotation_matrix[1][2] = -r_cos.z * r_sin.y;
	rotation_matrix[2][0] = r_sin.x * r_sin.y;
	rotation_matrix[2][1] = r_cos.x * r_sin.y;
	rotation_matrix[2][2] = r_cos.y;*/