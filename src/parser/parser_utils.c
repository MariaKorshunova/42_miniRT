/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:57:56 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/05 08:01:18 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	parser_skipspaces(char *s, int *i)
{
	if (!s || !i)
		exit (1);
	if (!s[*i])
		return ;
	while (s[*i] && (s[*i] == '\t' || s[*i] == ' ' || s[*i] == '\n'
			|| s[*i] == '\v' || s[*i] == '\f' || s[*i] == '\r'))
		(*i)++;
}

void	parser_error(t_scene *scene, int exitcode)
{
	free_scene(scene);
	printf("Error!\n");
	exit(exitcode);
}

float	parser_readfloat(t_scene *scene, char *s, int *i)
{
	float	res;
	float	tmp1;
	float	tmp2;

	if (!ft_isdigit(s[*i]) && s[*i] != '-')
		parser_error(scene, 1);
	res = (float) ft_atoi(s + (*i));
	while (s[*i] && ft_isdigit(s[*i]))
		(*i)++;
	if (s[*i] != '.' && !ft_isdigit(s[(*i) + 1]))
		return (res);
	else if (s[*i] == '.' && !ft_isdigit(s[(*i) + 1]))
		parser_error(scene, 1);
	(*i)++;
	tmp1 = ft_atoi(s + (*i));
	tmp2 = 1;
	while ((int)(tmp1 / tmp2))
		tmp2 *= 10;
	while (s[*i] && ft_isdigit(s[*i]))
		(*i)++;
	return (res + (tmp1 / tmp2));
}

int	parser_readcolor(t_scene *scene, char *s, int *i)
{
	int	res;

	res = (ft_atoi(s + *i)) << 8;
	if (ft_atoi(s + *i) > 255 || ft_atoi(s + *i) < 0)
		parser_error(scene, 1);
	while (s[*i] && ft_isdigit(s[*i]))
		(*i)++;
	if (s[*i] != ',' || !ft_isdigit(s[(*i) + 1]))
		parser_error(scene, 1);
	(*i)++;
	res = (res + ft_atoi(s + *i)) << 8;
	if (ft_atoi(s + *i) > 255 || ft_atoi(s + *i) < 0)
		parser_error(scene, 1);
	while (s[*i] && ft_isdigit(s[*i]))
		(*i)++;
	if (s[*i] != ',' || !ft_isdigit(s[(*i) + 1]))
		parser_error(scene, 1);
	(*i)++;
	res = (res + ft_atoi(s + *i)) << 8;
	if (ft_atoi(s + *i) > 255 || ft_atoi(s + *i) < 0)
		parser_error(scene, 1);
	while (s[*i] && ft_isdigit(s[*i]))
		(*i)++;
	return (res);
}

t_coord	parser_readcoord(t_scene *scene, char *s, int *i)
{
	t_coord	res;

	res.x = parser_readfloat(scene, s, i);
	if (s[*i] != ',' || !ft_isdigit(s[(*i) + 1]))
		parser_error(scene, 1);
	(*i)++;
	res.y = parser_readfloat(scene, s, i);
	if (s[*i] != ',' || !ft_isdigit(s[(*i) + 1]))
		parser_error(scene, 1);
	(*i)++;
	res.z = parser_readfloat(scene, s, i);
	return (res);
}
