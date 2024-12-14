/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:11:53 by moassi            #+#    #+#             */
/*   Updated: 2024/07/19 09:15:20 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_color(char	**rgb, char c, t_data *data, int identifiers[6])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!is_numeric(rgb[i]))
			return (0);
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (0);
		if (c == 'F')
		{
			data->floor_color[i] = ft_atoi(rgb[i]);
			identifiers[4] = 1;
		}
		else if (c == 'C')
		{
			data->cieling_color[i] = ft_atoi(rgb[i]);
			identifiers[5] = 1;
		}
		i++;
	}
	return (1);
}

static int	is_direction_texture(char **split, t_data *data, int identifiers[6])
{
	if (!ft_strcmp("NO", split[0]) && !data->north_texture)
	{
		identifiers[0] = 1;
		data->north_texture = ft_strdup(split[1]);
		return (1);
	}
	else if (!ft_strcmp("SO", split[0]) && !data->south_texture)
	{
		identifiers[1] = 1;
		data->south_texture = ft_strdup(split[1]);
		return (1);
	}
	else if (!ft_strcmp("WE", split[0]) && !data->west_texture)
	{
		identifiers[2] = 1;
		data->west_texture = ft_strdup(split[1]);
		return (1);
	}
	else if (!ft_strcmp("EA", split[0]) && !data->east_texture)
	{
		identifiers[3] = 1;
		data->east_texture = ft_strdup(split[1]);
		return (1);
	}
	return (0);
}

static int	is_color_identifier(char **split, t_data *data, int identifiers[6])
{
	char	**rgb;

	rgb = ft_split(split[1], ',');
	if ((!ft_strcmp("C", split[0]) || !ft_strcmp("F", split[0]))
		&& (rgb[0] && rgb[1] && rgb[2] && !rgb[3]))
	{
		if (!is_valid_color(rgb, split[0][0], data, identifiers))
			return (free_char_matrix(rgb), 0);
		return (free_char_matrix(rgb), 1);
	}
	else if (!ft_strcmp("C", split[0]) && !data->ceiling_texture)
	{
		identifiers[5] = 1;
		data->using_textures_c = true;
		data->ceiling_texture = ft_strdup(split[1]);
		return (free_char_matrix(rgb), 1);
	}
	else if (!ft_strcmp("F", split[0]) && !data->floor_texture)
	{
		identifiers[4] = 1;
		data->using_textures_f = true;
		data->floor_texture = ft_strdup(split[1]);
		return (free_char_matrix(rgb), 1);
	}
	return (free_char_matrix(rgb), 0);
}

int	extract(char **split, t_data *data, int identifiers[6])
{
	if (is_direction_texture(split, data, identifiers))
		return (1);
	else if (is_color_identifier(split, data, identifiers))
	{
		return (1);
	}
	return (0);
}

int	validate_texture(t_input_ll **t_ll, t_data *data)
{
	int			i;
	char		**split;
	t_input_ll	*cur;
	int			identifiers[6];

	i = -1;
	while (++i < 6)
		identifiers[i] = 0;
	if (ll_len(*t_ll) < 6)
		return (0);
	i = -1;
	cur = *t_ll;
	while (++i < 6)
	{
		split = ft_split(cur->line, ' ');
		if (!(split[1] && !split[2] && extract(split, data, identifiers)))
			return (free_textures(data), free_char_matrix(split), 0);
		free_char_matrix(split);
		cur = cur->next;
	}
	i = -1;
	while (++i < 6)
		if (identifiers[i] != 1)
			return (free_textures(data), 0);
	return (1);
}
