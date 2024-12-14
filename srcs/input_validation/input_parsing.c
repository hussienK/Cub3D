/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:18:41 by moassi            #+#    #+#             */
/*   Updated: 2024/07/15 14:43:55 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_to_ll(char *line, t_input_ll **ll, int *i)
{
	t_input_ll	*new;
	t_input_ll	*cur;
	char		*tmp;

	new = (t_input_ll *)malloc(sizeof(t_input_ll));
	tmp = line;
	line = ft_substr(line, 0, ft_strlen(line) - 1);
	new->line = line;
	new->next = NULL;
	free(tmp);
	if (!*ll)
		*ll = new;
	else
	{
		cur = *ll;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	(*i)++;
}

static int	get_map_width(t_input_ll **ll)
{
	int			w;
	t_input_ll	*cur;

	w = 0;
	cur = *ll;
	while (cur)
	{
		if (ft_strlen(cur->line) > w)
			w = ft_strlen(cur->line);
		cur = cur->next;
	}
	return (w);
}

void	parse_textures(int fd, t_input_ll **input_ll)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line && i < 6)
	{
		if (ft_strlen(line) > 1)
			add_to_ll(line, input_ll, &i);
		else
			free(line);
		if (i < 6)
			line = get_next_line(fd);
	}
}

void	parse_map(int fd, t_input_ll **map_ll, t_data *data)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strlen(line) > 1)
			add_to_ll(line, map_ll, &i);
		else
			free(line);
		line = get_next_line(fd);
	}
	data->map_height = i;
	data->map_width = get_map_width(map_ll);
	close(fd);
}
