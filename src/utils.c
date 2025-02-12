/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:22:52 by uanglade          #+#    #+#             */
/*   Updated: 2025/02/12 02:15:04 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_tileset(t_tileset tileset, void *mlx, int width, int height)
{
	int	i;
	int	j;

	if (!tileset.tileset || !mlx)
		return ;
	i = -1;
	while (++i < width)
	{
		j = -1;
		while (++j < height)
			mlx_destroy_image(mlx, tileset.tileset[i][j].img);
		free(tileset.tileset[i]);
	}
	free(tileset.tileset);
}

void	clean_and_exit(char *error, t_var var, int is_error)
{
	int	i;

	if (is_error)
		write(2, error, ft_strlen(error));
	free_tileset(var.map_sprites, var.mlx, 13, 8);
	free_tileset(var.player_sprites, var.mlx, 6, 4);
	i = -1;
	if (var.map.tiles)
	{
		while (++i < var.map.height)
			free(var.map.tiles[i]);
		free(var.map.tiles);
	}
	if (var.mlx && var.mlx_win)
		mlx_destroy_window(var.mlx, var.mlx_win);
	if (var.mlx)
		mlx_destroy_display(var.mlx);
	if (var.mlx)
		mlx_loop_end(var.mlx);
	free(var.mlx);
	exit(is_error);
}

int	direct_distance_to_tile(t_tile a, t_tile b)
{
	return (abs(a.x - b.x) + abs(a.y - b.y));
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
	*(unsigned int *)dst = color;
}
