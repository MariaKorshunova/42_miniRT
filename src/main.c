/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:41:51 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/03 22:48:21 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Временная функция тестирования header.h. */
void	test_vector(void);

typedef struct s_light		t_light;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;

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
	t_sphere	*next;
};

struct s_plane
{
	t_coord	point;
	t_coord	orientation;
	int		color;
	t_plane	*next;
};

struct s_cylinder
{
	t_coord		point;
	t_coord		orientation;
	float		diameter;
	float		height;
	int			color;
	t_cylinder	*next;
};

typedef struct s_objects
{
	t_light		*lights;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
}	t_objects;

typedef struct s_scene
{
	t_coord		camera_point;
	t_coord		camera_orientation;
	float		camera_fov;
	float		ambient_light_intensity;
	int			ambient_light_rgb;
	t_objects	objects;
}	t_scene;

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

void	parser_linehandler(t_scene *scene, char *tmp)
{
	if (!scene || !ft_strncmp(tmp, "\n", 2))
		return ;
}

t_scene	*parser(int argc, char **argv)
{
	int		file_fd;
	char	*tmp;
	t_scene	*scene;

	file_fd = open_file(argc, argv);
	scene = (t_scene *) malloc (sizeof(t_scene));
	if (!scene)
		exit (12);
	tmp = get_next_line(file_fd);
	while (tmp)
	{
		parser_linehandler(scene, tmp);
		free (tmp);
		tmp = get_next_line(file_fd);
	}
	return (scene);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return (0);
}

void	test_vector(void)
{
	t_coord	a;
	t_coord	b;
	t_coord	ab;

	new_vector(&a, -1, 0, 1);
	new_vector(&b, -2, 1, 2);
	print_vector("point a", &a);
	print_vector("point b", &b);
	new_vector_by_two_points(&ab, &a, &b);
	print_vector("AB =", &ab);
	printf("length AB = %f\n", vector_length(&ab));
	printf("length AB by 2 points = %f\n", vector_length_by_two_points(&b, &a));
	scalar_multiplication(&ab, -2);
	print_vector("AB =", &ab);
	vector_addition(&ab, &ab, &ab);
	print_vector("new AB = AB + AB =", &ab);
}
