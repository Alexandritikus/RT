/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bar_button.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 13:22:08 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/19 10:59:35 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define WIDTH 150
#define HEIGHT 50

int	home_button(int x, int y, int start)
{
	if (x > start && x < (start + WIDTH))
	{
		if (y > 0 && y < HEIGHT)
			return (1);
	}
	return (0);
}

int	scene_list_button(int x, int y, int start)
{
	if (x > (start + WIDTH) && x < (start + WIDTH * 2))
	{
		if (y > 0 && y < HEIGHT)
			return (1);
	}
	return (0);
}
