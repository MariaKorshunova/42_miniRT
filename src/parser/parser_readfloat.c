/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readfloat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:05:06 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/06 20:10:06 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parser.h"

static float	parser_readfloat_getfractionalpart(char *s, int i)
{
	float	nb;
	int		tmp;

	tmp = 0;
	nb = 0;
	while (tmp < 6 && s[i] >= '0' && s[i] <= '9')
	{
		nb = 10 * nb + s[i++] - '0';
		tmp ++;
	}
	while (tmp)
	{
		nb /= 10;
		tmp --;
	}
	return (nb);
}

float	parser_readfloat(t_scene *scene, char *s, int *i)
{
	float	res;
	float	tmp1;

	if (!(ft_isdigit(s[*i]) || ((s[*i] == '-' || s[*i] == '+')
				&& ft_isdigit(s[*i + 1]))))
		parser_error(scene, 1);
	res = (float) ft_atoi(s + (*i));
	if (s[*i] == '-' || s[*i] == '+')
		(*i)++;
	while (s[*i] && ft_isdigit(s[*i]))
		(*i)++;
	if (s[*i] != '.')
		return (res);
	else if (s[*i] == '.' && !ft_isdigit(s[(*i) + 1]))
		parser_error(scene, 1);
	(*i)++;
	tmp1 = parser_readfloat_getfractionalpart(s, *i);
	while (s[*i] && ft_isdigit(s[*i]))
		(*i)++;
	if (res >= 0)
		return (res + tmp1);
	return (res - tmp1);
}
