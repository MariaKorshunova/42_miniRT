/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:50:13 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/09 17:40:53 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	key_hook(int keycode, t_global *data);

void	hook(t_global *data)
{
	mlx_hook(data->window, ON_DESTROY, 0, minirt_close, data);
	mlx_hook(data->window, ON_KEYDOWN, 1L << 0, key_hook, data);
}

static int	key_hook(int keycode, t_global *data)
{
	if (keycode == 53)
		minirt_close(data);
	return (0);
}

/*  additional function for finding int keyhook
	mlx_key_hook(data->window, key_print_hook, data); */
int	key_print_hook(int keycode, t_global *data)
{
	(void) data;
	printf("Hello from key_hook %d!\n", keycode);
	return (0);
}
