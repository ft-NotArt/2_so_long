/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_kill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:00:40 by anoteris          #+#    #+#             */
/*   Updated: 2024/12/16 15:44:38 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_doo_attack_east(t_game *game, t_player *player)
{
	if (player->attack->frame == FRAME1
		&& is_enemy(game->maps->map[player->attack->y - 1][player->attack->x]))
		enemy_del(game, &game->maps->enemies,
			player->attack->y - 1, player->attack->x);
	else if (player->attack->frame == FRAME2
		&& is_enemy(game->maps->map[player->attack->y][player->attack->x + 1]))
		enemy_del(game, &game->maps->enemies,
			player->attack->y, player->attack->x + 1);
	else if (player->attack->frame == FRAME3
		&& is_enemy(game->maps->map[player->attack->y + 1][player->attack->x]))
		enemy_del(game, &game->maps->enemies,
			player->attack->y + 1, player->attack->x);
}

static void	check_doo_attack_south(t_game *game, t_player *player)
{
	if (player->attack->frame == FRAME1
		&& is_enemy(game->maps->map[player->attack->y][player->attack->x + 1]))
		enemy_del(game, &game->maps->enemies,
			player->attack->y, player->attack->x + 1);
	else if (player->attack->frame == FRAME2
		&& is_enemy(game->maps->map[player->attack->y + 1][player->attack->x]))
		enemy_del(game, &game->maps->enemies,
			player->attack->y + 1, player->attack->x);
	else if (player->attack->frame == FRAME3
		&& is_enemy(game->maps->map[player->attack->y][player->attack->x - 1]))
		enemy_del(game, &game->maps->enemies,
			player->attack->y, player->attack->x - 1);
}

static void	check_doo_attack_west(t_game *game, t_player *player)
{
	if (player->attack->frame == FRAME1
		&& is_enemy(game->maps->map[player->attack->y + 1][player->attack->x]))
		enemy_del(game, &game->maps->enemies,
			player->attack->y + 1, player->attack->x);
	else if (player->attack->frame == FRAME2
		&& is_enemy(game->maps->map[player->attack->y][player->attack->x - 1]))
		enemy_del(game, &game->maps->enemies,
			player->attack->y, player->attack->x - 1);
	else if (player->attack->frame == FRAME3
		&& is_enemy(game->maps->map[player->attack->y - 1][player->attack->x]))
		enemy_del(game, &game->maps->enemies,
			player->attack->y - 1, player->attack->x);
}

static void	check_doo_attack_north(t_game *game, t_player *player)
{
	if (player->attack->frame == FRAME1
		&& is_enemy(game->maps->map[player->attack->y][player->attack->x - 1]))
		enemy_del(game, &game->maps->enemies,
			player->attack->y, player->attack->x - 1);
	else if (player->attack->frame == FRAME2
		&& is_enemy(game->maps->map[player->attack->y - 1][player->attack->x]))
		enemy_del(game, &game->maps->enemies,
			player->attack->y - 1, player->attack->x);
	else if (player->attack->frame == FRAME3
		&& is_enemy(game->maps->map[player->attack->y][player->attack->x + 1]))
		enemy_del(game, &game->maps->enemies,
			player->attack->y, player->attack->x + 1);
}

void	check_player_attack(t_game *game, t_player *player)
{
	if (player->attack->type == DEE)
	{
		if (is_enemy(game->maps->map[player->attack->y][player->attack->x]))
		{
			enemy_del(game, &game->maps->enemies,
				player->attack->y, player->attack->x);
		}
	}
	else
	{
		if (is_enemy(game->maps->map[player->attack->y][player->attack->x]))
		{
			enemy_del(game, &game->maps->enemies,
				player->attack->y, player->attack->x);
		}
		if (player->attack->orient == EAST)
			check_doo_attack_east(game, player);
		if (player->attack->orient == SOUTH)
			check_doo_attack_south(game, player);
		if (player->attack->orient == WEST)
			check_doo_attack_west(game, player);
		if (player->attack->orient == NORTH)
			check_doo_attack_north(game, player);
	}
}