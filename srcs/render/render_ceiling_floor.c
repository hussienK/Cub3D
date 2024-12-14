/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceiling_floor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:39:10 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/18 13:17:50 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	does the drawing of ceiling and floor to image
*/
void	draw_ceiling_floor_texture(t_table *d, int y)
{
	int	x;

	x = 0;
	while (x < W)
	{
		d->cv->cell_x = (int)d->cv->floor_x;
		d->cv->cell_y = (int)d->cv->floor_y;
		d->cv->tx = (int)(TEX_W * (d->cv->floor_x - d->cv->cell_x)) & (TEX_W - 1);
		d->cv->ty = (int)(TEX_W * (d->cv->floor_y - d->cv->cell_y)) & (TEX_W - 1);
		d->cv->floor_x += d->cv->floor_step_x;
		d->cv->floor_y += d->cv->floor_step_y;
		if (!d->data->using_textures_f)
			d->cv->color = (d->data->floor_color[0] << 16)
				| (d->data->floor_color[1] << 8) | d->data->floor_color[2];
		else
		{
			d->cv->color = d->textures[FLOOR_INDEX][TEX_W * d->cv->ty + d->cv->tx];
			d->cv->color = (d->cv->color >> 1) & 0x7F7F7F;
		}
		d->buffer[y][x] = d->cv->color;
		d->cv->pos = (y * d->render_image->size_line + x
				* (d->render_image->bpp / 8));
		*(unsigned int *)(d->render_image->data + d->cv->pos) = d->cv->color;
		if (d->data->using_textures_c == false)
			d->cv->color = (d->data->cieling_color[0] << 16)
				| (d->data->cieling_color[1] << 8) | d->data->cieling_color[2];
		else
		{
			d->cv->color = d->textures[CEILING_INDEX][TEX_W * d->cv->ty + d->cv->tx];
			d->cv->color = (d->cv->color >> 1) & 0x7F7F7F;
		}
		d->buffer[y][x] = d->cv->color;
		d->cv->pos = ((H - y - 1) * d->render_image->size_line + x
				* (d->render_image->bpp / 8));
		*(unsigned int *)(d->render_image->data + d->cv->pos) = d->cv->color;
		x++;
	}
}

/*
	does the drawing of ceiling and floor to image using textures
*/
void	draw_ceiling_floor_color(t_table *d, int y)
{
	int	x;

	x = 0;
	while (x < W)
	{
		d->cv->floor_x += d->cv->floor_step_x;
		d->cv->floor_y += d->cv->floor_step_y;

		d->buffer[y][x] = d->cv->color;
		d->cv->pos = (y * d->render_image->size_line + x
				* (d->render_image->bpp / 8));
		*(unsigned int *)(d->render_image->data + d->cv->pos) = d->cv->color;

		d->buffer[y][x] = d->cv->color;
		d->cv->pos = ((H - y - 1) * d->render_image->size_line + x
				* (d->render_image->bpp / 8));
		*(unsigned int *)(d->render_image->data + d->cv->pos) = d->cv->color;
		x++;
	}
}

/*
	does the nessecary calculations to draw ceiling and floor
*/
void	render_ceiling_floor(t_table *d)
{
	int		y;
	int		p;
	float	pos_z;

	y = 0;
	while (y < H)
	{
		d->cv->ray_dir_x0 = d->player->dir_x - d->player->plane_x;
		d->cv->ray_dir_y0 = d->player->dir_y - d->player->plane_y;
		d->cv->ray_dir_x1 = d->player->dir_x + d->player->plane_x;
		d->cv->ray_dir_y1 = d->player->dir_y + d->player->plane_y;
		p = y - H / 2;
		pos_z = 0.5 * H;
		d->cv->row_distance = pos_z / p;
		d->cv->floor_step_x = d->cv->row_distance
			* (d->cv->ray_dir_x1 - d->cv->ray_dir_x0) / W;
		d->cv->floor_step_y = d->cv->row_distance
			* (d->cv->ray_dir_y1 - d->cv->ray_dir_y0) / W;
		d->cv->floor_x = d->player->pos_x
			+ d->cv->row_distance * d->cv->ray_dir_x0;
		d->cv->floor_y = d->player->pos_y
			+ d->cv->row_distance * d->cv->ray_dir_y0;
		draw_ceiling_floor_texture(d, y);
		y++;
	}
}
