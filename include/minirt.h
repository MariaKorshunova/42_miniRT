/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:00:49 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/06 18:09:33 by bpoetess         ###   ########.fr       */
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

t_scene	*parser(int argc, char **argv);
void	free_scene(t_scene *scene);

/* utils */
void	print_scene(t_scene	*scene);
void	print_coordinate(t_coord *coord, char *endchar);

#endif