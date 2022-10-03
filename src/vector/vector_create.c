/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:19:51 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/03 15:53:22 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/* 	create a new t_vector.
	Upon successful completion, the pointer to new t_vector is returned. 
	Otherwise, NULL is returned */
t_coord	*new_vector(float x, float y, float z)
{
	t_coord	*new;

	new = NULL;
	new = malloc(sizeof(t_coord));
	if (new == NULL)
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	return (new);
}

/* 	create a new t_vector by two points.
	Upon successful completion, the pointer to new t_vector is returned. 
	Otherwise, NULL is returned */
t_coord	*new_vector_by_two_points(t_coord *a, t_coord *b)
{
	t_coord	*new;

	new = NULL;
	new = malloc(sizeof(t_coord));
	if (new == NULL)
		return (NULL);
	new->x = b->x - a->x;
	new->y = b->y - a->y;
	new->z = b->z - a->z;
	return (new);
}
