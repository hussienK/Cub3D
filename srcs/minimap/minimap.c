/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:04:14 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/19 09:22:55 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minimap(t_table *d)
{
	t_minimap	*map;
	int			x;

	map = (t_minimap *)malloc(sizeof(t_minimap));
	if (!map)
		return ;
	map->path_image = mlx_xpm_file_to_image(d->mlx_ptr,
			"./assets/fixed/path.xpm", &x, &x);
	map->solid_image = mlx_xpm_file_to_image(d->mlx_ptr,
			"./assets/fixed/solid.xpm", &x, &x);
	map->player_image = mlx_xpm_file_to_image(d->mlx_ptr,
			"./assets/fixed/player.xpm", &x, &x);
	map->border_image = mlx_xpm_file_to_image(d->mlx_ptr,
			"./assets/fixed/border.xpm", &x, &x);
	map->door_image = mlx_xpm_file_to_image(d->mlx_ptr,
			"./assets/fixed/door_minimap.xpm", &x, &x);
	map->exit_image = mlx_xpm_file_to_image(d->mlx_ptr,
			"./assets/fixed/exit_minimap.xpm", &x, &x);
	if (!map->solid_image || !map->path_image || !map->player_image
		|| !map->border_image || !map->door_image || !map->exit_image)
		exit_with_message(d, "Error: failed to load minimap texture\n");
	d->minimap = map;
}

void	draw_items(t_table *d, int j, int i, int nb)
{
	if (nb == 5)
	{
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr,
			d->minimap->door_image, W - 160 + (i * 10), 10 + (j * 10));
	}
	else if (nb == 4)
	{
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr,
			d->minimap->exit_image, W - 160 + (i * 10), 10 + (j * 10));
	}
	else if (nb > 0)
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr,
			d->minimap->solid_image, W - 160 + (i * 10), 10 + (j * 10));
	else
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr,
			d->minimap->path_image, W - 160 + (i * 10), 10 + (j * 10));
}

void	put_to_screen(t_table *d, int y, int j, int i)
{
	int	x;

	x = (int)d->player->pos_x - 7;
	while (x <= (int)d->player->pos_x + 7)
	{
		if (x < 0 || y < 0 || x >= d->data->map_width
			|| y >= d->data->map_height)
			mlx_put_image_to_window(d->mlx_ptr, d->win_ptr,
				d->minimap->solid_image, W - 160 + (i * 10), 10 + (j * 10));
		else if (x == (int)d->player->pos_x && y == (int)d->player->pos_y)
			mlx_put_image_to_window(d->mlx_ptr, d->win_ptr,
				d->minimap->player_image, W - 160 + (i * 10), 10 + (j * 10));
		else
			draw_items(d, j, i, d->data->map[y][x]);
		i++;
		x++;
	}
}

void	put_borders(t_table	*d)
{
	int	i;
	int	j;

	j = -1;
	while (j <= 15)
	{
		i = -1;
		while (i <= 15)
		{
			if (i == -1 || j == -1 || i == 15 || j == 15)
				mlx_put_image_to_window(d->mlx_ptr, d->win_ptr,
					d->minimap->border_image,
					W - 160 + (i * 10), 10 + (j * 10));
			i++;
		}
		j++;
	}
}

void	render_minimap(t_table *d)
{
	int	y;
	int	i;
	int	j;

	y = (int)d->player->pos_y - 7;
	j = 0;
	while (y <= (int)d->player->pos_y + 7)
	{
		i = 0;
		put_to_screen(d, y, j, i);
		j++;
		y++;
	}
	put_borders(d);
}
