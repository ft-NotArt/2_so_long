/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:41:45 by anoteris          #+#    #+#             */
/*   Updated: 2024/12/19 12:50:37 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copy_map(char **map)
{
	char	**cpy ;
	int		height ;

	height = -1 ;
	while (map[++height])
		;
	cpy = malloc((height + 1) * sizeof(char *));
	cpy[height] = NULL ;
	while (--height >= 0)
		cpy[height] = ft_strdup(map[height]);
	return (cpy);
}

int	get_player_x(char **map)
{
	int	x ;
	int	y ;

	y = 0 ;
	while (map[++y])
	{
		x = 0 ;
		while (map[y][++x])
		{
			if (map[y][x] == 'P')
				return (x);
		}
	}
	return (-1);
}

int	get_player_y(char **map)
{
	int	x ;
	int	y ;

	y = 0 ;
	while (map[++y])
	{
		x = 0 ;
		while (map[y][++x])
		{
			if (map[y][x] == 'P')
				return (y);
		}
	}
	return (-1);
}

void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == 'E')
	{
		map[y][x] = 'f';
		return ;
	}
	if (map[y][x] == '1' || map[y][x] == 'f')
		return ;
	map[y][x] = 'f';
	flood_fill(map, x - 1, y);
	flood_fill(map, x + 1, y);
	flood_fill(map, x, y - 1);
	flood_fill(map, x, y + 1);
}

bool	check_flood_fill(t_map *map)
{
	char	**map_cpy ;
	int		x ;
	int		y ;

	map->player->x = get_player_x(map->map);
	map->player->y = get_player_y(map->map);
	map_cpy = copy_map(map->map);
	flood_fill(map_cpy, map->player->x, map->player->y);
	y = 0 ;
	while (map_cpy[++y])
	{
		x = 0 ;
		while (map_cpy[y][++x])
		{
			if (map_cpy[y][x] == 'C' || map_cpy[y][x] == 'E')
				return (free_str_array(map_cpy), false);
		}
	}
	free_str_array(map_cpy);
	return (true);
}
