/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:40:03 by moassi            #+#    #+#             */
/*   Updated: 2024/07/18 14:33:11 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_char_matrix(char **mat)
{
	int	i;

	if (!mat)
		return ;
	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}

void	free_ll(t_input_ll **ll)
{
	if (ll == NULL || *ll == NULL)
		return ;
	while ((*ll)->next)
		free_ll(&((*ll)->next));
	free((*ll)->line);
	(*ll)->line = NULL;
	free(*ll);
	*ll = NULL;
}

void	free_textures(t_data *data)
{
	free(data->north_texture);
	free(data->south_texture);
	free(data->east_texture);
	free(data->west_texture);
	if (data->floor_texture)
		free(data->floor_texture);
	if (data->ceiling_texture)
		free(data->ceiling_texture);
}

void	free_intmap(t_data *data, int l)
{
	int	i;

	if (!data->map)
		return ;
	i = -1;
	while (++i < l)
		free(data->map[i]);
	free(data->map);
}

void	free_minimap(t_table *d)
{
	if (!d)
		return ;
	if (!d->minimap)
		return ;
	if (d->minimap->path_image)
		mlx_destroy_image(d->mlx_ptr, d->minimap->path_image);
	if (d->minimap->solid_image)
		mlx_destroy_image(d->mlx_ptr, d->minimap->solid_image);
	if (d->minimap->player_image)
		mlx_destroy_image(d->mlx_ptr, d->minimap->player_image);
	if (d->minimap->border_image)
		mlx_destroy_image(d->mlx_ptr, d->minimap->border_image);
	if (d->minimap->exit_image)
		mlx_destroy_image(d->mlx_ptr, d->minimap->exit_image);
	if (d->minimap->door_image)
		mlx_destroy_image(d->mlx_ptr, d->minimap->door_image);
	if (d->minimap)
		free(d->minimap);
}
