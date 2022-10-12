/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:41:51 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/12 17:56:19 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_point(t_coord *point, float x, float y, float z)
{
	point->x = x;
	point->y = y;
	point->z = z;
}

float	check_intersection_sphere(t_sphere *sphere, t_ray *ray)
{
	float	points[2];

	if (!solve_quadratic_equation(
			pow(2, vector_length(&(ray->point[1]))),
			vector_length_by_two_points(&(ray->point[1]), &(sphere->point)),
			pow(2, vector_length(&(sphere->point)))
			- pow(2, sphere->diameter / 2),
			points))
		return (-1);
	if (points[0] < points[1])
		return (points[0]);
	return (points[1]);
}

void	check_for_spheres(t_global *global, t_ray *ray, int *x, int *y)
{
	t_sphere	*sphere;
	float		tmp;
	float		length;

	sphere = global->scene->obj->spheres;
	length = -1;
	while (sphere)
	{
		tmp = check_intersection_sphere(sphere, ray);
		if (tmp != -1 && length > tmp)
			length = tmp;
		sphere = sphere->next;
	}
	if (length != -1)
	{
		printf("\t%f\n", length);
		mlx_pixel_put(global->mlx, global->window, *x, *y, 0xffffff);
	}
}

void	raytracer(t_global *global)
{
	t_ray	ray;
	t_coord	lambda;
	int		x;
	int		y;

	new_vector(&(ray.point[0]), 0, 0, -1);
	new_vector(&(ray.point[1]), -global->scene->camera_angles[0],
		global->scene->camera_angles[1], 0);
	lambda.x = 2 * global->scene->camera_angles[0] / WIDTH;
	lambda.y = 2 * global->scene->camera_angles[1] / HEIGHT;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			new_vector(&(ray.point[1]),
				-global->scene->camera_angles[0] + lambda.x * x,
				global->scene->camera_angles[1] - lambda.y * y, 0);
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
	// raytracing(&data);
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
