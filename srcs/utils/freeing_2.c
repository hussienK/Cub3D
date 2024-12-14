/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:27:50 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/17 16:31:24 by hkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_destroy(t_table *table)
{
	free_minimap(table);
	mlx_destroy_image(table->mlx_ptr, table->render_image->image);
	mlx_destroy_window(table->mlx_ptr, table->win_ptr);
	mlx_destroy_display(table->mlx_ptr);
	free(table->mlx_ptr);
	free(table->player);
	free_textures(table->data);
	free_intmap(table->data, table->data->map_height);
	free(table->cv);
	free(table->render_image);
	free(table);
	exit(0);
	return (0);
}
