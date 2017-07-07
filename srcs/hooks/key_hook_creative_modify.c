/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_creative_modify.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtiterin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 13:05:24 by vtiterin          #+#    #+#             */
/*   Updated: 2017/06/26 13:05:27 by vtiterin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	axis_modify(t_object *active, bool sign)
{
	if (active->complex)
	{
		if (!sign && active->complex->axis > 120)
			active->complex->axis -= 1;
		else if (sign && active->complex->axis < 122)
			active->complex->axis += 1;
	}
	else if (active)
	{
		if (!sign && active->axis > 120)
			active->axis -= 1;
		else if (sign && active->axis < 122)
			active->axis += 1;
	}
}

void	mode_modify(t_object *active, bool sign)
{
	if (active->complex)
	{
		if (!sign && active->complex->mode > 1)
			active->complex->mode -= 1;
		else if (sign && active->complex->mode < 3)
			active->complex->mode += 1;
	}
	else if (active)
	{
		if (!sign && active->mode > 1)
			active->mode -= 1;
		else if (sign && active->mode < 3)
			active->mode += 1;
	}
}
