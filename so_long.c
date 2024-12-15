/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:51:32 by uanglade          #+#    #+#             */
/*   Updated: 2024/12/15 03:58:47 by uanglade         ###   ########.fr       */
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
	t_data		img;
	t_player	player;
	t_tileset	map_sprites;
	t_tileset	player_sprites;
	t_map		map;
	float		time;
}				t_var;

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
	if (color != 0x000000)
	{
		*(unsigned int*)dst = color;
	}
	else
	{
		*(unsigned int*)dst = 0xe17cb7;
	}
}

t_map	parse_map(char *map_path, t_var *var)
{
	t_map	ret;
	int		fd;
	int		i;
	char	*buffer;
	int		j;
 
	i = 0;
	fd = open(map_path, O_RDONLY);
	buffer = get_next_line(fd);
	ret.tiles = (t_tile **)malloc(sizeof(t_tile) * 1024);
	while (buffer != NULL)
	{
		ret.tiles[i] = (t_tile *)malloc(sizeof(t_tile) * ft_strlen(buffer));
		ret.width = ft_strlen(buffer);
		j = 0;
		while (buffer[j] != '\n' && buffer[j])
		{
			ret.tiles[i][j].x = j;
			ret.tiles[i][j].y = i;
			if (buffer[j] == '1')
				ret.tiles[i][j].type = FULL;
			else if (buffer[j] == '0')
				ret.tiles[i][j].type = EMPTY;
			else if (buffer[j] == 'C')
				ret.tiles[i][j].type = COLLECTIBLE;
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
		i++;
		buffer = get_next_line(fd);
	}
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
		{
			my_mlx_pixel_put(tile, i, j, my_mlx_pixel_get(full_img, x * 16 + i, y * 16 + j));
		}
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
	return (ret);
}

void	put_image_to_window_buffer(t_var *var, t_data img, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 16)
	{
		j = -1;
		while (++j < 16)
		{
			//my_mlx_pixel_put(&var->img, i, j, 0x00000FF);
			my_mlx_pixel_put(&var->img, x, y, my_mlx_pixel_get(&img, i, j));
		}
	}
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

int	can_player_go(t_var var, e_direction direction)
{
	if (direction == UP)
		return (var.map.tiles[var.player.y - 1][var.player.x].type != FULL);
	if (direction == DOWN)
		return (var.map.tiles[var.player.y + 1][var.player.x].type != FULL);
	if (direction == RIGHT)
		return (var.map.tiles[var.player.y][var.player.x + 1].type != FULL);
	if (direction == LEFT)
		return (var.map.tiles[var.player.y][var.player.x - 1].type != FULL);
	return (0);
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
		var->player.item_count++;
	}
}

int	handle_key(int key_code, t_var *var)
{
	if (key_code == KEY_UP)
	{
		var->player.direction = UP;
		if (can_player_go(*var, UP))
			var->player.y--;
	}
	if (key_code == KEY_DOWN)
	{
		var->player.direction = DOWN;
		if (can_player_go(*var, DOWN))
			var->player.y++;
	}
	if (key_code == KEY_RIGHT)
	{
		var->player.direction = RIGHT;
		if (can_player_go(*var, RIGHT))
			var->player.x++;
	}
	if (key_code == KEY_LEFT)
	{
		var->player.direction = LEFT;
		if (can_player_go(*var, LEFT))
			var->player.x--;
	}
	if (key_code == KEY_ESC)
	{
		mlx_loop_end(var->mlx);
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
	char	*relative_path = "./CosmicLilac_Tiles.xpm";
	int		img_width;
	int		img_height;

	var.mlx = mlx_init();
	var.map = parse_map(av[1], &var);
	var.mlx_win = mlx_new_window(var.mlx, var.map.width * 16, var.map.height * 16, "Hello world!");
	var.img.img = mlx_new_image(var.mlx, var.map.width * 16, var.map.height * 16);
	var.img.addr = mlx_get_data_addr(var.img.img, &var.img.bits_per_pixel, &var.img.line_length, &var.img.endian);
	var.map_sprites = create_map_tileset(relative_path, var);
	var.player_sprites = create_player_tileset("./player_sprites.xpm", var);
	var.player.direction = RIGHT;
	var.time = get_time();
	mlx_clear_window(var.mlx, var.mlx_win);
	draw_map(var.map, var.map_sprites, var);
	draw_player(var.player, var.player_sprites, var);
	mlx_loop_hook(var.mlx, render, &var);
	mlx_key_hook(var.mlx_win, handle_key, &var);
	mlx_loop(var.mlx);
}
