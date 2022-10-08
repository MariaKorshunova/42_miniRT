/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:41:51 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/08 19:52:06 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	solve_quadratic_equation(float a, float b, float c, float roots[2])
{
	float	d_sqare;

	d_sqare = b * b - 4 * a * c;
	if (d_sqare < 0)
	{
		roots[0] = INFINITY;
		roots[1] = INFINITY;
		return (0);
	}
	if (d_sqare == 0)
	{
		roots[0] = (-b - sqrt(d_sqare)) / (2 * a);
		roots[1] = roots[0];
		return (1);
	}
	roots[0] = (-b - sqrt(d_sqare)) / (2 * a);
	roots[1] = (-b + sqrt(d_sqare)) / (2 * a);
	return (2);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	scene = parser(argc, argv);
	float roots[2];
	solve_quadratic_equation(-1, 0, 0, roots);
	printf("roots = %f, %f\n", roots[0], roots[1]);
	print_scene(scene);
	free_scene (scene);
	exit (0);
}

/* 	Временный main - заглушка без работающего парсера
	Создание сцены вручную 

void		scene_imitation_test(t_scene *scene);
t_sphere	*create_sphere(t_coord point, float d, int color);

int	main(int argc, char **argv)
{
	t_scene	*scene;

	(void)argc;
	(void)argv;
	scene = parser_createscene();
	scene_imitation_test(scene);
	print_scene(scene);
	free_scene(scene);
	return (0);
}

void	scene_imitation_test(t_scene *scene)
{
	t_coord		coord;

	new_vector(&scene->camera_point, 0, 0, 0);
	new_vector(&scene->camera_orientation, 0, 0, -1);
	scene->camera_fov = 70;
	scene->ambient_light_intensity = 1.0f;
	scene->ambient_light_rgb = 1;
	new_vector(&coord, 3, 2, -32);
	scene->obj->spheres = create_sphere(coord, 12, 10);
}

t_sphere	*create_sphere(t_coord point, float d, int color)
{
	t_sphere	*new_sphere;

	new_sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!new_sphere)
		return (NULL);
	new_sphere->point = point;
	new_sphere->diameter = d;
	new_sphere->color = color;
	new_sphere->next = NULL;
	return (new_sphere);
}*/
