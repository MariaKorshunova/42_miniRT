/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:44:53 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/27 19:24:20 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../../include/transformation.h"

static void	fill_angles(t_coord *r_sin, t_coord *r_cos, t_coord *cam)
{
	*r_sin = *cam;
	new_vector(r_cos, 0, 0, 1);
	vector_multiplication(r_sin, r_cos, r_sin);
	r_cos->x = cos(asin(r_sin->x));
	r_cos->y = cos(asin(r_sin->y));
	r_cos->z = cos(asin(r_sin->z));
}

static void	fill_rotation_matrix(float rotation_matrix[3][3], t_coord *coord)
{
	t_coord	r_cos;
	t_coord	r_sin;

	fill_angles(&r_sin, &r_cos, coord);
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

void	rotate_objects(t_scene *scene, t_coord *coord)
{
	t_objects	obj;
	t_coord		tmp;
	float		rotation_matrix[3][3];

	obj = *scene->obj;
	if (coord->z < 0)
	{
		new_vector(&tmp, 0, 0, 1);
		fill_rotation_matrix(rotation_matrix, &tmp);
		rotation_matrix[1][1] = -1;
		rotation_matrix[2][2] = -1;
		apply_rotation_to_objects(&scene->camera_orientation,
			&obj, rotation_matrix);
	}
	fill_rotation_matrix(rotation_matrix, coord);
	apply_rotation_to_objects(&scene->camera_orientation,
		&obj, rotation_matrix);
}
