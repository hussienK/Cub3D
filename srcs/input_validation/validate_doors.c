/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_doors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:06:56 by moassi            #+#    #+#             */
/*   Updated: 2024/07/19 09:10:31 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_doors(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (data->map[i][j] == 5)
			{
				if (!((data->map[i - 1][j] == 1 && data->map[i + 1][j] == 1
					&& data->map[i][j + 1] == 0 && data->map[i][j - 1] == 0)
					|| (data->map[i - 1][j] == 0 && data->map[i + 1][j] == 0
					&& data->map[i][j + 1] == 1 && data->map[i][j - 1] == 1)))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	valid_exit(t_data *data)
{
	int	i;
	int	j;
	int	zeros;

	i = 0;
	zeros = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (data->map[i][j] == 4 && data->map[i][j + 1] == 0)
				zeros++;
			if (data->map[i][j] == 4 && data->map[i][j - 1] == 0)
				zeros++;
			if (data->map[i][j] == 4 && data->map[i + 1][j] == 0)
				zeros++;
			if (data->map[i][j] == 4 && data->map[i - 1][j] == 0)
				zeros++;
			j++;
		}
		i++;
	}
	return (zeros == 1);
}
