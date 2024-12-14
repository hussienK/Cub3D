/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:49:52 by moassi            #+#    #+#             */
/*   Updated: 2024/07/17 22:12:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	inits the player with starting vals	
*/
t_player	*init_player(t_data *d)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos_x = d->start_x + 0.5;
	player->pos_y = d->start_y + 0.5;
	init_player_dir(d, player);
	player->time = 0;
	player->old_time = 0;
	player->moving_back = false;
	player->moving_forward = false;
	player->moving_left = false;
	player->moving_right = false;
	player->rotating_left = false;
	player->rotating_right = false;
	player->mouse_left = false;
	player->mouse_right = false;
	return (player);
}

/*
	-initializes all game data like calculation vars and player
*/
t_table	*init_game_data(t_data *d)
{
	t_table		*table;
	t_calc_vars	*cv;

	cv = (t_calc_vars *)malloc(sizeof(t_calc_vars));
	if (!cv)
		return (NULL);
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->cv = cv;
	table->data = d;
	table->mlx_ptr = mlx_init();
	if (!table->mlx_ptr)
		return (free(table), NULL);
	table->win_ptr = NULL;
	table->player = NULL;
	table->minimap = NULL;
	(create_image(table), generate_textures(table));
	table->win_ptr = mlx_new_window(table->mlx_ptr, W, H, "CUB3D");
	if (!table->win_ptr)
		return (free(table->mlx_ptr), free(table), NULL);
	table->player = init_player(d);
	if (!table->player)
		return (free(table->mlx_ptr), free(table->win_ptr), free(table), NULL);
	return (gettimeofday(&(table->previous_time), NULL), table);
}

/*
	-calculates the frame rate
	-makes sure frame rate is capped at 60
*/
void	manage_frame_rate(struct timeval render_time,
	struct timeval current_time, t_table *d)
{
	double			time_diff;
	double			time_diff2;

	time_diff = (current_time.tv_sec - d->previous_time.tv_sec)
		+ (current_time.tv_usec - d->previous_time.tv_usec) / 1e6;
	time_diff2 = (render_time.tv_sec - current_time.tv_sec)
		+ (render_time.tv_usec - current_time.tv_usec) / 1e6;
	put_fps(d, time_diff);
	d->previous_time = current_time;
	rotate(d, time_diff);
	move(d, time_diff);
	mouse_move(d);
	open_doors(d);
	if (((1.0 / 60) - time_diff2) > 0)
		uusleep(((1.0 / 60) - time_diff2) * 1e6);
}

/*
	-calls the main render functions
	-calls the function to manage frame rates
*/
int	render(t_table *d)
{
	struct timeval	render_time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	render_ceiling_floor(d);
	render_walls(d);
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr,
		d->render_image->image, 0, 0);
	render_minimap(d);
	gettimeofday(&render_time, NULL);
	manage_frame_rate(render_time, current_time, d);
	return (0);
}

/*
	creates the main game structure and launches the game
*/
int	main(int argc, char *argv[])
{
	t_data	data;
	t_table	*table;
	int		y;

	if (!validate_input(argc, argv, &data))
		return (1);
	table = init_game_data(&data);
	init_minimap(table);
	if (!table)
		return (1);
	mlx_hook(table->win_ptr, DestroyNotify,
		StructureNotifyMask, &on_destroy, table);
	mlx_hook(table->win_ptr, KeyPress,
		KeyPressMask, &move_press, table);
	mlx_hook(table->win_ptr, KeyRelease,
		KeyReleaseMask, &move_unpress, table);
	mlx_loop_hook(table->mlx_ptr, &(render), table);
	mlx_mouse_get_pos(table->mlx_ptr, table->win_ptr, &(table->last_x), &y);
	mlx_mouse_hide(table->mlx_ptr, table->win_ptr);
	mlx_loop(table->mlx_ptr);
	return (free_textures(&data), free_intmap(&data, data.map_height), 0);
}
