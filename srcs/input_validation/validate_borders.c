/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_borders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:15:50 by moassi            #+#    #+#             */
/*   Updated: 2024/07/15 17:17:17 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_north(int **map, int i, int j)
{
	if (i == 0)
		return (0);
	i--;
	while (i >= 0 && map[i][j] != 1)
	{
		if (map[i][j] == 9)
			return (0);
		i--;
		if (i == -1)
			return (0);
	}
	return (1);
}

static int	check_south(int **map, t_data *data, int i, int j)
{
	if (i == data->map_height - 1)
		return (0);
	while (i < data->map_height && map[i][j] != 1)
	{
		if (map[i][j] == 9)
			return (0);
		i++;
		if (i == data->map_height)
			return (0);
	}
	return (1);
}

static int	check_west(int **map, int i, int j)
{
	if (j == 0)
		return (0);
	j--;
	while (j >= 0 && map[i][j] != 1)
	{
		if (map[i][j] == 9)
			return (0);
		j--;
		if (j == -1)
			return (0);
	}
	return (1);
}

static int	check_east(int **map, t_data *data, int i, int j)
{
	if (j == data->map_width - 1)
		return (0);
	while (j < data->map_width && map[i][j] != 1)
	{
		if (map[i][j] == 9)
			return (0);
		j++;
		if (j == data->map_width)
			return (0);
	}
	return (1);
}

int	can_reach_out(int **map, t_data *data, int i, int j)
{
	if (!check_north(map, i, j) || !check_south(map, data, i, j))
		return (1);
	if (!check_west(map, i, j) || !check_east(map, data, i, j))
		return (1);
	return (0);
}
