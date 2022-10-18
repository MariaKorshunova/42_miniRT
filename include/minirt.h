/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:00:49 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/18 18:00:03 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h> 
# include <sys/uio.h> 
# include <stdio.h> 
# include <stdlib.h>
# include <math.h>

# include "../libft/libft.h"
# include "get_next_line.h"
# include "vector.h"
# include "scene.h"
# include "parser.h"
# include "../libmlx/mlx.h"

# define WIDTH 1920
# define HEIGHT 1080

# define BACKGROUND_COLOR 0

/* set mlx events */
# define ON_DESTROY 17
# define ON_KEYDOWN 2

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_global
{
	t_scene	*scene;
	void	*mlx;
	void	*window;
	t_img	img;
}	t_global;

typedef struct s_pixel
{
	int			x;
	int			y;
	t_ray		ray;
	t_coord		d;
	float		length;
	t_coord		intersection;
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
}	t_pixel;

t_scene	*parser(int argc, char **argv);
void	free_scene(t_scene *scene);
int		minirt_close(t_global *data);

/* 	./image/image.c 
	functions for mlx management with image*/
void	ft_mlx_pixel_put_img(t_img	*img, int x, int y, int color);
void	init_image(t_global *data);

/* 	./image/hook.c
	manage events*/
void	hook(t_global *data);
int		key_print_hook(int keycode, t_global *data);

/*	./raytracing/check_intersection.c
	functions check intersection with objects */
void	check_intersection(t_global *global, t_pixel *pixel);

/*	 ./raytracing/intersection.c
	 function returns distance to some object */
float	check_intersection_plane(t_plane *plane, t_ray *ray, t_coord *d);
float	check_intersection_sphere(t_sphere *sphere, t_ray *ray, t_coord *d);
float	check_intersection_cylinder(t_cylinder	*cylinder,
			t_ray *ray, t_coord *d);

/*	./raytracer/rayracer.c */
void	raytracer(t_global *global);

/*	./raytracer/compute_pixel_sphere.c */
void	pixel_computing(t_global *global, t_pixel *pixel);
void	pixel_cleaning(t_pixel *pixel);
int		color_diffusal(int color_sum, int color1, int color2, float intensity);
void	pixel_computing_sphere(t_global *global, t_pixel *pixel);
float	pixel_computing_sphere_diffusal_recflect_ratio(t_global *global,
			t_pixel *pixel);

/*	./raytracer/compute_pixel_plane.c */
void	pixel_computing_plane(t_global *global, t_pixel *pixel);
float	pixel_computing_plane_diffusal_recflect_ratio(t_global *global,
			t_pixel *pixel);

/*	 ./raytracing/solver.c
	 solver of equations*/
int		solve_quadratic_equation(float a, float b, float c, float roots[2]);

/* utils */
void	print_scene(t_scene	*scene);
void	print_coordinate(t_coord *coord, char *endchar);

#endif