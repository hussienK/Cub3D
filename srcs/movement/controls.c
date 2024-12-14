/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:08:57 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/18 14:31:17 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	change game based on keyboard actions
*/
int	move_unpress(int keypress, t_table *table)
{
	if (keypress == 119)
		table->player->moving_forward = false;
	else if (keypress == 115)
		table->player->moving_back = false;
	if (keypress == 97)
		table->player->moving_right = false;
	else if (keypress == 100)
		table->player->moving_left = false;
	if (keypress == 65363)
		table->player->rotating_right = false;
	else if (keypress == 65361)
		table->player->rotating_left = false;
	return (0);
}

/*
	change game based on keyboard actions
*/
int	move_press(int keypress, t_table *table)
{
	if (keypress == 65307)
		on_destroy(table);
	if (keypress == 119)
		table->player->moving_forward = true;
	else if (keypress == 115)
		table->player->moving_back = true;
	if (keypress == 97)
		table->player->moving_right = true;
	else if (keypress == 100)
		table->player->moving_left = true;
	if (keypress == 65363)
		table->player->rotating_right = true;
	else if (keypress == 65361)
		table->player->rotating_left = true;
	return (0);
}

/*
	moves the view based on mouse positions
*/
int	mouse_move(t_table *d)
{
	int	x;
	int	y;
	int	delta_x;

	mlx_mouse_get_pos(d->mlx_ptr, d->win_ptr, &x, &y);
	delta_x = x - d->last_x;
	d->player->mouse_left = false;
	d->player->mouse_right = false;
	if (delta_x > 0)
		d->player->mouse_right = true;
	else if (delta_x < 0)
		d->player->mouse_left = true;
	else
	{
		mlx_mouse_move(d->mlx_ptr, d->win_ptr, W / 2, H / 2);
		mlx_mouse_get_pos(d->mlx_ptr, d->win_ptr, &x, &y);
	}
	d->last_x = x;
	return (0);
}
