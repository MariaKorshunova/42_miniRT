/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:00:22 by jmabel            #+#    #+#             */
/*   Updated: 2021/10/18 16:42:02 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*temp_s1;
	unsigned char	*temp_s2;

	i = 0;
	temp_s1 = (unsigned char *)s1;
	temp_s2 = (unsigned char *)s2;
	while (i < n)
	{
		if (*temp_s1 != *temp_s2)
			return (*temp_s1 - *temp_s2);
		temp_s1++;
		temp_s2++;
		i++;
	}
	return (0);
}
