/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:51:32 by uanglade          #+#    #+#             */
/*   Updated: 2025/02/12 02:53:28 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	handle_player_interactions(t_var *var)
{
	if (var->map.tiles[var->player.y][var->player.x].type == COLLECTIBLE)
	{
		var->map.tiles[var->player.y][var->player.x].type = EMPTY;
		var->player.coin_count++;
	}
	if (var->map.tiles[var->player.y][var->player.x].type == EXIT
		&& var->player.coin_count == var->map.nb_coins)
	{
		clean_and_exit(NULL, *var, 0);
	}
}

int	handle_key(int key_code, t_var *var)
{
	if (key_code == KEY_ESC)
		clean_and_exit(NULL, *var, 0);
	else if (key_code == KEY_DOWN || key_code == KEY_UP || key_code == KEY_LEFT
		|| key_code == KEY_RIGHT)
	{
		var->player.direction = key_code;
		if (can_go(var->map, (t_tile){var->player.x, var->player.y, 0, 0},
			key_code))
		{
			var->player.y += (key_code == KEY_UP) * -1 + (key_code == KEY_DOWN);
			var->player.x += (key_code == KEY_LEFT) * -1
				+ (key_code == KEY_RIGHT);
			var->player.move_count++;
			printf("%d\n", var->player.move_count);
		}
	}
	handle_player_interactions(var);
	return (1);
}

int	render(t_var *var)
{
	draw_map(var->map, var->map_sprites, *var);
	draw_player(var->player, var->player_sprites, *var);
	return (1);
}

int	main(int ac, char **av)
{
	static t_var	var = (t_var){0};

	var.mlx = mlx_init();
	if (!var.mlx)
		return ((void)ac, clean_and_exit("Error init mlx", var, 1), 1);
	var.map = parse_map(av[1], &var);
	var.mlx_win = mlx_new_window(var.mlx, var.map.width * 16, var.map.height
			* 16, "so_long by uanglade!");
	if (!var.mlx_win)
		return (clean_and_exit("Error creating window", var, 1), 1);
	var.map_sprites = create_tileset("./res/CosmicLilac_Tiles.xpm", var, 13, 8);
	var.player_sprites = create_tileset("./res/player_sprites.xpm", var, 6, 4);
	var.time = clock();
	if (!is_map_valid(var.map, var.player, var))
		return (clean_and_exit("Map not solvable", var, 1), 1);
	mlx_clear_window(var.mlx, var.mlx_win);
	draw_map(var.map, var.map_sprites, var);
	draw_player(var.player, var.player_sprites, var);
	mlx_loop_hook(var.mlx, render, &var);
	mlx_key_hook(var.mlx_win, handle_key, &var);
	mlx_loop(var.mlx);
}
