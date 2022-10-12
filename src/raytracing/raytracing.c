/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:46:08 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/12 17:21:37 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	int		x_img;		// Координаты image  в mlx
	int		y_img;

	t_coord		plane;	// координаты плоскости проецирования,
						// рассчитываются с помощью FOV
*/

void	raytracing(t_global *data)
{
	int			x_img;
	int			y_img;

	y_img = 0;
	while (y_img <= HEIGHT)
	{
		x_img = 0;
		while (x_img <= WIDTH)
		{
			ft_mlx_pixel_put_img(&data->img, x_img, y_img,
				((int) hypot((int) x_img, (int) y_img) & 0xff)
				| ((int) hypot((int)x_img, (int)y_img) & 0xff00)
				| ((int) hypot((int)x_img, (int)y_img) & 0xff0000));
			x_img += 1;
		}
		y_img += 1;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img);
}
