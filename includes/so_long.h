/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:10:05 by uanglade          #+#    #+#             */
/*   Updated: 2025/02/12 02:53:15 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <time.h>
# include "keys.h"
# include "../GNL/get_next_line.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include "../GNL/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

typedef enum s_direction
{
	UP = KEY_UP,
	DOWN = KEY_DOWN,
	RIGHT = KEY_RIGHT,
	LEFT = KEY_LEFT,
}				e_direction;

typedef struct s_player
{
	int			x;
	int			y;
	int			coin_count;
	int			move_count;
	e_direction	direction;
}				t_player;

typedef enum s_type
{
	FULL,
	EMPTY,
	COLLECTIBLE,
	START,
	EXIT
}			e_type;

typedef struct s_tile
{
	int		x;
	int		y;
	e_type	type;
	int		is_accesible;
}				t_tile;

typedef struct s_map
{
	int		width;
	int		height;
	int		nb_coins;
	t_tile	**tiles;
}			t_map;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_tileset
{
	int		height;
	int		width;
	t_data	**tileset;
}				t_tileset;

typedef struct s_var
{
	void		*mlx;
	void		*mlx_win;
	t_player	player;
	t_tileset	map_sprites;
	t_tileset	player_sprites;
	t_map		map;
	clock_t		time;
}				t_var;

int		ft_strlinelen(char *str);
void	clean_and_exit(char *error, t_var var, int is_error);
t_map	parse_map(char *map_path, t_var *var);
void	draw_player(t_player player, t_tileset player_sprites, t_var var);
void	draw_map(t_map map, t_tileset tileset, t_var var);
int		direct_distance_to_tile(t_tile a, t_tile b);
void	clean_and_exit(char *error, t_var var, int is_error);
void	free_tileset(t_tileset tileset, void *mlx, int width, int height);
int		can_go(t_map map, t_tile position, e_direction direction);
void	flood_fill(t_tile point, t_map map);
int		is_map_valid(t_map map, t_player player, t_var var);
int		my_mlx_pixel_get(t_data *data, int x, int y);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	put_tile_to_img(t_data *full_img, t_data *tile, int x, int y);
t_tileset	create_tileset(char *rel_path, t_var var, int width, int height);

# define TILE_WALL_CORNER_DOWN_RIGHT(x) (x == 0 ? 0 : 0)
# define TILE_WALL_DOWN_1(x) (x == 0 ? 1 : 0)
# define TILE_WALL_DOWN_2(x) (x == 0 ? 2 : 0)
# define TILE_WALL_CORNER_DOWN_LEFT(x) (x == 0 ? 3 : 0)
# define TILE_WALL_RIGHT_1(x) (x == 0 ? 0 : 1)
# define TILE_WALL_LEFT_1 (x) (x == 0 ? 3 : 1)
# define TILE_WALL_RIGHT_2(x) (x == 0 ? 0 : 2)
# define TILE_WALL_LEFT_2(x) (x == 0 ? 3 : 2)
# define TILE_WALL_CORNER_UP_RIGHT(x) (x == 0 ? 0 : 3)
# define TILE_WALL_UP_1(x) (x == 0 ? 1 : 3)
# define TILE_WALL_UP_2(x) (x == 0 ? 2 : 3)
# define TILE_WALL_CORNER_UP_LEFT(x) (x == 0 ? 3 : 3)
# define TILE_WALL_FULL_1(x) (x == 0 ? 1 : 1)
# define TILE_WALL_FULL_2(x) (x == 0 ? 2 : 1)
# define TILE_WALL_FULL_3(x) (x == 0 ? 1 : 2)
# define TILE_WALL_FULL_4(x) (x == 0 ? 2 : 2)
# define TILE_FLOOR(x) (x == 0 ? 4 : 0)
# define TILE_FLOOR_DECORATION_1(x) (x == 0 ? 0 : 6)
# define TILE_FLOOR_DECORATION_2(x) (x == 0 ? 1 : 5)
# define TILE_FLOOR_DECORATION_3(x) (x == 0 ? 9 : 5)
# define TILE_BACKGROUND(x) (x == 0 ? 2 : 7)
# define TILE_COLLECTIBLE(x) (x == 0 ? 12 : 4)
# define TILE_ENTRY(x) (x == 0 ? 12 : 0)
# define TILE_EXIT(x) (x == 0 ? 12 : 5)

#endif
