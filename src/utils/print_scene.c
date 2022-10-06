/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:14:57 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/06 18:28:31 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_scene_characteristics(t_scene *scene);

void	print_spheres(t_sphere	*sp)
{
	int	i;

	i = 0;
	while (sp)
	{
		printf("\e[0;33mSphere %d: \e[0m", i++);
		printf("\t\e[0;34mPoint: \e[0m");
		print_coordinate(&sp->point, "\n");
		printf("        \t\e[0;34mDiameter: \e[0m%f\n",
			sp->diameter);
		printf("        \t\e[0;34mColor: \e[0m0x%x\n",
			sp->color);
		sp = sp->next;
	}
}

void	print_lights(t_light	*l)
{
	int	i;

	i = 0;
	while (l)
	{
		printf("\e[0;33mLight %d: \e[0m", i++);
		printf("\t\e[0;34mPoint: \e[0m");
		print_coordinate(&l->point, "\n");
		printf("        \t\e[0;34mLighting ratio: \e[0m%f\n",
			l->lighting_ratio);
		printf("        \t\e[0;34mColor: \e[0m0x%x\n",
			l->color);
		l = l->next;
	}
}

void	print_cylinders(t_cylinder	*cy)
{
	int	i;

	i = 0;
	while (cy)
	{
		printf("\e[0;33mCylinder %d: \e[0m", i++);
		printf("\t\e[0;34mPoint: \e[0m");
		print_coordinate(&cy->point, "\n");
		printf("        \t\e[0;34mOrientation: \e[0m");
		print_coordinate(&cy->orientation, "\n");
		printf("\n        \t\e[0;34mColor: \e[0m0x%x\n",
			cy->color);
		printf("        \t\e[0;34mDiameter: \e[0m%f\n",
			cy->diameter);
		printf("        \t\e[0;34mHeight: \e[0m%f\n",
			cy->height);
		cy = cy->next;
	}
}

void	print_planes(t_plane	*pl)
{
	int	i;

	i = 0;
	while (pl)
	{
		printf("\e[0;33mPlane %d: \e[0m", i++);
		printf("\t\e[0;34mPoint: \e[0m");
		print_coordinate(&pl->point, "\n");
		printf("        \t\e[0;34mOrientation: \e[0m");
		print_coordinate(&pl->orientation, "\n");
		printf("\n        \t\e[0;34mColor: \e[0m0x%x\n",
			pl->color);
		pl = pl->next;
	}
}

void	print_scene(t_scene	*scene)
{
	print_scene_characteristics(scene);
	if (scene->obj && scene->obj->spheres)
		print_spheres(scene->obj->spheres);
	if (scene->obj && scene->obj->lights)
		print_lights(scene->obj->lights);
	if (scene->obj && scene->obj->cylinders)
		print_cylinders(scene->obj->cylinders);
	if (scene->obj && scene->obj->planes)
		print_planes(scene->obj->planes);
}

static void	print_scene_characteristics(t_scene *scene)
{
	printf("\e[0;32mCamera_point: \e[0m");
	print_coordinate(&scene->camera_point, "\n");
	printf("\e[0;32mCamera_orientation: \e[0m");
	print_coordinate(&scene->camera_orientation, "\n");
	printf("\e[0;32mCamera_fov: \e[0m%f\n", scene->camera_fov);
	printf("\e[0;32mAmbient_light_intensity: \e[0m%f\n",
		scene->ambient_light_intensity);
	printf("\e[0;32mAmbient_light_rgb: \e[0m0x%x\n", scene->ambient_light_rgb);
	printf("\e[0;32mObjects:\e[0m\n");
}

void	print_coordinate(t_coord *coord, char *endchar)
{
	printf("(%f, %f, %f)", coord->x, coord->y, coord->z);
	if (endchar)
		printf("%s", endchar);
}
