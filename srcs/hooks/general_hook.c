/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:31:42 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/07 12:48:49 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	exit_x(t_env *env)
{
	delete_environment(env);
	exit(1);
	return (0);
}
