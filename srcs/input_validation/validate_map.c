/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:29:54 by moassi            #+#    #+#             */
/*   Updated: 2024/07/19 09:07:15 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_row(int *row, t_input_ll *cur, int width)
{
	int	i;

	i = 0;
	while (i < width && cur->line[i])
	{
		if (cur->line[i] == ' ')
			row[i] = 9;
		else if (cur->line[i] == 'D')
			row[i] = 5;
		else if (cur->line[i] == 'F')
			row[i] = 4;
		else
			row[i] = cur->line[i] - '0';
		i++;
	}
	while (i < width)
	{
		row[i] = 9;
		i++;
	}
}

static int	fill_map(t_data *data, t_input_ll *m_ll)
{
	int			i;
	t_input_ll	*cur;

	i = 0;
	cur = m_ll;
	data->map = (int **)malloc(sizeof(int *) * (data->map_height + 1));
	if (!data->map)
		return (0);
	while (i < data->map_height)
	{
		data->map[i] = (int *)malloc(sizeof(int) * (data->map_width));
		fill_row(data->map[i], cur, data->map_width);
		cur = cur->next;
		i++;
	}
	data->map[i] = NULL;
	return (1);
}

static int	valid_borders(int **map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (map[i][j] == 0 && can_reach_out(map, data, i, j))
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static void	adjust_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (data->map[i][j] == 2)
			{
				data->map[i][j] = 0;
				data->start_x = j;
				data->start_y = i;
			}
			if (data->map[i][j] == 9)
				data->map[i][j] = 1;
			j++;
		}
		i++;
	}
}

int	validate_map(t_input_ll **m_ll, t_data *data)
{
	if (!check_map_chars(*m_ll, data))
		return (0);
	if (!fill_map(data, *m_ll) || !valid_borders(data->map, data))
		return (free_intmap(data, data->map_height), 0);
	if (!valid_doors(data) || !valid_exit(data))
		return (free_intmap(data, data->map_height), 0);
	adjust_map(data);
	return (1);
}
