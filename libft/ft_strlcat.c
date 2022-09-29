/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 17:13:43 by jmabel            #+#    #+#             */
/*   Updated: 2021/10/18 11:30:21 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (dst[j] != '\0' && j < dstsize)
		j++;
	while (src[i] != '\0' && j + i < dstsize - 1)
	{
		dst[j + i] = src[i];
		i++;
	}
	if (j + i < dstsize)
		dst[j + i] = '\0';
	return (ft_strlen(src) + j);
}
