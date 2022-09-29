/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:48:03 by jmabel            #+#    #+#             */
/*   Updated: 2022/01/01 20:53:37 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*dst;
	size_t	size_max;

	size_max = 18446744073709551615UL;
	if (count && (size > size_max / count))
		return (NULL);
	dst = malloc(count * size);
	if (dst == NULL)
		return (NULL);
	ft_bzero(dst, size * count);
	return (dst);
}
