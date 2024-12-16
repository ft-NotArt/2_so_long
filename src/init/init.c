/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 22:46:43 by anoteris          #+#    #+#             */
/*   Updated: 2024/12/16 04:47:58 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	set_attack_coord(t_attack *attack, int x, int y)
{
	attack->x = x ;
	attack->y = y ;
	if (attack->orient == EAST)
		attack->x++ ;
	if (attack->orient == SOUTH)
		attack->y++ ;
	if (attack->orient == WEST)
		attack->x-- ;
	if (attack->orient == NORTH)
		attack->y-- ;
}

t_attack	*attack_init(type type, int x, int y, orient orient)
{
	t_attack	*attack ;

	attack = malloc(sizeof(t_attack));
	attack->frame = FRAME1 ;
	attack->type = type ;
	attack->orient = orient ;
	set_attack_coord(attack, x, y);
	attack->image = NULL ;
	return (attack);
}

t_player	*player_init(void)
{
	t_player	*player ;

	player = malloc(sizeof(t_player));
	player->image = NULL ;
	player->x = 0 ;
	player->y = 0 ;
	player->orient = EAST ;
	player->status = STANDING ;
	player->step_count = 0 ;
	player->attack = NULL ;
	player->last_action_time = 0 ;
	return (player);
}

t_map	*map_init(char *map_file)
{
	t_map	*map ;

	map = malloc(sizeof(t_map));
	map->map = read_map(map_file);
	map->width = 0 ;
	map->height = 0 ;
	map->enemy_number = 0 ;
	map->player = player_init();
	map->step_count_img = NULL ;
	map->enemies = NULL ;
	map->next = NULL ;
	return (map);
}

static void	enemy_set_attacks(t_enemy *enemy, t_map *map, int x, int y)
{
	enemy->attack_set[0] = 0 ;
	enemy->attack_set[1] = 0 ;
	enemy->attack_set[2] = 0 ;
	if (map->map[y][x] == DEE)
		enemy->attack_set[1] = 1;
	else
		enemy->attack_set[2] = 1;
}

t_enemy	*enemy_init(t_map *map, int x, int y)
{
	t_enemy		*enemy ;
	static int	orient = 0 ;

	enemy = malloc(sizeof(t_enemy));
	enemy->image = NULL ;
	enemy->type = map->map[y][x] ;
	enemy->x = x ;
	enemy->y = y ;
	enemy->orient = (orient % 4);
	orient++ ;
	enemy_set_attacks(enemy, map, x, y);
	enemy->attack = NULL ;
	enemy->next = NULL ;
	return (enemy);
}

t_game	*game_init(t_map *maps)
{
	t_game	*game ;

	game = malloc(sizeof(t_game));
	game->maps = maps ;
	game->mlx = mlx_init(game->maps->width * BITS,
			(game->maps->height + 2) * BITS,
			"TEST", false);
	game->player_attack_set[0] = 1;
	game->player_attack_set[1] = 0;
	game->player_attack_set[2] = 0;
	return (game);
}
