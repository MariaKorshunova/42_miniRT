/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tips.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:24:03 by jmabel            #+#    #+#             */
/*   Updated: 2022/10/26 21:09:48 by bpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_tips(void)
{
	printf("\e[0;33mYou can change the scene in this ways:\n\e[0m");
	printf("\e[0;32mWASD: walking\n\e[0m");
	printf("\e[0;32mSelect object: \e[0mleft mose click\n");
	printf("\e[0;32mUnhook object: \e[0mright mose click\n");
	printf("\e[0;32mZoom object: \e[0mmouse wheel\n");
	printf("\e[0;32mSelect axis to change: \e[0m x, y, z buttons\n");
	printf("\e[0;32mTranslate object by the selected axis: \e[0m< > buttons\n");
	printf("\e[0;32mRotate object by the selected axis: \e[0m");
	printf("up and down arrays buttons\n");
	printf("\e[0;32mChange height cylinder: \e[0mh button, then < > buttons\n");
}
