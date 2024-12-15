/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:10:05 by uanglade          #+#    #+#             */
/*   Updated: 2024/12/03 21:13:32 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "keys.h"
# include "../GNL/get_next_line.h"
# include "../libft/libft.h"

typedef enum s_direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
}				e_direction;

typedef struct s_player
{
	int			x;
	int			y;
	int			item_count;
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
}				t_tile;

typedef struct s_map
{
	int		width;
	int		height;
	t_tile	**tiles;
}			t_map;

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
