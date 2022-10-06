/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:14:34 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/06 18:05:50 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"

t_scene	*parser_createscene(void);

void	parser_skipspaces(char *s, int *i);
void	parser_error(t_scene *scene, int exitcode);
float	parser_readfloat(t_scene *scene, char *s, int *i);
int		parser_readcolor(t_scene *scene, char *s, int *i);
t_coord	parser_readcoord(t_scene *scene, char *s, int *i);

void	parser_readambient(t_scene *scene, char *s, int *i, int *readelem);
void	parser_readcamera(t_scene *scene, char *s, int *i, int *readelem);
void	parser_readlight(t_scene *scene, char *s, int *i, int *readelem);

void	free_scene(t_scene *scene);

float	parser_readfloat(t_scene *scene, char *s, int *i);

#endif
