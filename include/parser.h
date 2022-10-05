/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:14:34 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/05 08:15:15 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"

void	parser_skipspaces(char *s, int *i);
void	parser_error(t_scene *scene, int exitcode);
float	parser_readfloat(t_scene *scene, char *s, int *i);
int		parser_readcolor(t_scene *scene, char *s, int *i);
t_coord	parser_readcoord(t_scene *scene, char *s, int *i);

void	parser_readambient(t_scene *scene, char *s, int *i, int *readelem);
void	parser_readcamera(t_scene *scene, char *s, int *i, int *readelem);
void	parser_readlight(t_scene *scene, char *s, int *i, int *readelem);

void	free_scene(t_scene *scene);

#endif
