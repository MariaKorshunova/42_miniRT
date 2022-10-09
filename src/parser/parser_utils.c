/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 04:57:56 by bpoetess          #+#    #+#             */
/*   Updated: 2022/10/09 18:50:49 by bpoetess         ###   ########.fr       */
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

void	parser_error(int exitcode, t_parser *p)
{
	if (p && p->scene)
		free_scene(p->scene);
	if (p && p->file_fd != -1)
		close(p->file_fd);
	if (exitcode == 12)
		ft_putstr_fd("Memory allocation error\n", STDERR_FILENO);
	else
		ft_putstr_fd("Error!\n", STDERR_FILENO);
	exit(exitcode);
}

static void	parser_skip_toanextnumber(t_parser *p)
{
	while (p->s[p->i] && ft_isdigit(p->s[p->i]))
		(p->i)++;
	if (p->s[p->i] != ',')
		parser_error(1, p);
	(p->i)++;
	parser_skipspaces(p->s, &(p->i));
	if (!ft_isdigit(p->s[p->i]) && p->s[p->i] != '-' && p->s[p->i] != '+')
		parser_error(1, p);
}

int	parser_readcolor(t_parser *p)
{
	int	res;

	res = (ft_atoi(p->s + p->i)) << 8;
	if (ft_atoi(p->s + p->i) > 255 || ft_atoi(p->s + p->i) < 0)
		parser_error(1, p);
	parser_skip_toanextnumber(p);
	res = (res + ft_atoi(p->s + p->i)) << 8;
	if (ft_atoi(p->s + p->i) > 255 || ft_atoi(p->s + p->i) < 0)
		parser_error(1, p);
	parser_skip_toanextnumber(p);
	res = (res + ft_atoi(p->s + p->i)) << 8;
	if (ft_atoi(p->s + p->i) > 255 || ft_atoi(p->s + p->i) < 0)
		parser_error(1, p);
	while (p->s[p->i] && ft_isdigit(p->s[p->i]))
		(p->i)++;
	return (res);
}

t_coord	parser_readcoord(t_parser *p)
{
	t_coord	res;

	res.x = parser_readfloat (p);
	parser_skip_toanextnumber(p);
	res.y = parser_readfloat (p);
	parser_skip_toanextnumber(p);
	res.z = parser_readfloat (p);
	return (res);
}
