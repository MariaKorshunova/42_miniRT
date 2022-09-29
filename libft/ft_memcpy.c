/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 11:32:16 by jmabel            #+#    #+#             */
/*   Updated: 2021/10/17 13:53:33 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if ((char *)dst == (char *)src)
		return (dst);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}
