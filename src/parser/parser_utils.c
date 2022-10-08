/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:57:56 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/08 18:22:55 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parser.h"

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
	if (exitcode == 12)
		ft_putstr_fd("Memory allocation error\n", STDERR_FILENO);
	else
		ft_putstr_fd("Error!\n", STDERR_FILENO);
	exit(exitcode);
}

static void	parser_skip_toanextnumber(t_scene *scene, char *s, int *i)
{
	while (s[*i] && ft_isdigit(s[*i]))
		(*i)++;
	if (s[*i] != ',')
		parser_error(scene, 1);
	(*i)++;
	parser_skipspaces(s, i);
	if (!ft_isdigit(s[*i]) && s[*i] != '-' && s[*i] != '+')
		parser_error(scene, 1);
}

int	parser_readcolor(t_scene *scene, char *s, int *i)
{
	int	res;

	res = (ft_atoi(s + *i)) << 8;
	if (ft_atoi(s + *i) > 255 || ft_atoi(s + *i) < 0)
		parser_error(scene, 1);
	parser_skip_toanextnumber(scene, s, i);
	res = (res + ft_atoi(s + *i)) << 8;
	if (ft_atoi(s + *i) > 255 || ft_atoi(s + *i) < 0)
		parser_error(scene, 1);
	parser_skip_toanextnumber(scene, s, i);
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
	parser_skip_toanextnumber(scene, s, i);
	res.y = parser_readfloat(scene, s, i);
	parser_skip_toanextnumber(scene, s, i);
	res.z = parser_readfloat(scene, s, i);
	return (res);
}
