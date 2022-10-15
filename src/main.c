/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:41:51 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/15 14:09:43 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* 	Сделать универсальной функцию
	Подсчет вектора луча вытащить наверх,
	чтобы не считать отдельно в каждом фигуре */
void	check_for_spheres(t_global *global, t_ray *ray, int *x, int *y)
{
	t_sphere	*sphere;
	t_sphere	*closest_sphere;
	float		tmp;
	float		length;

	sphere = global->scene->obj->spheres;
	closest_sphere = 0;
	length = -1;
	while (sphere)
	{
		tmp = check_intersection_sphere(sphere, ray);
		if (tmp != -1 && (length == -1 || tmp < length))
		{
			length = tmp;
			closest_sphere = sphere;
		}
		sphere = sphere->next;
	}
	if (length != -1 && closest_sphere)
		mlx_pixel_put(global->mlx, global->window, *x, *y,
			closest_sphere->color);
}

void	raytracer(t_global *global)
{
	t_ray	ray;
	float	lambda;
	t_coord	camera_plane;
	int		x;
	int		y;

	ray.point[0] = global->scene->camera_point;
	vector_addition(&(camera_plane), &(ray.point[0]),
		&(global->scene->camera_orientation));
	lambda = 2 * global->scene->camera_angles[0] / WIDTH;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			new_vector(&(ray.point[1]),
				global->scene->camera_point.x
				+global->scene->camera_orientation.x
				-global->scene->camera_angles[0] + lambda * x,
				global->scene->camera_point.y
				+ global->scene->camera_orientation.y
				+ global->scene->camera_angles[1] - lambda * y,
				global->scene->camera_point.z
				+ global->scene->camera_orientation.z);
			check_for_spheres(global, &ray, &x, &y);
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_global	data;

	data.scene = parser(argc, argv);
	print_scene(data.scene);
	init_image(&data);
	raytracer(&data);
	mlx_put_image_to_window(data.mlx, data.img.img, data.window, 0, 0);
	hook(&data);
	mlx_loop(data.mlx);
	minirt_close(&data);
	exit (0);
}

int	minirt_close(t_global *data)
{
	free_scene(data->scene);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->window);
	exit(0);
}
