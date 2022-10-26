/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:58:47 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/25 15:05:24 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	ft_resize_sphere(int mousecode, t_global	*global);
static void	ft_resize_cylinder(int mousecode, t_global	*global);

void	ft_resize_object(int mousecode, t_global	*global)
{
	if (!global->nearest_obj)
		return ;
	if (global->nearest_type == SPHERE)
		ft_resize_sphere(mousecode, global);
	if (global->nearest_type == CYLINDER)
		ft_resize_cylinder(mousecode, global);
	return ;
}

static void	ft_resize_sphere(int mousecode, t_global	*global)
{
	if (mousecode == 5)
	{
		((t_sphere *)(global->nearest_obj))->diameter += 0.1;
		raytracer(global);
	}
	else if (mousecode == 4)
	{
		if (((t_sphere *)(global->nearest_obj))->diameter <= 0.1)
			return ;
		((t_sphere *)(global->nearest_obj))->diameter -= 0.1;
		raytracer(global);
	}
}

static void	ft_resize_cylinder(int mousecode, t_global	*global)
{
	if (mousecode == 5)
	{
		((t_cylinder *)(global->nearest_obj))->diameter += 0.1;
		raytracer(global);
	}
	else if (mousecode == 4)
	{
		if (((t_cylinder *)(global->nearest_obj))->diameter <= 0.1)
			return ;
		((t_cylinder *)(global->nearest_obj))->diameter -= 0.1;
		raytracer(global);
	}
}
