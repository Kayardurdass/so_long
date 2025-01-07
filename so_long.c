/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:51:32 by uanglade          #+#    #+#             */
/*   Updated: 2025/01/07 14:45:50 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GNL/get_next_line.h"
#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include "includes/so_long.h"
#include "includes/keys.h"
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void	clean_and_exit(char *error, t_var var, int is_error)
{
	int	i;
	int	j;
	i = -1;
	while (++i < 13)
	{
		j = -1;
		while (++j < 8)
			mlx_destroy_image(var.mlx, var.map_sprites.tileset[i][j].img);
		free(var.map_sprites.tileset[i]);
	}
	free(var.map_sprites.tileset);
	i = -1;
	while (++i < 6)
	{
		j = -1;
		while (++j < 4)
			mlx_destroy_image(var.mlx, var.player_sprites.tileset[i][j].img);
		free(var.player_sprites.tileset[i]);
	}
	free(var.player_sprites.tileset);
	i = -1;
	while (++i < var.map.height)
		free(var.map.tiles[i]);
	free(var.map.tiles);
	mlx_destroy_window(var.mlx, var.mlx_win);
	mlx_destroy_display(var.mlx);
	mlx_loop_end(var.mlx);
	if (is_error)
		perror(error);
	exit(is_error);
}

int		direct_distance_to_tile(t_tile a, t_tile b)
{
	return (abs(a.x - b.x) + abs(a.y - b.y));
}

int	can_go(t_map map, t_tile position, e_direction direction)
{
	if (direction == UP && position.y - 1 < map.height)
		return (map.tiles[position.y - 1][position.x].type != FULL);
	if (direction == DOWN && position.y + 1 < map.height)
		return (map.tiles[position.y + 1][position.x].type != FULL);
	if (direction == RIGHT && position.x + 1 < map.width)
		return (map.tiles[position.y][position.x + 1].type != FULL);
	if (direction == LEFT && position.y - 1 < map.width)
		return (map.tiles[position.y][position.x - 1].type != FULL);
	return (0);
}

void	flood_fill(t_tile point, t_map map)
{
	if (can_go(map, point, LEFT) && map.tiles[point.y][point.x - 1].is_accesible == 0)
	{
		map.tiles[point.y][point.x - 1].is_accesible = 1;
		flood_fill(map.tiles[point.y][point.x - 1], map);
	}
	if (can_go(map, point, RIGHT) && map.tiles[point.y][point.x + 1].is_accesible == 0)
	{
		map.tiles[point.y][point.x + 1].is_accesible = 1;
		flood_fill(map.tiles[point.y][point.x + 1], map);
	}
	if (can_go(map, point, UP)  && map.tiles[point.y - 1][point.x].is_accesible == 0)
	{
		map.tiles[point.y - 1][point.x].is_accesible = 1;
		flood_fill(map.tiles[point.y - 1][point.x], map);
	}
	if (can_go(map, point, DOWN) && map.tiles[point.y + 1][point.x].is_accesible == 0)
	{
		map.tiles[point.y + 1][point.x].is_accesible = 1;
		flood_fill(map.tiles[point.y + 1][point.x], map);
	}
}

int	is_map_valid(t_map map, t_player player)
{
	int	i;
	int	j;
	int	temp;

	temp = map.nb_coins;
	flood_fill((t_tile){player.x, player.y, 0}, map);
	i = -1;
	while (++i < map.height)
	{
		j = -1;
		while (++j < map.width)
		{
			if (map.tiles[i][j].is_accesible == 1 && (map.tiles[i][j].type == COLLECTIBLE || map.tiles[i][j].type == EXIT))
				temp--;
		}
	}
	return (temp == -1);
}

int	my_mlx_pixel_get(t_data *data, int x, int y)
{
	char	*ret;

	ret = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)ret);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		get_file_line_count(char *path)
{
	int		i;
	int		fd;
	char	*buff;

	fd = open(path, O_RDONLY);
	buff = get_next_line(fd);
	while (buff != NULL)
	{
		free(buff);
		buff = get_next_line(fd);
		i++;
	}
	free(buff);
	close(fd);
	return (i);
}

t_map	parse_map(char *map_path, t_var *var)
{
	t_map	ret;
	int		fd;
	int		i;
	char	*buffer;
	int		j;
 
	i = 0;
	ret.height = get_file_line_count(map_path);
	if (ret.height < 3)
		clean_and_exit("map too smal", *var, 1);
	fd = open(map_path, O_RDONLY);
	buffer = get_next_line(fd);
	ret.nb_coins = 0;
	ret.tiles = (t_tile **)ft_calloc(ret.height, sizeof(t_tile *));
	if (!ret.tiles)
		clean_and_exit("Malloc error in the parsing of the map", *var, 1);
	ret.width = ft_strlen(buffer);
	printf("linecount : %d\n", ret.width);
	while (buffer != NULL)
	{
		ret.tiles[i] = (t_tile *)ft_calloc(ft_strlen(buffer), sizeof(t_tile));
		if (!ret.tiles[i])
			clean_and_exit("Malloc error in the parsing of the map", *var, 1);
		if (ft_strlen(buffer) != ret.width)
			clean_and_exit("A line was longer or shorter than an other", *var, 1);
		ret.width = ft_strlen(buffer);
		j = 0;
		while (buffer[j] != '\n' && buffer[j])
		{
			ret.tiles[i][j].x = j;
			ret.tiles[i][j].y = i;
			ret.tiles[i][j].is_accesible = 0;
			if (buffer[j] == '1')
			{
				ret.tiles[i][j].type = FULL;
				ret.tiles[i][j].is_accesible = -1;
			}
			else if (buffer[j] == '0')
				ret.tiles[i][j].type = EMPTY;
			else if (buffer[j] == 'C')
			{
				ret.tiles[i][j].type = COLLECTIBLE;
				ret.nb_coins++;
			}
			else if (buffer[j] == 'E')
				ret.tiles[i][j].type = EXIT;
			else if (buffer[j] == 'P')
			{
				ret.tiles[i][j].type = START;
				var->player.x = j;
				var->player.y = i;
			}
			j++;
		}
		free(buffer);
		i++;
		buffer = get_next_line(fd);
	}
	free(buffer);
	close(fd);
	ret.height = i;
	return (ret);
}

void	put_tile_to_img(t_data *full_img, t_data *tile, int x, int y)
{
	int		i;
	int		j;
	uint	color;

	i = -1;
	while (++i < 16)
	{
		j = -1;
		while (++j < 16)
			my_mlx_pixel_put(tile, i, j, my_mlx_pixel_get(full_img, x * 16 + i, y * 16 + j));
	}
}

t_tileset	create_map_tileset(char *relative_path, t_var var)
{
	t_tileset	ret;
	t_data		full_tileset;
	int			i;
	int			j;

	full_tileset.img = mlx_xpm_file_to_image(var.mlx, relative_path, &ret.width, &ret.height);
	full_tileset.addr = mlx_get_data_addr(full_tileset.img, &full_tileset.bits_per_pixel, &full_tileset.line_length, &full_tileset.endian);
	i = -1;
	ret.tileset = (t_data**)malloc(sizeof(t_data *) * 13);
	while (++i < 13)
	{
		j = -1;
		ret.tileset[i] = (t_data*)malloc(sizeof(t_data) * 8);
		while (++j < 8)
		{
			ret.tileset[i][j].img = mlx_new_image(var.mlx, 16, 16);
			ret.tileset[i][j].addr = mlx_get_data_addr(ret.tileset[i][j].img, &ret.tileset[i][j].bits_per_pixel, &ret.tileset[i][j].line_length, &ret.tileset[i][j].endian);
			put_tile_to_img(&full_tileset, &ret.tileset[i][j], i, j);
		}
	}
	mlx_destroy_image(var.mlx, full_tileset.img);
	return (ret);
}

t_tileset	create_player_tileset(char *relative_path, t_var var)
{
	t_tileset	ret;
	t_data		full_tileset;
	int			i;
	int			j;

	full_tileset.img = mlx_xpm_file_to_image(var.mlx, relative_path, &ret.width, &ret.height);
	full_tileset.addr = mlx_get_data_addr(full_tileset.img, &full_tileset.bits_per_pixel, &full_tileset.line_length, &full_tileset.endian);
	i = -1;
	ret.tileset = (t_data**)malloc(sizeof(t_data *) * 6);
	while (++i < 6)
	{
		j = -1;
		ret.tileset[i] = (t_data*)malloc(sizeof(t_data) * 4);
		while (++j < 4)
		{
			ret.tileset[i][j].img = mlx_new_image(var.mlx, 16, 16);
			ret.tileset[i][j].addr = mlx_get_data_addr(ret.tileset[i][j].img, &ret.tileset[i][j].bits_per_pixel, &ret.tileset[i][j].line_length, &ret.tileset[i][j].endian);
			put_tile_to_img(&full_tileset, &ret.tileset[i][j], i, j);
		}
	}
	mlx_destroy_image(var.mlx, full_tileset.img);
	return (ret);
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
			if (map.tiles[i][j].type == EMPTY)
				mlx_put_image_to_window(var.mlx, var.mlx_win, tileset.tileset[TILE_FLOOR(0)][TILE_FLOOR(1)].img, j * 16, i * 16);
			if (map.tiles[i][j].type == FULL)
				mlx_put_image_to_window(var.mlx, var.mlx_win, tileset.tileset[TILE_WALL_FULL_1(0)][TILE_WALL_FULL_1(1)].img, j * 16, i * 16);
			if (map.tiles[i][j].type == COLLECTIBLE)
				mlx_put_image_to_window(var.mlx, var.mlx_win, tileset.tileset[TILE_COLLECTIBLE(0)][TILE_COLLECTIBLE(1)].img, j * 16, i * 16);
			if (map.tiles[i][j].type == START)
				mlx_put_image_to_window(var.mlx, var.mlx_win, tileset.tileset[TILE_ENTRY(0)][TILE_ENTRY(1)].img, j * 16, i * 16);
			if (map.tiles[i][j].type == EXIT)
				mlx_put_image_to_window(var.mlx, var.mlx_win, tileset.tileset[TILE_EXIT(0)][TILE_EXIT(1)].img, j * 16, i * 16);
		}
	}
}

void	draw_player(t_player player, t_tileset player_sprites, t_var var)
{
	static int	sprite_state;
	static float last_update;
	
	if (!last_update)
		last_update = var.time;
	if (fabs(last_update - (var.time - 0.5)) < 0.01 && fabs(last_update - var.time) > 0.001)
	{
		sprite_state++;
		last_update = var.time;
	}
	if (sprite_state > 5)
		sprite_state = 0;
	if (player.direction == UP)
		mlx_put_image_to_window(var.mlx, var.mlx_win, player_sprites.tileset[sprite_state][2].img, player.x * 16, player.y * 16);
	if (player.direction == DOWN)
		mlx_put_image_to_window(var.mlx, var.mlx_win, player_sprites.tileset[sprite_state][0].img, player.x * 16, player.y * 16);
	if (player.direction == LEFT)
		mlx_put_image_to_window(var.mlx, var.mlx_win, player_sprites.tileset[sprite_state][3].img, player.x * 16, player.y * 16);
	if (player.direction == RIGHT)
		mlx_put_image_to_window(var.mlx, var.mlx_win, player_sprites.tileset[sprite_state][1].img, player.x * 16, player.y * 16);
}

float	ft_atof(char *nbr)
{
	int		big;
	int		little;
	float	ret;

	big = ft_atoi(nbr);
	little = ft_atoi(nbr + ft_nbrlen(big) + 1);
	ret = (float)big + ((float)little / pow(10, ft_nbrlen(little)));
	return (ret);
}

float	get_time()
{
	int		fd;
	char	*buff;
	float	ret;

	fd = open("/proc/uptime", O_RDONLY);
	if (fd < 0)
		return (0);
	buff = get_next_line(fd);
	ret = ft_atof(buff);
	free(buff);
	close(fd);
	return (ret);
}

void	handle_player_interactions(t_var *var)
{
	if (var->map.tiles[var->player.y][var->player.x].type == COLLECTIBLE)
	{
		var->map.tiles[var->player.y][var->player.x].type = EMPTY;
		var->player.coin_count++;
	}
	if (var->map.tiles[var->player.y][var->player.x].type == EXIT && var->player.coin_count == var->map.nb_coins)
	{
		clean_and_exit(NULL, *var, 0);
	}
}

int	handle_key(int key_code, t_var *var)
{
	if (key_code == KEY_UP)
	{
		var->player.direction = UP;
		if (can_go(var->map, (t_tile){var->player.x, var->player.y}, UP))
		{
			var->player.y--;
			var->player.move_count++;
			printf("%d\n", var->player.move_count);
		}
	}
	if (key_code == KEY_DOWN)
	{
		var->player.direction = DOWN;
		if (can_go(var->map, (t_tile){var->player.x, var->player.y}, DOWN))
		{
			var->player.y++;
			var->player.move_count++;
			printf("%d\n", var->player.move_count);
		}
	}
	if (key_code == KEY_RIGHT)
	{
		var->player.direction = RIGHT;
		if (can_go(var->map, (t_tile){var->player.x, var->player.y}, RIGHT))
		{
			var->player.x++;
			var->player.move_count++;
			printf("%d\n", var->player.move_count);
		}
	}
	if (key_code == KEY_LEFT)
	{
		var->player.direction = LEFT;
		if (can_go(var->map, (t_tile){var->player.x, var->player.y}, LEFT))
		{
			var->player.x--;
			var->player.move_count++;
			printf("%d\n", var->player.move_count);
		}
	}
	if (key_code == KEY_ESC)
	{
		clean_and_exit(NULL, *var, 0);
	}
	handle_player_interactions(var);
	return (1);
}

int	render(t_var *var)
{
	var->time = get_time();
	draw_map(var->map, var->map_sprites, *var);
	draw_player(var->player, var->player_sprites, *var);
	return (1);
}

int	main(int ac, char **av)
{
	t_var	var;
	int		img_width;
	int		img_height;

	var.mlx = mlx_init();
	var.map = parse_map(av[1], &var);
	var.mlx_win = mlx_new_window(var.mlx, var.map.width * 16, var.map.height * 16, "so_long by uanglade!");
	var.map_sprites = create_map_tileset("./CosmicLilac_Tiles.xpm", var);
	var.player_sprites = create_player_tileset("./player_sprites.xpm", var);
	var.player.direction = RIGHT;
	var.time = get_time();
	if (!is_map_valid(var.map, var.player))
		return (printf("map error: not solvable !"), 1);
	var.player.coin_count = 0;
	mlx_clear_window(var.mlx, var.mlx_win);
	draw_map(var.map, var.map_sprites, var);
	draw_player(var.player, var.player_sprites, var);
	mlx_loop_hook(var.mlx, render, &var);
	mlx_key_hook(var.mlx_win, handle_key, &var);
	mlx_loop(var.mlx);
}
