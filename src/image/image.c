/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:24:32 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/24 17:38:48 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	error_mlx(t_global *data);

void	clean_image(void *img)
{
	int	i;
	int	j;

	if (!img)
		return ;
	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
			ft_mlx_pixel_put_img(img, i, j++, BACKGROUND_COLOR);
		i++;
	}	
}

void	ft_mlx_pixel_put_img(t_img	*img, int x, int y, int color)
{
	char			*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_image(t_global *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error_mlx(data);
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "minirt");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->window || !data->img.img)
		error_mlx(data);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&(data->img.bpp), &(data->img.line_length), &(data->img.endian));
	if (!data->img.addr)
		error_mlx(data);
}

static void	error_mlx(t_global *data)
{
	free_scene(data->scene);
	perror(NULL);
	exit (12);
}
