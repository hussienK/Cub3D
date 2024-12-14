/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:16:57 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/17 21:42:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	draws the textures to the image
*/
void	do_drawing(t_table *d, int x)
{
	int	y;

	y = d->cv->draw_start;
	while (y <= d->cv->draw_end)
	{
		d->cv->tex_y = (int)d->cv->tex_pos & (TEX_H - 1);
		d->cv->tex_pos += d->cv->step;
		d->cv->color = d->textures[d->cv->tex_num]
		[TEX_H * d->cv->tex_y + d->cv->tex_x];
		if (d->cv->side == 1)
			d->cv->color = (d->cv->color >> 1) & 0x7F7F7F;
		d->buffer[y][x] = d->cv->color;
		d->cv->pos = (y * d->render_image->size_line + x
				* (d->render_image->bpp / 8));
		*(unsigned int *)(d->render_image->data + d->cv->pos) = d->buffer[y][x];
		y++;
	}
}

/*
	calcualtes the vars needed to put the textures
*/
void	calc_texture_vars(t_table *d, int x)
{
	if (d->cv->side == 0)
		d->cv->wall_x = d->player->pos_y + d->cv->perp_wall_dist
			* d->cv->ray_dir_y;
	else
		d->cv->wall_x = d->player->pos_x + d->cv->perp_wall_dist
			* d->cv->ray_dir_x;
	d->cv->wall_x -= floor((d->cv->wall_x));
	d->cv->tex_x = (int)(d->cv->wall_x * (double)TEX_W);
	if (d->cv->side == 0 && d->cv->ray_dir_x > 0)
		d->cv->tex_x = TEX_W - d->cv->tex_x - 1;
	if (d->cv->side == 1 && d->cv->ray_dir_y)
		d->cv->tex_x = TEX_W - d->cv->tex_x - 1;
	d->cv->step = 1.0 * TEX_W / d->cv->line_height;
	d->cv->tex_pos = (d->cv->draw_start - H / 2 + d->cv->line_height / 2)
		* d->cv->step;
	do_drawing(d, x);
}

/*
	-calculates the ray start and end
	-calculates correct texture index
*/
void	calc_draw_vars(t_table *d, int x)
{
	d->cv->line_height = (int)(H / d->cv->perp_wall_dist);
	d->cv->draw_start = -d->cv->line_height / 2 + H / 2;
	if (d->cv->draw_start < 0)
		d->cv->draw_start = 0;
	d->cv->draw_end = d->cv->line_height / 2 + H / 2;
	if (d->cv->draw_end >= H)
		d->cv->draw_end = H - 1;
	choose_texture(d);
	calc_texture_vars(d, x);
}

/*
	jumps to next map square, either in x-direction, or in y-direction
	and checks if a wall is hit
*/
void	do_dda(t_table *d, int x)
{
	d->cv->hit = 0;
	while (d->cv->hit == 0)
	{
		if (d->cv->side_dist_x < d->cv->side_dist_y)
		{
			d->cv->side_dist_x += d->cv->delta_dist_x;
			d->cv->map_x += d->cv->step_x;
			d->cv->side = 0;
		}
		else
		{
			d->cv->side_dist_y += d->cv->delta_dist_y;
			d->cv->map_y += d->cv->step_y;
			d->cv->side = 1;
		}
		if (d->data->map[d->cv->map_y][d->cv->map_x] > 0)
			d->cv->hit = 1;
		check_for_special(d);
	}
	if (d->cv->side == 0)
		d->cv->perp_wall_dist = d->cv->side_dist_x - d->cv->delta_dist_x;
	else
		d->cv->perp_wall_dist = d->cv->side_dist_y - d->cv->delta_dist_y;
	calc_draw_vars(d, x);
}

/*
	-calculate the step and initial steps
*/
void	render_walls_extra_calc(t_table *d, int x)
{
	if (d->cv->ray_dir_x < 0)
	{
		d->cv->step_x = -1;
		d->cv->side_dist_x = (d->player->pos_x - d->cv->map_x)
			* d->cv->delta_dist_x;
	}
	else
	{
		d->cv->step_x = 1;
		d->cv->side_dist_x = (d->cv->map_x + 1.0 - d->player->pos_x)
			* d->cv->delta_dist_x;
	}
	if (d->cv->ray_dir_y < 0)
	{
		d->cv->step_y = -1;
		d->cv->side_dist_y = (d->player->pos_y - d->cv->map_y)
			* d->cv->delta_dist_y;
	}
	else
	{
		d->cv->step_y = 1;
		d->cv->side_dist_y = (d->cv->map_y + 1.0 - d->player->pos_y)
			* d->cv->delta_dist_y;
	}
	do_dda(d, x);
}
