/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:14:57 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/05 17:44:09 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_scene_characteristics(t_scene *scene);

void	print_scene(t_scene	*scene)
{
	int	i;

	i = 1;
	print_scene_characteristics(scene);
	while (scene->obj->spheres)
	{
		printf("\e[0;33mSphere %d: \e[0m", i++);
		printf("\t\e[0;34mPoint: \e[0m");
		print_coordinate(&scene->obj->spheres->point, "\n");
		printf("        \t\e[0;34mDiameter: \e[0m%f\n",
			scene->obj->spheres->diameter);
		printf("        \t\e[0;34mColor: \e[0m%d\n",
			scene->obj->spheres->color);
		scene->obj->spheres = scene->obj->spheres->next;
	}	
}

static void	print_scene_characteristics(t_scene *scene)
{
	printf("\e[0;32mCamera_point: \e[0m");
	print_coordinate(&scene->camera_point, "\n");
	printf("\e[0;32mCamera_orientation: \e[0m");
	print_coordinate(&scene->camera_point, "\n");
	printf("\e[0;32mCamera_fov: \e[0m%f\n", scene->camera_fov);
	printf("\e[0;32mAmbient_light_intensity: \e[0m%f\n",
		scene->ambient_light_intensity);
	printf("\e[0;32mAmbient_light_rgb: \e[0m%d\n", scene->ambient_light_rgb);
	printf("\e[0;32mObjects:\e[0m\n");
}

void	print_coordinate(t_coord *coord, char *endchar)
{
	printf("(%f, %f, %f)", coord->x, coord->y, coord->z);
	if (endchar)
		printf("%s", endchar);
}
