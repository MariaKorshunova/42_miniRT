/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:20:11 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/03 15:57:10 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/* 	Вывод на stdout вектора vector, опционально с именем вектора name */
void	print_vector(char *name, t_coord *vector)
{
	if (vector == NULL)
		return ;
	if (name)
		printf("%s=(%f, %f, %f)\n", name, vector->x, vector->y, vector->z);
	else
		printf("(%f, %f, %f)\n", vector->x, vector->y, vector->z);
	return ;
}
