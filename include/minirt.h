/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:00:49 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/08 19:34:57 by bpoetess         ###   ########.fr       */
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

# define WIDTH 800
# define HEIGHT 600

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	void	*image;
}	t_mlx;

typedef struct s_global
{
	t_scene	*scene;
	t_mlx	*mlx;
}	t_global;

t_scene	*parser(int argc, char **argv);
void	free_scene(t_scene *scene);

/* utils */
void	print_scene(t_scene	*scene);
void	print_coordinate(t_coord *coord, char *endchar);

#endif