/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 13:57:39 by jmabel            #+#    #+#             */
/*   Updated: 2021/10/17 16:21:28 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if ((char *)dst == 0 && (char *)src == 0)
		return (dst);
	if (src > dst)
	{
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	if (src <= dst)
	{
		while (len-- != 0)
			((char *)dst)[len] = ((char *)src)[len];
	}
	return (dst);
}
