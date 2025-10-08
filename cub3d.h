/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:01:15 by cguinot           #+#    #+#             */
/*   Updated: 2025/10/08 15:37:39 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft/libft.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef enum e_cardinal_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}	t_cardinal_direction;

typedef struct s_player
{
	int		map_x;
	int		map_y;
	float	x;
	float	y;
	int		tmp_x;
	int		tmp_y;
	float	angle;

	double	dir_x;
	double	dir_y;

	char	boussole;

	bool	key_up;
	bool	key_down;
	bool	key_right;
	bool	key_left;
	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_texture
{
	void	*img;
	int		*data;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_config
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_w;
	int			win_h;
	t_color		floor_color;
	t_color		ceiling_color;
	t_player	player;
	t_texture	textures[4];
	t_texture	frame;
	char		**map;
	int			map_height;
	int			map_width;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			wall_o;
	int			tex_y;
	int			tex_x;
	int			speed;
	float		wall_hit;
	int			map_started;
}	t_config;

/*parsing*/
int		check_extension(char *filename);
int		valid_text(char **texture, char *identifier, char *line);
int		text_parse(t_config *config, char *line, int textcount);
int		check_extension(char *filename);
int		is_line_color(char *line);
int		is_only_digit(char *nb);

int		add_map_line(t_config *config, char *line);
int		is_map_line(char *line);

int		find_player(t_config *config);
int		check_zero_neighbors(t_config *config, int x, int y);
int		is_only_whitespace(char *line);
int		check_unknown_argument(char *line);
int		handle_player_tile(t_config *config, int i, int j);
void	print_array(char **array);
int		ft_atoi_neuille(const char *str);

/*init*/
void	init_config(t_config *config);
void	init_player(t_player *player);
void	init_textures(t_config *config);
/*stats de la map*/
void	display_config(t_config *config);
void	display_map(t_config *config);

/*free*/
void	free_visited(char **visited, int height);
int		free_all(t_config *config);
void	free_tab(char **tab);
/*raycasting*/
int		draw_loop(t_config *game);

/*utils_ray*/
float	distance(float x, float y);
float	fixed_dist(float delta_x, float delta_y, t_config *game);
bool	touch(float px, float py, t_config *game);

/*draw*/
void	put_pixel(int x, int y, int color, t_texture *frame);
void	put_pixel_rgb(int x, int y, t_color *color, t_texture *frame);
int		get_texture_pixel(t_texture *tex, int x, int y);
void	clear_img(t_config *game);
void	draw_floor_ceiling(t_config *game);
/*hook*/
int		key_press(int keycode, t_config *config);
int		key_release(int keycode, t_player *player);
void	move_player(t_player *player, t_config *game);

# define WIN_H 800
# define WIN_W 2000
# define W 119
# define A 97
# define S 115
# define D 100
# define PI 3.14159265359
# define BLOCK 64
# define RIGHT 65363
# define LEFT 65361

#endif