/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 03:57:30 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/22 19:20:07 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

typedef struct s_light		t_light;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_scene		t_scene;
typedef struct s_objects	t_objects;

typedef struct s_coord
{
	float	x;
	float	y;
	float	z;
}	t_coord;

typedef struct s_ray
{
	t_coord	point[2];
}	t_ray;

struct s_light
{
	t_coord	point;
	float	lighting_ratio;
	int		color;
	t_light	*next;
};

struct s_sphere
{
	t_coord		point;
	float		diameter;
	int			color;
	int			color_ambient;
	t_sphere	*next;
};

struct s_plane
{
	t_coord	point;
	t_coord	orientation;
	int		color;
	int		color_ambient;
	t_plane	*next;
};

typedef enum e_cyl_intersect
{
	NO_INTERSECT,
	PIPE,
	PLANE_BEGIN,
	PLANE_END,
}	t_cyl_intersect;

struct s_cylinder
{
	t_coord		point;
	t_coord		orientation;
	float		diameter;
	float		height;
	int			color;
	int			color_ambient;
	int			flag_type;
	t_plane		plane_begin;
	t_plane		plane_end;
	t_cylinder	*next;
};

struct s_objects
{
	t_light		*lights;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
};

struct s_scene
{
	t_coord		camera_point;
	t_coord		camera_orientation;
	float		camera_fov;
	float		camera_angles[2];
	float		ambient_light_intensity;
	int			ambient_light_rgb;
	t_objects	*obj;
};

#endif