/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uanglade <uanglade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:24:01 by uanglade          #+#    #+#             */
/*   Updated: 2025/02/12 03:13:26 by uanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	_check(t_var var, t_map map)
{
	int	i;
	int	j;
	int	c;
	int	a;
	int	b;

	i = -1;
	c = 0;
	a = 0;
	b = 0;
	while (++i < map.height)
	{
		j = -1;
		while (++j < map.width)
		{
			if (map.tiles[i][j].type != FULL && (i == map.height - 1
				|| j == map.width - 1 || i == 0 || j == 0))
				return (clean_and_exit("Map not enclosed", var, 1));
			c += (map.tiles[i][j].type == EXIT);
			a += (map.tiles[i][j].type == START);
			b += (map.tiles[i][j].type == COLLECTIBLE);
		}
	}
	if (c != 1 || a != 1 || b == 0)
		return (clean_and_exit("More or less than one start or exit", var, 1));
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
	if (can_go(map, point, LEFT) && map.tiles[point.y][point.x
		- 1].is_accesible == 0)
	{
		map.tiles[point.y][point.x - 1].is_accesible = 1;
		flood_fill(map.tiles[point.y][point.x - 1], map);
	}
	if (can_go(map, point, RIGHT) && map.tiles[point.y][point.x
		+ 1].is_accesible == 0)
	{
		map.tiles[point.y][point.x + 1].is_accesible = 1;
		flood_fill(map.tiles[point.y][point.x + 1], map);
	}
	if (can_go(map, point, UP) && map.tiles[point.y
			- 1][point.x].is_accesible == 0)
	{
		map.tiles[point.y - 1][point.x].is_accesible = 1;
		flood_fill(map.tiles[point.y - 1][point.x], map);
	}
	if (can_go(map, point, DOWN) && map.tiles[point.y
			+ 1][point.x].is_accesible == 0)
	{
		map.tiles[point.y + 1][point.x].is_accesible = 1;
		flood_fill(map.tiles[point.y + 1][point.x], map);
	}
}

int	is_map_valid(t_map map, t_player player, t_var var)
{
	int	i;
	int	j;
	int	temp;

	_check(var, map);
	temp = map.nb_coins;
	flood_fill((t_tile){player.x, player.y, EMPTY, 1}, map);
	i = -1;
	while (++i < map.height)
	{
		j = -1;
		while (++j < map.width)
		{
			if (map.tiles[i][j].type != FULL && (i == map.height
					|| j == map.width || i == 0 || j == 0))
				return (clean_and_exit("Map not enclosed", var, 1), 0);
			if (map.tiles[i][j].is_accesible == 1
				&& (map.tiles[i][j].type == COLLECTIBLE
					|| map.tiles[i][j].type == EXIT))
				temp--;
		}
	}
	return (temp == -1);
}
