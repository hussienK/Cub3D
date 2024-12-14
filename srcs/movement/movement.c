/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:13:07 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/17 21:27:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_table *d, double time_diff)
{
	if (d->data->map[(int)d->player->pos_y]
		[(int)(d->player->pos_x + d->player->dir_x * MOVE_SPEED * time_diff)]
			<= 0)
		d->player->pos_x += d->player->dir_x * MOVE_SPEED * time_diff;
	if (d->data->map[(int)(d->player->pos_y
			+ d->player->dir_y * MOVE_SPEED * time_diff)]
			[(int)d->player->pos_x] <= 0)
		d->player->pos_y += d->player->dir_y * MOVE_SPEED * time_diff;
}

void	move_backward(t_table *d, double time_diff)
{
	if (d->data->map[(int)d->player->pos_y]
		[(int)(d->player->pos_x - d->player->dir_x * MOVE_SPEED * time_diff)]
			<= 0)
		d->player->pos_x -= d->player->dir_x * MOVE_SPEED * time_diff;
	if (d->data->map[(int)(d->player->pos_y
			- d->player->dir_y * MOVE_SPEED * time_diff)]
			[(int)d->player->pos_x] <= 0)
		d->player->pos_y -= d->player->dir_y * MOVE_SPEED * time_diff;
}

void	move_right(t_table *d, double time_diff)
{
	double	perp_dir_x;
	double	perp_dir_y;

	perp_dir_x = -d->player->dir_y;
	perp_dir_y = d->player->dir_x;
	if (d->data->map[(int)d->player->pos_y]
		[(int)(d->player->pos_x - perp_dir_x * time_diff)] <= 0)
		d->player->pos_x -= perp_dir_x * MOVE_SPEED * time_diff;
	if (d->data->map[(int)(d->player->pos_y - perp_dir_y
			* MOVE_SPEED * time_diff)]
		[(int)d->player->pos_x] <= 0)
		d->player->pos_y -= perp_dir_y * MOVE_SPEED * time_diff;
}

void	move_left(t_table *d, double time_diff)
{
	double	perp_dir_x;
	double	perp_dir_y;

	perp_dir_x = -d->player->dir_y;
	perp_dir_y = d->player->dir_x;
	if (d->data->map[(int)d->player->pos_y]
		[(int)(d->player->pos_x + perp_dir_x * time_diff)] <= 0)
		d->player->pos_x += perp_dir_x * MOVE_SPEED * time_diff;
	if (d->data->map[(int)(d->player->pos_y + perp_dir_y
			* MOVE_SPEED * time_diff)]
		[(int)d->player->pos_x] <= 0)
		d->player->pos_y += perp_dir_y * MOVE_SPEED * time_diff;
}

void	move(t_table *d, double time_diff)
{
	if (d->player->moving_forward)
		move_forward(d, time_diff);
	else if (d->player->moving_back)
		move_backward(d, time_diff);
	if (d->player->moving_left)
		move_left(d, time_diff);
	else if (d->player->moving_right)
		move_right(d, time_diff);
}
