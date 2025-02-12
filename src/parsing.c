/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:55:12 by uanglade          #+#    #+#             */
/*   Updated: 2025/02/12 02:56:31 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	get_file_line_count(char *path)
{
	int		i;
	int		fd;
	char	*buff;

	fd = open(path, O_RDONLY);
	buff = get_next_line(fd);
	i = 0;
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

void	fill_line2(char c, t_map *ret, t_var *var, t_tile *tile)
{
	if (c == '1')
	{
		tile->type = FULL;
		tile->is_accesible = -1;
	}
	else if (c == '0')
		tile->type = EMPTY;
	else if (c == 'C')
	{
		tile->type = COLLECTIBLE;
		ret->nb_coins++;
	}
	else if (c == 'E')
		tile->type = EXIT;
	else if (c == 'P')
	{
		tile->type = START;
		var->player.x = tile->x;
		var->player.y = tile->y;
	}
	else
		return (clean_and_exit("Other char found in map", *var, 1));
}

void	fill_line(char *buffer, t_map *ret, t_var *var, int i)
{
	int	j;

	j = 0;
	while (buffer[j] != '\n' && buffer[j])
	{
		ret->tiles[i][j].x = j;
		ret->tiles[i][j].y = i;
		ret->tiles[i][j].is_accesible = 0;
		fill_line2(buffer[j], ret, var, ret->tiles[i] + j);
		j++;
	}
}

int	parse_map2(t_map *ret, t_var *var, int fd, char *buffer)
{
	int	i;

	i = 0;
	while (buffer != NULL)
	{
		ret->tiles[i] = (t_tile *)ft_calloc(ft_strlinelen(buffer),
				sizeof(t_tile));
		if (!ret->tiles[i])
			clean_and_exit("Malloc error in the parsing of the map", *var, 1);
		if ((int)ft_strlinelen(buffer) != ret->width)
			clean_and_exit("A line was longer or shorter than an other", *var,
				1);
		ret->width = ft_strlinelen(buffer);
		fill_line(buffer, ret, var, i);
		free(buffer);
		i++;
		buffer = get_next_line(fd);
	}
	return (i);
}

t_map	parse_map(char *map_path, t_var *var)
{
	t_map	ret;
	int		fd;
	int		i;
	char	*buffer;

	i = 0;
	ret.height = get_file_line_count(map_path);
	if (ret.height < 3)
		clean_and_exit("map too smal", *var, 1);
	fd = open(map_path, O_RDONLY);
	ret.nb_coins = 0;
	ret.tiles = (t_tile **)ft_calloc(ret.height, sizeof(t_tile *));
	if (!ret.tiles)
		clean_and_exit("Malloc error in the parsing of the map", *var, 1);
	buffer = get_next_line(fd);
	ret.width = ft_strlen(buffer) - 1;
	i = parse_map2(&ret, var, fd, buffer);
	close(fd);
	ret.height = i;
	return (ret);
}
