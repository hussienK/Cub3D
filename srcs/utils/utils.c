/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:47:07 by moassi            #+#    #+#             */
/*   Updated: 2024/07/17 13:41:46 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ll_len(t_input_ll *ll)
{
	t_input_ll	*cur;
	int			i;

	i = 0;
	cur = ll;
	while (cur)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

int	is_numeric(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	get_time_v(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec + (tv.tv_sec * 1e6));
}

void	uusleep(long usec)
{
	long	wakeup_time;

	wakeup_time = get_time_v() + usec;
	while (get_time_v() < wakeup_time)
		usleep(100);
}

void	put_fps(t_table *d, double time_diff)
{
	char	*fps;

	fps = ft_itoa(1.0 / time_diff);
	mlx_string_put(d->mlx_ptr, d->win_ptr, 20, 30, 0xFF0000, fps);
	mlx_string_put(d->mlx_ptr, d->win_ptr, 35, 30, 0xFF0000, "fps");
	free(fps);
}
