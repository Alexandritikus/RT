/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:54:28 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/13 12:31:54 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_usage(char *binary)
{
	ft_putstr(RED_PRINT_ON);
	ft_putstr("usage: ");
	ft_putstr(binary);
	ft_putendl(" [hd | fhd]");
	ft_putstr("using ");
	ft_putstr(binary);
	ft_putendl(" without flags you choose HD resolution [1280 x 720]");
	ft_putstr(COLOR_PRINT_OFF);
}
