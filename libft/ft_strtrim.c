/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:53:13 by jmabel            #+#    #+#             */
/*   Updated: 2021/10/21 19:48:12 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	finish;
	size_t	i;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	finish = 0;
	i = ft_strlen(s1) - 1;
	while (*s1 && ft_strchr(set, *s1))
	{
		s1++;
		start++;
	}
	while (i > 0 && ft_strchr(set, s1[i - start]))
	{
		finish++;
		i--;
	}
	dest = ft_substr(s1, 0, ft_strlen(s1) - finish);
	return (dest);
}
