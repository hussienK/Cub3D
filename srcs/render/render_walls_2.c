/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:50:15 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/19 09:05:32 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	- right of a screen will get coords 1, left -1 first
	- get which box of map player is on
	- get length of ray from current pos to next x or y
*/
int	render_walls(t_table *d)
{
	int	x;

	x = -1;
	while (++x < W)
	{
		d->cv->camera_x = 2 * x / (double)W - 1;
		d->cv->ray_dir_x = d->player->dir_x
			+ d->player->plane_x * d->cv->camera_x;
		d->cv->ray_dir_y = d->player->dir_y
			+ d->player->plane_y * d->cv->camera_x;
		d->cv->map_x = (int)d->player->pos_x;
		d->cv->map_y = (int)d->player->pos_y;
		if (d->cv->ray_dir_x == 0)
			d->cv->delta_dist_x = 1e30;
		else
			d->cv->delta_dist_x = fabs(1.0 / d->cv->ray_dir_x);
		if (d->cv->ray_dir_y == 0)
			d->cv->delta_dist_y = 1e30;
		else
			d->cv->delta_dist_y = fabs(1.0 / d->cv->ray_dir_y);
		render_walls_extra_calc(d, x);
	}
	return (0);
}

void	check_for_special(t_table *d)
{
	d->cv->is_door = false;
	d->cv->is_exit = false;
	if (d->data->map[d->cv->map_y][d->cv->map_x] == 5)
		d->cv->is_door = true;
	else if (d->data->map[d->cv->map_y][d->cv->map_x] == 4)
		d->cv->is_exit = true;
}

void	choose_texture(t_table *d)
{
	if (d->cv->side == 0)
	{
		if (d->cv->ray_dir_x > 0)
			d->cv->tex_num = EAST_INDEX;
		else
			d->cv->tex_num = WEST_INDEX;
	}
	else
	{
		if (d->cv->ray_dir_y > 0)
			d->cv->tex_num = SOUTH_INDEX;
		else
			d->cv->tex_num = NORTH_INDEX;
	}
	if (d->cv->is_door)
		d->cv->tex_num = DOOR_INDEX;
	else if (d->cv->is_exit)
		d->cv->tex_num = EXIT_INDEX;
}
