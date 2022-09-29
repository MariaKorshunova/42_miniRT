/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 20:24:31 by jmabel            #+#    #+#             */
/*   Updated: 2021/10/24 11:31:32 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_intlen(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n >= 10)
	{
		len++;
		n = n / 10;
	}
	return (len + 1);
}

static	char	*ft_itoa_record(long n, int len, char *str)
{
	int	finish;
	int	i;

	finish = 0;
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
		finish = 1;
	}
	i = len - 1;
	while (i >= finish)
	{
		str[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	str[len] = '\0';
	return (str);
}

char	*ft_itoa(int nb)
{
	char	*str;
	long	n;
	int		len;

	n = nb;
	len = ft_intlen(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str = ft_itoa_record(n, len, str);
	return (str);
}
