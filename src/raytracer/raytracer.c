/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:46:08 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/20 20:03:22 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	raytracer(t_global *global)
{
	float	lambda;
	t_pixel	pixel;
	t_coord	camera_plane;

	pixel.ray.point[0] = global->scene->camera_point;
	new_vector(&pixel.ray.point[0], 0, 0, -1);
	vector_addition(&(camera_plane), &(pixel.ray.point[0]),
		&(global->scene->camera_orientation));
	lambda = 2 * global->scene->camera_angles[0] / WIDTH;
	pixel.y = 0;
	while (pixel.y < HEIGHT)
	{
		pixel.x = 0;
		while (pixel.x < WIDTH)
		{
			pixel_cleaning(&pixel);
			new_vector(&(pixel.ray.point[1]),
				+global->scene->camera_orientation.x
				-global->scene->camera_angles[0] + lambda * pixel.x,
				global->scene->camera_orientation.y
				+ global->scene->camera_angles[1] - lambda * pixel.y,
				0);
			check_intersection(global, &pixel);
			pixel_computing(global, &pixel);
			pixel.x++;
		}
		pixel.y++;
	}
}
