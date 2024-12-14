/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:31:56 by moassi            #+#    #+#             */
/*   Updated: 2024/07/19 09:04:36 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	no_orientation(int o_c[6])
{
	if (o_c[0] == 0 && o_c[1] == 0 && o_c[2] == 0 && o_c [3] == 0)
		return (1);
	return (0);
}

static void	init_oc_dc(int o_c[6])
{
	o_c[0] = 0;
	o_c[1] = 0;
	o_c[2] = 0;
	o_c[3] = 0;
	o_c[4] = 0;
	o_c[5] = 0;
}

static int	is_orientation(char c, int o_c[6], t_data *data)
{
	if (c == 'N' && no_orientation(o_c))
	{
		data->starting_orientation = c;
		o_c[0]++;
		return (1);
	}
	else if (c == 'S' && no_orientation(o_c))
	{
		data->starting_orientation = c;
		o_c[1]++;
		return (1);
	}
	else if (c == 'E' && no_orientation(o_c))
	{
		data->starting_orientation = c;
		o_c[2]++;
		return (1);
	}
	else if (c == 'W' && no_orientation(o_c))
	{
		data->starting_orientation = c;
		o_c[3]++;
		return (1);
	}
	return (0);
}

int	check_map_chars(t_input_ll *m_ll, t_data *data)
{
	t_input_ll	*cur;
	int			o_c[6];
	int			i;

	init_oc_dc(o_c);
	data->starting_orientation = '-';
	cur = m_ll;
	while (cur)
	{
		i = -1;
		while (cur->line[++i])
		{
			if (is_orientation(cur->line[i], o_c, data))
				cur->line[i] = '2';
			else if (cur->line[i] == 'D')
				o_c[4]++;
			else if (cur->line[i] == 'F')
				o_c[5]++;
			else if (cur->line[i] != ' ' && cur->line[i] != '1'
				&& cur->line[i] != '0')
				return (0);
		}
		cur = cur->next;
	}
	return (data->starting_orientation != '-' && o_c[4] >= 1 && o_c[5] == 1);
}
