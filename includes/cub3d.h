/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moassi <moassi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:45:51 by moassi            #+#    #+#             */
/*   Updated: 2024/07/19 09:08:02 by moassi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/ft_printf.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"

# define H 950
# define W 950

# define TEX_NUM 8
# define TEX_W 64
# define TEX_H 64

# define EAST_INDEX 1
# define WEST_INDEX 2
# define SOUTH_INDEX 0
# define NORTH_INDEX 3
# define CEILING_INDEX 5
# define FLOOR_INDEX 4
# define DOOR_INDEX 6
# define EXIT_INDEX 7

# define MOVE_SPEED 5
# define ROT_SPEED 3
# define MOUSE_ROT_SPEED 4

typedef enum e_error_msgs
{
	BADARGUMENTS,
	MAPNOTFOUND,
	INVALIDMAP
}	t_error_msgs;

typedef struct s_input_ll
{
	char				*line;
	struct s_input_ll	*next;
}	t_input_ll;

typedef struct s_calc_vars
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;

	float	ray_dir_x0;
	float	ray_dir_y0;
	float	ray_dir_x1;
	float	ray_dir_y1;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	int		p;

	int		color;
	int		pos;
	int		tex_num;
	bool	is_door;
	bool	is_exit;
}	t_calc_vars;

typedef struct s_data
{
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;
	char	*floor_texture;
	char	*ceiling_texture;
	bool	using_textures_f;
	bool	using_textures_c;
	int		floor_color[3];
	int		cieling_color[3];
	int		**map;
	int		map_width;
	int		map_height;
	char	starting_orientation;
	int		start_x;
	int		start_y;
}	t_data;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_y;
	double	dir_x;
	double	plane_x;
	double	plane_y;
	double	time;
	double	old_time;
	bool	moving_forward;
	bool	moving_back;
	bool	moving_left;
	bool	moving_right;
	bool	rotating_right;
	bool	rotating_left;
	bool	mouse_left;
	bool	mouse_right;
}	t_player;

typedef struct s_minimap
{
	void	*solid_image;
	void	*path_image;
	void	*player_image;
	void	*border_image;
	void	*door_image;
	void	*exit_image;
}	t_minimap;

typedef struct s_table
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_player			*player;
	t_calc_vars			*cv;
	t_data				*data;
	t_minimap			*minimap;
	t_img				*render_image;
	int					buffer[H][W];
	int					textures[TEX_NUM][TEX_H * TEX_W];
	struct timeval		previous_time;
	int					last_x;
}	t_table;

/* utils*/
int		ll_len(t_input_ll *ll);
void	free_char_matrix(char **mat);
void	free_ll(t_input_ll **ll);
void	free_textures(t_data *data);
void	free_intmap(t_data *data, int l);
long	get_time_v(void);
void	uusleep(long usec);
int		is_numeric(char	*str);
void	put_fps(t_table *d, double time_diff);

/* error msgs */
int		err(t_error_msgs type, int ret);
void	exit_with_message(t_table *table, char *str);

/* input validation */
int		validate_input(int ac, char **av, t_data *data);
int		validate_texture(t_input_ll **t_ll, t_data *data);
int		validate_map(t_input_ll **m_ll, t_data *data);
int		valid_exit(t_data *data);
int		valid_doors(t_data *data);

int		check_map_chars(t_input_ll *m_ll, t_data *data);
int		can_reach_out(int **map, t_data *data, int i, int j);

/* input parsing */
void	parse_textures(int fd, t_input_ll **input_ll);
void	parse_map(int fd, t_input_ll **map_ll, t_data *data);

int		render_walls(t_table *d);
void	render_walls_extra_calc(t_table *d, int x);
void	render_ceiling_floor(t_table *d);
void	generate_textures(t_table *d);
void	choose_texture(t_table *d);
void	check_for_special(t_table *d);
int		on_destroy(t_table *table);

void	rotate(t_table *d, double time_diff);
void	move(t_table *d, double time_diff);
int		move_unpress(int keypress, t_table *table);
int		move_press(int keypress, t_table *table);
int		mouse_move(t_table *d);
void	init_player_dir(t_data *d, t_player *p);

void	open_doors(t_table *d);
void	init_minimap(t_table *d);
void	render_minimap(t_table *d);
void	free_minimap(t_table *d);
void	create_image(t_table *d);

#endif
