/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 08:03:06 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/05 17:20:00 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parser.h"

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

t_scene	*parser_createscene(void)
{
	t_scene	*scene;

	scene = (t_scene *) malloc (sizeof(t_scene));
	if (!scene)
		exit (12);
	scene->obj = (t_objects *) malloc (sizeof(t_objects));
	if (!(scene->obj))
		exit (12);
	scene->obj->cylinders = 0;
	scene->obj->lights = 0;
	scene->obj->planes = 0;
	scene->obj->spheres = 0;
	return (scene);
}

static void	parser_linehandler(t_scene *scene, char *s, int *readelem)
{
	int	i;

	i = 0;
	parser_skipspaces(s, &i);
	if (!scene || !s || !s[i])
		return ;
	if (s[i] == 'A')
		parser_readambient(scene, s, &i, readelem);
	if (s[i] == 'C')
		parser_readcamera(scene, s, &i, readelem);
	if (s[i] == 'L')
		parser_readlight(scene, s, &i, readelem);
}

t_scene	*parser(int argc, char **argv)
{
	int		file_fd;
	char	*tmp;
	int		readelem;
	t_scene	*scene;

	file_fd = open_file(argc, argv);
	scene = parser_createscene();
	readelem = 0;
	tmp = get_next_line(file_fd);
	while (tmp)
	{
		parser_linehandler(scene, tmp, &readelem);
		free (tmp);
		tmp = get_next_line(file_fd);
	}
	return (scene);
}
