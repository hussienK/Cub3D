/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:12:52 by hkanaan           #+#    #+#             */
/*   Updated: 2024/07/18 13:17:20 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	the logic for openning the textures
*/
void	get_texture(t_table *d, char *path, int index, t_img img)
{
	char	*raw_data;
	int		*int_data;
	int		x;
	int		y;

	img.image = mlx_xpm_file_to_image(d->mlx_ptr, path, &y, &x);
	if (!img.image)
		exit_with_message(d, "Error: failed to load textures\n");
	raw_data = mlx_get_data_addr(img.image, &img.bpp, &img.size_line,
			&img.format);
	int_data = (int *)raw_data;
	x = 0;
	while (x < TEX_W)
	{
		y = 0;
		while (y < TEX_H)
		{
			d->textures[index][TEX_H * y + x]
				= int_data[y * (img.size_line / 4) + x];
			y++;
		}
		x++;
	}
	mlx_destroy_image(d->mlx_ptr, img.image);
}

/*
	opens all the textures and loads them into their place
*/
void	generate_textures(t_table *d)
{
	t_img img = {0};

	get_texture(d, d->data->south_texture, SOUTH_INDEX, img);
	get_texture(d, d->data->east_texture, EAST_INDEX, img);
	get_texture(d, d->data->west_texture, WEST_INDEX, img);
	get_texture(d, d->data->north_texture, NORTH_INDEX, img);
	if (d->data->using_textures_f)
		get_texture(d, d->data->floor_texture, FLOOR_INDEX, img);
	if (d->data->using_textures_c)
		get_texture(d, d->data->ceiling_texture, CEILING_INDEX, img);
	get_texture(d, "./assets/door.xpm", DOOR_INDEX, img);
	get_texture(d, "./assets/exit.xpm", EXIT_INDEX, img);
}

/*
	creates the render image
*/
void	create_image(t_table *d)
{
	t_img	*image;

	image = (t_img *)malloc(sizeof(t_img));
	if (!image)
		return ;
	image->image = mlx_new_image(d->mlx_ptr, W, H);
	image->data = mlx_get_data_addr(image->image, &(image->bpp),
			&(image->size_line), &(image->format));
	d->render_image = image;
}
