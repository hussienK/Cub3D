/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:57:10 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/18 14:27:51 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	helper for the other init
*/
void	init_player_plane(t_data *d, t_player *p)
{
	if (d->starting_orientation == 'N')
	{
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (d->starting_orientation == 'E')
	{
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (d->starting_orientation == 'S')
	{
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	else if (d->starting_orientation == 'W')
	{
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

/*
	sets the starting dir based on orientation
*/
void	init_player_dir(t_data *d, t_player *p)
{
	if (d->starting_orientation == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
	}
	else if (d->starting_orientation == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
	}
	else if (d->starting_orientation == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
	}
	else if (d->starting_orientation == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
	}
	init_player_plane(d, p);
}
