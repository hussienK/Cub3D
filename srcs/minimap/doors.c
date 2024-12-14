/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:08:15 by marvin            #+#    #+#             */
/*   Updated: 2024/07/17 21:08:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	win_door(t_table *d)
{
	int	x;
	int	y;

	x = (int)d->player->pos_x;
	y = (int)d->player->pos_y;
	if (d->data->map[y][x] == -2)
	{
		printf("YOU WON!\n");
		on_destroy(d);
	}
}

void	close_doors(t_table *d)
{
	int	i;
	int	j;

	j = (int)d->player->pos_y - 4;
	while (j <= (int)d->player->pos_y + 4)
	{
		i = (int)d->player->pos_x - 4;
		while (i <= (int)d->player->pos_x + 4)
		{
			if (i < 0 || j < 0 || i >= d->data->map_width
				|| j >= d->data->map_height)
			{
				i++;
				continue ;
			}
			if (d->data->map[j][i] == -1)
				d->data->map[j][i] = 5;
			else if (d->data->map[j][i] == -2)
				d->data->map[j][i] = 4;
			i++;
		}
		j++;
	}
}

void	open_doors(t_table *d)
{
	int	i;
	int	j;

	close_doors(d);
	j = (int)d->player->pos_y - 2;
	while (j <= (int)d->player->pos_y + 2)
	{
		i = (int)d->player->pos_x - 2;
		while (i <= (int)d->player->pos_x + 2)
		{
			if (i < 0 || j < 0 || i >= d->data->map_width
				|| j >= d->data->map_height)
			{
				i++;
				continue ;
			}
			if (d->data->map[j][i] == 5)
				d->data->map[j][i] = -1;
			else if (d->data->map[j][i] == 4)
				d->data->map[j][i] = -2;
			i++;
		}
		j++;
	}
	win_door(d);
}
