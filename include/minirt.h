/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:00:49 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/14 05:29:37 by bpoetess         ###   ########.fr       */
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

/*	 ./raytracing/solver.c
	 solver of equations*/
int		solve_quadratic_equation(float a, float b, float c, float roots[2]);

/* 	raytracing.c */
void	raytracing(t_global *data);

/* utils */
void	print_scene(t_scene	*scene);
void	print_coordinate(t_coord *coord, char *endchar);

#endif