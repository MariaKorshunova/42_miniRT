/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_readfloat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:05:06 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/20 16:39:27 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parser.h"

void	parser_skipspacesifnotspaceerror(t_parser *p)
{
	if (!ft_isspace(p->s[p->i]))
		parser_error(1, p);
	parser_skipspaces(p->s, &(p->i));
}

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

static int	parser_readfloat_getsign(t_parser *p)
{
	int	res;

	if (p->s[p->i] == '-')
		res = -1;
	else
		res = 1;
	if (p->s[p->i] == '-' || p->s[p->i] == '+')
		(p->i)++;
	return (res);
}

float	parser_readfloat(t_parser *p)
{
	float	res;
	float	tmp1;
	int		sign;

	if (!(ft_isdigit(p->s[p->i]) || ((p->s[p->i] == '-' || p->s[p->i] == '+')
				&& ft_isdigit(p->s[p->i + 1]))))
		parser_error(1, p);
	res = (float) ft_atoi(p->s + (p->i));
	sign = parser_readfloat_getsign(p);
	while (p->s[p->i] && ft_isdigit(p->s[p->i]))
		(p->i)++;
	if (p->s[p->i] != '.')
		return (res);
	else if (p->s[p->i] == '.' && !ft_isdigit(p->s[(p->i) + 1]))
		parser_error(1, p);
	(p->i)++;
	tmp1 = parser_readfloat_getfractionalpart(p->s, p->i);
	while (p->s[p->i] && ft_isdigit(p->s[p->i]))
		(p->i)++;
	if (sign == 1)
		return (res + tmp1);
	return (res - tmp1);
}
