/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:41:51 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/14 05:03:01 by bpoetess         ###   ########.fr       */
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
	t_coord	d;
	t_coord	oc;

	vector_subtraction(&d, &ray->point[0], &(ray->point[1]));
	vector_subtraction(&oc, &sphere->point, &(ray->point[0]));
	if (!solve_quadratic_equation(
			scalar_product_2_vectors(&(d), &(d)),
			2 * scalar_product_2_vectors(&(d), &(oc)),
			scalar_product_2_vectors(&(oc), &(oc))
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
				-global->scene->camera_angles[0] + lambda * x,
				global->scene->camera_angles[1] - lambda * y,
				global->scene->camera_point.z + 1);
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
