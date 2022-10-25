/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:14:57 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/25 13:54:46 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_scene_characteristics(t_scene *scene);
void		print_color(int color);

void	print_spheres(t_sphere	*sp, char type)
{
	int	i;

	i = 0;
	while (sp)
	{
		if (type == 'a')
			printf("\e[0;33mSphere %d: \e[0m", i++);
		else
			printf("\e[0;33mSphere: \e[0m");
		printf("\t\e[0;34mPoint: \e[0m");
		print_coordinate(&sp->point, "\n");
		printf("        \t\e[0;34mDiameter: \e[0m%f\n",
			sp->diameter);
		print_color(sp->color);
		print_color(sp->color_ambient);
		sp = sp->next;
		if (type != 'a')
			break ;
	}
}

void	print_lights(t_light *l)
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
		print_color(l->color);
		l = l->next;
	}
}

void	print_cylinders(t_cylinder	*cy, char type)
{
	int	i;

	i = 0;
	while (cy)
	{
		if (type == 'a')
			printf("\e[0;33mCylinder %d: \e[0m", i++);
		else
			printf("\e[0;33mCylinder: \e[0m");
		printf("\t\e[0;34mPoint: \e[0m");
		print_coordinate(&cy->point, "\n");
		printf("        \t\e[0;34mOrientation: \e[0m");
		print_coordinate(&cy->orientation, "\n");
		print_color(cy->color);
		print_color(cy->color_ambient);
		printf("        \t\e[0;34mDiameter: \e[0m%f\n",
			cy->diameter);
		printf("        \t\e[0;34mHeight: \e[0m%f\n",
			cy->height);
		cy = cy->next;
		if (type != 'a')
			break ;
	}
}

void	print_planes(t_plane *pl, char type)
{
	int	i;

	i = 0;
	while (pl)
	{
		if (type == 'a')
			printf("\e[0;33mPlane %d: \e[0m", i++);
		else
			printf("\e[0;33mPlane: \e[0m");
		printf("\t\e[0;34mPoint: \e[0m");
		print_coordinate(&pl->point, "\n");
		printf("        \t\e[0;34mOrientation: \e[0m");
		print_coordinate(&pl->orientation, "\n");
		print_color(pl->color);
		print_color(pl->color_ambient);
		pl = pl->next;
		if (type != 'a')
			break ;
	}
}

void	print_scene(t_scene	*scene)
{
	printf("\n\tOne pixel struct is %lu bits,\n\
	One global struct is %lu bits,\n\
	One scene struct is %lu bits,\n\
	One obj struct is %lu bits,\n\
	One sphere struct is %lu bits,\n\
	One plane struct is %lu bits,\n\
	One cylinder struct is %lu bits,\n\
	One light struct is %lu bits,\n",
		sizeof(t_pixel), sizeof(t_global), sizeof(t_scene),
		sizeof(t_objects), sizeof(t_sphere), sizeof(t_plane),
		sizeof(t_cylinder), sizeof(t_light));
	print_scene_characteristics(scene);
	if (scene->obj && scene->obj->spheres)
		print_spheres(scene->obj->spheres, 'a');
	if (scene->obj && scene->obj->lights)
		print_lights(scene->obj->lights);
	if (scene->obj && scene->obj->cylinders)
		print_cylinders(scene->obj->cylinders, 'a');
	if (scene->obj && scene->obj->planes)
		print_planes(scene->obj->planes, 'a');
}

static void	print_scene_characteristics(t_scene *scene)
{
	printf("\e[0;32mCamera_point: \e[0m");
	print_coordinate(&scene->camera_point, "\n");
	printf("\e[0;32mCamera_angles: \e[0m%f\t%f\n", scene->camera_angles[0],
		scene->camera_angles[1]);
	printf("\e[0;32mCamera_orientation: \e[0m");
	print_coordinate(&scene->camera_orientation, "\n");
	printf("\e[0;32mCamera_fov: \e[0m%f\n", scene->camera_fov);
	printf("\e[0;32mAmbient_light_intensity: \e[0m%f\n",
		scene->ambient_light_intensity);
	printf("\e[0;32mAmbient_light_rgb:\e[0m\t%d, %d, %d\n",
		scene->ambient_light_rgb >> 16 & 255,
		scene->ambient_light_rgb >> 8 & 255,
		scene->ambient_light_rgb & 255);
	printf("\e[0;32mObjects:\e[0m\n");
}

void	print_coordinate(t_coord *coord, char *endchar)
{
	printf("(%f, %f, %f)", coord->x, coord->y, coord->z);
	if (endchar)
		printf("%s", endchar);
}

void	print_color(int color)
{
	printf("        \t\e[0;34mColor, RGB:\t \e[0m%d, %d, %d\t[0x%x]\n",
		color >> 16 & 255, color >> 8 & 255, color & 255, color & 0xffffff);
}
