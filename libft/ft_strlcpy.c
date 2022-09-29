/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 15:52:55 by jmabel            #+#    #+#             */
/*   Updated: 2021/10/17 17:13:09 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[len] != '\0')
	{
		if (len < (dstsize - 1))
		{
			dst[i] = src[len];
			i++;
		}
		len++;
	}
	dst[i] = '\0';
	return (len);
}
