/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:58:38 by moassi            #+#    #+#             */
/*   Updated: 2024/07/18 12:48:32 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_cub_extension(char *file)
{
	char	*str;

	str = ft_strchr(file, '.');
	if (!str)
		return (0);
	return (!ft_strcmp(".cub", str));
}

int	validate_map_and_texture(t_input_ll **t_ll, t_input_ll **m_ll, t_data *data)
{
	if (!validate_texture(t_ll, data))
		return (free_ll(t_ll), free_ll(m_ll), 0);
	if (!validate_map(m_ll, data))
		return (free_textures(data), free_ll(t_ll), free_ll(m_ll), 0);
	return (1);
}

int	validate_input(int ac, char **av, t_data *data)
{
	t_input_ll	*texture_ll;
	t_input_ll	*map_ll;
	int			fd;

	data->east_texture = NULL;
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->west_texture = NULL;
	data->ceiling_texture = NULL;
	data->floor_texture = NULL;
	data->using_textures_c = false;
	data->using_textures_f = false;
	texture_ll = NULL;
	map_ll = NULL;
	if (ac != 2 || !is_cub_extension(av[1]))
		return (err(BADARGUMENTS, 0));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (err(MAPNOTFOUND, 0));
	parse_textures(fd, &texture_ll);
	parse_map(fd, &map_ll, data);
	if (!validate_map_and_texture(&texture_ll, &map_ll, data))
		return (err(INVALIDMAP, 0));
	return (free_ll(&texture_ll), free_ll(&map_ll), 1);
}
