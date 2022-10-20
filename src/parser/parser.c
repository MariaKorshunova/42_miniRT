/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:03:06 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/20 19:54:27 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parser.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == ' ' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return ((int) c);
	return (0);
}

static	int	open_file(int argc, char **argv)
{
	char	*tmp;
	int		i;

	if (argc != 2 || !argv[1] || !argv[1][0] || ft_strlen (argv[1]) < 3)
	{
		printf("Usage: miniRT (.rt scene file)\n");
		exit (2);
	}
	tmp = argv[1];
	i = 0;
	while (tmp[i])
		i++;
	tmp = tmp + i - 3;
	if (ft_strncmp(tmp, ".rt", 4))
	{
		printf("Usage: miniRT (.rt scene file)\n");
		exit (2);
	}
	i = open (argv[1], O_RDONLY);
	if (!i || i == -1)
	{
		printf("Cannot open the \"%s\" file\n", argv[1]);
		exit(2);
	}
	return (i);
}

t_scene	*parser_createscene(t_parser *p)
{
	t_scene	*scene;

	scene = (t_scene *) malloc (sizeof(t_scene));
	if (!scene)
		parser_error (12, 0);
	scene->obj = (t_objects *) malloc (sizeof(t_objects));
	if (!(scene->obj))
		parser_error (12, p);
	new_vector(&scene->camera_point, 0, 0, 0);
	new_vector(&scene->camera_orientation, 0, 0, 1);
	scene->camera_fov = 90;
	scene->ambient_light_intensity = 1;
	scene->ambient_light_rgb = 0xffffff;
	scene->obj->cylinders = 0;
	scene->obj->lights = 0;
	scene->obj->planes = 0;
	scene->obj->spheres = 0;
	return (scene);
}

static void	parser_linehandler(t_parser	*p)
{
	p->i = 0;
	parser_skipspaces(p->s, &(p->i));
	if (!p->s || !p->s[p->i] || p->s[p->i] == '#')
		return ;
	else if (p->s[p->i] == 'A' && ft_isspace(p->s[p->i + 1]))
		parser_readambient(p);
	else if (p->s[p->i] == 'C' && ft_isspace(p->s[p->i + 1]))
		parser_readcamera(p);
	else if (p->s[p->i] == 'L' && ft_isspace(p->s[p->i + 1]))
		parser_readlight(p);
	else if (!ft_strncmp(p->s + p->i, "sp", 2) && ft_isspace(p->s[p->i + 2]))
		parser_readsphere(p);
	else if (!ft_strncmp(p->s + p->i, "pl", 2) && ft_isspace(p->s[p->i + 2]))
		parser_readplane(p);
	else if (!ft_strncmp(p->s + p->i, "cy", 2) && ft_isspace(p->s[p->i + 2]))
		parser_readcylinder(p);
	else
		parser_error(1, p);
}

void	translate_objects(t_scene *scene)
{
	t_objects	obj;

	obj = *scene->obj;
	while (obj.spheres)
	{
		vector_addition(&obj.spheres->point, &obj.spheres->point,
			&scene->camera_point);
		obj.spheres = obj.spheres->next;
	}
	while (obj.planes)
	{
		vector_addition(&obj.planes->point, &obj.planes->point,
			&scene->camera_point);
		obj.planes = obj.planes->next;
	}
	while (obj.cylinders)
	{
		vector_addition(&obj.cylinders->point, &obj.cylinders->point,
			&scene->camera_point);
		obj.cylinders = obj.cylinders->next;
	}
	while (obj.lights)
	{
		vector_addition(&obj.lights->point, &obj.lights->point,
			&scene->camera_point);
		obj.lights = obj.lights->next;
	}
}

t_scene	*parser(int argc, char **argv)
{
	t_parser	parser_env;

	parser_env.file_fd = open_file(argc, argv);
	parser_env.scene = parser_createscene(&parser_env);
	parser_env.readelem = 0;
	parser_env.s = get_next_line(parser_env.file_fd);
	while (parser_env.s)
	{
		parser_linehandler(&parser_env);
		printf("%s", parser_env.s);
		free (parser_env.s);
		parser_env.s = get_next_line(parser_env.file_fd);
	}
	close(parser_env.file_fd);
	printf("\nreading is done, file_fd closed\n");
	get_fov_angles(parser_env.scene);
	translate_objects(parser_env.scene);
	parser_fill_color_ambient(&parser_env);
	return (parser_env.scene);
}
