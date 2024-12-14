/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:08:13 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/17 17:05:14 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rot_left(t_table *d, double time_diff, int speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = d->player->dir_x;
	d->player->dir_x = d->player->dir_x * cos(-speed * time_diff)
		- d->player->dir_y * sin(-speed * time_diff);
	d->player->dir_y = old_dir_x * sin(-speed * time_diff)
		+ d->player->dir_y * cos(-speed * time_diff);
	old_plane_x = d->player->plane_x;
	d->player->plane_x = d->player->plane_x * cos(-speed * time_diff)
		- d->player->plane_y * sin(-speed * time_diff);
	d->player->plane_y = old_plane_x * sin(-speed * time_diff)
		+ d->player->plane_y * cos(-speed * time_diff);
}

void	rot_right(t_table *d, double time_diff, int speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = d->player->dir_x;
	d->player->dir_x = d->player->dir_x * cos(speed * time_diff)
		- d->player->dir_y * sin(speed * time_diff);
	d->player->dir_y = old_dir_x * sin(speed * time_diff)
		+ d->player->dir_y * cos(speed * time_diff);
	old_plane_x = d->player->plane_x;
	d->player->plane_x = d->player->plane_x * cos(speed * time_diff)
		- d->player->plane_y * sin(speed * time_diff);
	d->player->plane_y = old_plane_x * sin(speed * time_diff)
		+ d->player->plane_y * cos(speed * time_diff);
}

void	rotate(t_table *d, double time_diff)
{
	if (d->player->rotating_left)
		rot_left(d, time_diff, ROT_SPEED);
	else if (d->player->rotating_right)
		rot_right(d, time_diff, ROT_SPEED);
	else if (d->player->mouse_right)
		rot_right(d, time_diff, MOUSE_ROT_SPEED);
	else if (d->player->mouse_left)
		rot_left(d, time_diff, MOUSE_ROT_SPEED);
}
