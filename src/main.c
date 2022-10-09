/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:41:51 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/09 17:48:04 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_global	data;

	data.scene = parser(argc, argv);
	print_scene(data.scene);
	init_image(&data);
	hook(&data);
	mlx_loop(data.mlx);
	minirt_close(&data);
	exit (0);
}

int	minirt_close(t_global *data)
{
	free_scene(data->scene);
	mlx_destroy_window(data->mlx, data->window);
	exit(0);
}
