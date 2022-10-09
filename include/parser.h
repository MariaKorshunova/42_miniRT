/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:14:34 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/09 18:48:36 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"

typedef struct s_parser
{
	t_scene	*scene;
	int		readelem;
	char	*s;
	int		i;
	int		file_fd;
}	t_parser;

t_scene	*parser_createscene(t_parser *p);
int		ft_isspace(char c);

void	parser_skipspaces(char *s, int *i);
void	parser_error(int exitcode, t_parser *parser);
float	parser_readfloat(t_parser *parser);
int		parser_readcolor(t_parser *parser);
t_coord	parser_readcoord(t_parser *parser);

void	parser_readambient(t_parser *parser);
void	parser_readcamera(t_parser *parser);
void	parser_readlight(t_parser *parser);

void	free_scene(t_scene *scene);

void	parser_skipspacesifnotspaceerror(t_parser *parser);
float	parser_readfloat(t_parser *parser);

void	parser_readsphere(t_parser *parser);

void	parser_check_isnotnormailzed(t_parser *parser, t_coord vect);
void	parser_readplane(t_parser *parser);

void	parser_readcylinder(t_parser *parser);

#endif
