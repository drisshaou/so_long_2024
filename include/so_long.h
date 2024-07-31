/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:23:59 by drhaouha          #+#    #+#             */
/*   Updated: 2024/07/31 07:33:49 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <stdio.h>
# include <stddef.h>
# include <limits.h>
# include <stdbool.h>
# include "libftmini.h"

# define WIDTH 1024
# define HEIGHT 768
# define STEP 1
# define ALPHA 0x00ff16

# define LETTER_LEFT		97
# define LETTER_RIGHT		100
# define LETTER_UP			119
# define LETTER_DOWN		115
# define ARROW_LEFT			65361
# define ARROW_RIGHT		65363
# define ARROW_UP			65362
# define ARROW_DOWN			65364
# define KEY_ESC			65307

# define ERR				"Error\n"
# define ERR_ALLOC_MEM		"Error\nCan't allocate memory.\n"
# define ERR_OPEN_FILE		"Error\ncan't open file"
# define ERR_INCORR_MAP		"Error\nThe map is not correct.\n"
# define ERR_NO_PLAYER		"Player not found.\n"
# define ERR_MORE_PLAYER	"More than one player.\n"
# define ERR_NO_ITEM		"Item not found.\n"
# define ERR_NO_EXIT		"Exit not found.\n"
# define ERR_MORE_EXIT		"More than one exit.\n"
# define ERR_OTHER_EL		"Other(s) character(s) found.\n"
# define ERR_UNREACH_EL		"Error\nUnreachable element(s).\n"
# define ERR_NO_FILE		"Error\nFile not found.\n"
# define ERR_EXT_UNKNOWN	"Error\nExtension unknown.\n"
# define ERR_EMPTY_MAP		"Error\nThe map is empty.\n"
# define ERR_MAP_UNRECT		"Error\nThe map is not rectangular.\n"
# define ERR_LOAD_TEXTURE	"Error\nSome texture(s) can't be loaded.\n"
# define ERR_MLX_INIT		"Error\nCan't init mlx.\n"

typedef struct s_count
{
	int	player;
	int	item;
	int	exit;
	int	others;
}	t_count;

typedef struct s_size
{
	int	width;
	int	height;
}	t_size;

typedef struct s_dim
{
	int	cols;
	int	rows;
}	t_dim;

typedef struct s_coord
{
	int	col;
	int	row;
}	t_coord;

typedef struct s_pt
{
	int	x;
	int	y;
}	t_pt;

typedef struct s_img
{
	void	*ptr;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		_x;
	int		_y;
}	t_img;

typedef struct s_pground
{
	t_img	*img;
}	t_pground;

typedef struct s_player
{
	t_img	*img;
	void	*ptrs[4][6];
	int		frame;
	int		counter;
	int		direction;
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	int		row;
	int		col;
	int		collected;
	bool	is_moving;
	char	id;
}	t_player;

typedef struct s_num
{
	t_img	*img;
	void	*ptrs[11];
}	t_num;

typedef struct s_win
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	int			screen_w;
	int			screen_h;
	char		**map;
	t_num		*numeric;
	t_player	*player;
	t_player	*ghost;
	t_pground	*playground;
	t_pground	*playground_full;
	t_pground	*playground_tmp;
	t_img		*floor;
	t_img		*grey_cube;
	t_img		*blue_cube;
	t_img		*point;
	t_img		*cherry;
	t_img		*cherry_fg;
	t_img		*cherry_bg;
	t_img		*ladder;
	t_img		*game_over;
	t_img		*you_win;
	t_coord		*exit;
	t_dim		*map_dim;
	int			collectibes;
	bool		finished;
	bool		has_ghost;
	bool		**collect;
}	t_slng;

void	print_flooded_map(char **map, t_coord cur);
void	flood_fill(char **map, t_coord size, t_coord cur, char *str);
bool	validate_flood(char **map, t_coord size, t_coord begin);
bool	validate_elem(t_count el);

bool	check_map_elem(char **map, t_coord *begin);
bool	check_map_sides(char **map);
char	**mapdup(char **map);
bool	check_map(char **map);

char	*get_map_line(int fd);
int		get_map_size(char const *path);
char	**get_map(char const *path);
bool	check_file(const char *path);
bool	parse_file(char ***map, const char *path);

void	free_playground_images(t_slng *so);
void	free_numeric(t_slng *so);
void	free_ghost(t_slng *so);
void	free_player(t_slng *so);
void	free_playgrounds(t_slng *so);
void	free_collect(bool ***collect, t_dim d);
void	free_map(char ***map);
bool	progressive_free(t_slng *so, int i);
void	free_slng(t_slng *so, int i);

void	destroy_all_images_next(t_slng *so);
void	destroy_all_images(t_slng *so);
int		exit_game(t_slng *so);

t_img	get_collected_layer(t_slng *so, t_img *img);
t_img	get_counter_layer(t_slng *so, t_img *img, int nb);
t_img	get_ghost_layer(t_slng *so, t_img *img);
t_img	get_player_layer(t_slng *so, t_img *img);
t_img	get_exit_layer(t_slng *so, t_img *img);

int		update_player_frame(t_slng *so, int count);
void	playground_to_layer(t_img *layer, t_img *img);
int		get_pixel_from_image(t_img *img, t_pt pos);
void	put_pixel_to_image(t_img *img, t_pt pos, int color);
t_img	get_background_layer(t_slng *so, t_img *img, t_pt p, t_size s);

void	insert_image_to(t_img *dest, t_img *src, t_pt dst);
void	insert_layer_in_image(t_slng *so, t_img *img, t_img layer);
void	refresh_frame(t_slng *so);
t_pt	coord_to_position(t_slng *so, t_coord dest, t_dim d);

t_img	*get_playground_layer(t_slng *so);
void	clean_frame(t_slng *so);
void	update_playgrounds_pos(t_slng *so);
int		draw_frame(t_slng *so);

void	__timer(unsigned long long i);
void	you_win_next(t_slng *so);
void	you_win(t_slng *so);

int		to_argb(int t, int r, int g, int b);
void	apply_grayscale(t_img *img);
void	game_is_over(t_slng *so);

void	update_map_content(t_slng *so, t_player *which, t_coord coord);
void	keep_player_inside(t_slng *so);
void	playground_n_players_up_down_adjust(t_slng *so);
void	playground_n_players_left_right_adjust(t_slng *so);
void	animate_player(t_slng *so, t_player *which);
bool	move_verticaly_first(t_slng *so, t_coord delta);
bool	move_horizontaly_first(t_slng *so, t_coord delta);
int		_abs(int j);
bool	move_towards_player(t_slng *so);
bool	is_next_coord_valid(t_slng *so, t_player *which, t_coord coord);
void	process_ghost(t_slng *so);
void	process_player(t_slng *so);
int		game_loop(t_slng *so);

void	set_move_direction(t_player *which);
void	reset_move(t_player *which);
int		key_release(int keycode, t_slng *so);

t_pt	prevent_zero_div(t_slng *so, t_pt p);
t_pt	get_displacement(t_slng *so);
void	displace_playground_n_player(t_slng *so, t_pt delta);
void	center_player_in_window(t_slng *so);

t_coord	get_coord_in_map(t_slng *so, char id);
t_pt	get_pos_in_playground(t_slng *so, t_dim d, char id);
void	init_ghost(t_slng *so);
void	init_player(t_slng *so);
void	init_window_n_players(t_slng *so);
bool	set_playground_tmp(t_slng *so);
bool	set_playground_full(t_slng *so);
void	add_walls(t_slng *so, t_dim d);
void	add_collectibles(t_slng *so, t_dim d);
void	add_floor(t_slng *so, t_dim d);
bool	set_playgrounds(t_slng *so);

bool	process_xpm_image(t_slng *so, t_img **img, char *path);
bool	add_ghost_images_next(t_slng *so, char *textures[4]);
bool	add_ghost_images(t_slng *so);
bool	add_player_images_next(t_slng *so, char *textures[4][6]);
bool	add_player_images(t_slng *so);
bool	add_numeric_images_next(t_slng *so, char *textures[11]);
bool	add_numeric_images(t_slng *so);
bool	add_playground_images(t_slng *so);
bool	add_all_images(t_slng *so);

t_dim	get_map_dimension(t_slng *so);
bool	malloc_img(t_img **img);
bool	malloc_playground_images(t_slng *so);
bool	malloc_numeric(t_slng *so);
bool	malloc_ghost(t_slng *so);
bool	malloc_player(t_slng *so);
bool	malloc_playgrounds(t_slng *so);
bool	malloc_init_collect(t_slng *so);
bool	malloc_init_exit(t_slng *so);
bool	malloc_init_map_dim(t_slng *so);

bool	prepare_memory(t_slng *so);
int		try_game(char ***map);

#endif
