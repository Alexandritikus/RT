/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshudria <oshudria@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 10:41:22 by oshudria          #+#    #+#             */
/*   Updated: 2017/06/15 14:26:29 by oshudria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	print_counts(int num)
{
	int	i;

	i = 0;
	while (num)
	{
		ft_putchar('=');
		num--;
		i++;
	}
	if (i < 100)
	{
		ft_putchar('>');
		i++;
	}
	while (i < 100)
	{
		ft_putchar('.');
		i++;
	}
}

static void	print_progress_bar(int status)
{
	ft_putstr(YELLOW_PRINT_ON);
	ft_putchar('[');
	print_counts(status);
	ft_putstr("] ");
	ft_putnbr(status);
	ft_putstr(" %");
	ft_putchar('\r');
	fflush(stdout);
	ft_putstr(COLOR_PRINT_OFF);
}

void		whaiting_message(void)
{
	ft_putstr(PURPLE_PRINT_ON);
	ft_putendl("Please whait for a moment...");
	ft_putstr(COLOR_PRINT_OFF);
}

void		thread_progress_count(int n, int *thread_progress)
{
	if (n > *thread_progress)
		*thread_progress = n;
}

void		*progress_bar(void *param)
{
	static int	progress_status = 0;
	t_env		*env;
	int			max_lines;
	int			progress;

	env = (t_env*)param;
	max_lines = env->sh / N_THREAD;
	while (env->thread_progress <= max_lines)
	{
		if (progress_status < env->thread_progress)
		{
			progress_status = env->thread_progress;
			progress = 100 * env->thread_progress / max_lines;
			print_progress_bar(progress);
		}
		if (progress == 100)
		{
			progress_status = 0;
			break ;
		}
	}
	ft_putchar('\n');
	return (NULL);
}
