/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tileset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:27:15 by uanglade          #+#    #+#             */
/*   Updated: 2025/02/12 03:12:38 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_strlinelen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	return (i);
}

void	create_tileset2(t_data ts, t_tileset *ret, t_var var)
{
	int	i;
	int	j;

	i = -1;
	while (++i < ret->width)
	{
		j = -1;
		ret->tileset[i] = (t_data *)malloc(sizeof(t_data) * ret->height);
		if (!ret->tileset)
			return (clean_and_exit("Failed to malloc tileset", var, 1));
		while (++j < ret->height)
		{
			ret->tileset[i][j].img = mlx_new_image(var.mlx, 16, 16);
			if (!ret->tileset[i][j].img)
				return (clean_and_exit("Failed to load tileset", var, 1));
			ret->tileset[i][j].addr = mlx_get_data_addr(ret->tileset[i][j].img,
					&ret->tileset[i][j].bits_per_pixel,
					&ret->tileset[i][j].line_length,
					&ret->tileset[i][j].endian);
			if (!ret->tileset[i][j].addr)
				return (clean_and_exit("Failed to load tileset", var, 1));
			put_tile_to_img(&ts, &ret->tileset[i][j], i, j);
		}
	}
}

t_tileset	create_tileset(char *rel_path, t_var var, int width, int height)
{
	t_tileset	ret;
	t_data		ts;

	ts.img = mlx_xpm_file_to_image(var.mlx, rel_path, &ret.width, &ret.height);
	if (!ts.img)
		return (clean_and_exit("Failed to load tileset", var, 1), ret);
	ts.addr = mlx_get_data_addr(ts.img, &ts.bits_per_pixel, &ts.line_length,
			&ts.endian);
	if (!ts.addr)
		return (clean_and_exit("Failed to get img address", var, 1), ret);
	ret.tileset = (t_data **)malloc(sizeof(t_data *) * width);
	if (!ret.tileset)
		return (clean_and_exit("Failed to malloc tileset", var, 1), ret);
	ret.height = height;
	ret.width = width;
	create_tileset2(ts, &ret, var);
	mlx_destroy_image(var.mlx, ts.img);
	return (ret);
}
