/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:41:51 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/03 19:50:41 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Временная функция тестирования header.h. */
void	test_vector(void);

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
