/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:41:51 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/15 17:40:42 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_global	data;

	data.scene = parser(argc, argv);
	print_scene(data.scene);
	init_image(&data);
	raytracer(&data);
	mlx_put_image_to_window(data.mlx, data.img.img, data.window, 0, 0);
	hook(&data);
	mlx_loop(data.mlx);
	minirt_close(&data);
	exit (0);
}

int	minirt_close(t_global *data)
{
	free_scene(data->scene);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->window);
	exit(0);
}
