/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:23:39 by uanglade          #+#    #+#             */
/*   Updated: 2025/02/12 02:12:43 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	draw_map2(t_tile tile, t_tileset tileset, t_var var, long ij)
{
	int	i;
	int	j;

	i = (int)(ij >> 32);
	j = (int)(ij & 0b11111111111111111111111111111111);
	if (tile.type == EMPTY)
		mlx_put_image_to_window(var.mlx, var.mlx_win,
			tileset.tileset[TILE_FLOOR(0)][TILE_FLOOR(1)].img, j * 16, i * 16);
	if (tile.type == FULL)
		mlx_put_image_to_window(var.mlx, var.mlx_win,
			tileset.tileset[TILE_WALL_FULL_1(0)][TILE_WALL_FULL_1(1)].img, j
			* 16, i * 16);
	if (tile.type == COLLECTIBLE)
		mlx_put_image_to_window(var.mlx, var.mlx_win,
			tileset.tileset[TILE_COLLECTIBLE(0)][TILE_COLLECTIBLE(1)].img, j
			* 16, i * 16);
}

void	draw_map(t_map map, t_tileset tileset, t_var var)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map.height)
	{
		j = -1;
		while (++j < map.width)
		{
			draw_map2(map.tiles[i][j], tileset, var, (long)((long)i << 32 | j));
			if (map.tiles[i][j].type == START)
				mlx_put_image_to_window(var.mlx, var.mlx_win,
					tileset.tileset[TILE_ENTRY(0)][TILE_ENTRY(1)].img, j * 16, i
					* 16);
			if (map.tiles[i][j].type == EXIT)
				mlx_put_image_to_window(var.mlx, var.mlx_win,
					tileset.tileset[TILE_EXIT(0)][TILE_EXIT(1)].img, j * 16, i
					* 16);
		}
	}
}

int	get_sprite_index(e_direction dir)
{
	if (dir == UP)
		return (2);
	if (dir == DOWN)
		return (0);
	if (dir == LEFT)
		return (3);
	return (1);
}

void	draw_player(t_player player, t_tileset player_sprites, t_var var)
{
	static int		sprite_state;
	static clock_t	last_update;

	if (!last_update)
		last_update = clock();
	if (clock() - last_update >= 60000.0f)
	{
		sprite_state++;
		last_update = clock();
	}
	if (sprite_state > 5)
		sprite_state = 0;
	mlx_put_image_to_window(var.mlx, var.mlx_win,
		player_sprites.tileset[sprite_state][get_sprite_index(player.direction)]
		.img,
		player.x * 16, player.y * 16);
}

void	put_tile_to_img(t_data *full_img, t_data *tile, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 16)
	{
		j = -1;
		while (++j < 16)
			my_mlx_pixel_put(tile, i, j, my_mlx_pixel_get(full_img, x * 16 + i,
					y * 16 + j));
	}
}
