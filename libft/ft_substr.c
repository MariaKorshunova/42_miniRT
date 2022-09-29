/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:29:25 by jmabel            #+#    #+#             */
/*   Updated: 2021/10/24 15:39:38 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < (size_t)start)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - (size_t)start)
		len = ft_strlen(s) - (size_t)start;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < len)
		dest[i++] = s[(size_t)start++];
	dest[i] = '\0';
	return (dest);
}
