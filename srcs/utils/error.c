/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:57:49 by moassi            #+#    #+#             */
/*   Updated: 2024/07/17 20:09:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	prints a custom error message
*/
int	err(t_error_msgs type, int ret)
{
	if (type == BADARGUMENTS)
		ft_printf("Error\ninvalid arguments\n");
	else if (type == MAPNOTFOUND)
		ft_printf("Error\ncannot find or open .cub file\n");
	else if (type == INVALIDMAP)
		ft_printf("Error\ninvalid map\n");
	return (ret);
}

/*
	exits cleanly while displaying an error message
*/
void	exit_with_message(t_table *table, char *str)
{
	ft_putstr_fd(str, 2);
	free_minimap(table);
	if (table->render_image && table->render_image->image)
		mlx_destroy_image(table->mlx_ptr, table->render_image->image);
	if (table->render_image)
		free(table->render_image);
	if (table->win_ptr)
		mlx_destroy_window(table->mlx_ptr, table->win_ptr);
	if (table->mlx_ptr)
	{
		mlx_destroy_display(table->mlx_ptr);
		free(table->mlx_ptr);
	}
	if (table->player)
		free(table->player);
	free_textures(table->data);
	free_intmap(table->data, table->data->map_height);
	free(table->cv);
	free(table);
	exit (1);
}
