/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:41:51 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/05 17:44:44 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_scene	*scene;

	scene = parser(argc, argv);
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

	new_vector(&scene->camera_point, 0, 0, -1);
	new_vector(&scene->camera_orientation, 0, 0, 1);
	scene->camera_fov = M_PI;
	scene->ambient_light_intensity = 1.0f;
	scene->ambient_light_rgb = 1;
	new_vector(&coord, 3, 2, -32);
	scene->obj->spheres = create_sphere(coord, 5, 10);
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
}
*/