/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:08:24 by anoteris          #+#    #+#             */
/*   Updated: 2024/12/10 15:13:34 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_game *game, t_player *player, int input_dir)
{
	if (input_dir == EAST)
	{
		check_player_tile(game, player->y, player->x + 1);
		move_east(game, PLAYER);
	}
	if (input_dir == SOUTH)
	{
		check_player_tile(game, player->y + 1, player->x);
		move_south(game, PLAYER);
	}
	if (input_dir == WEST)
	{
		check_player_tile(game, player->y, player->x - 1);
		move_west(game, PLAYER);
	}
	if (input_dir == NORTH)
	{
		check_player_tile(game, player->y - 1, player->x);
		move_north(game, PLAYER);
	}
	game->maps->player->pose = alternate_walking(game->maps->player->pose);
}

static void	align_or_move_player(t_game *game, t_player *player, int input_dir)
{
	if (player->orient != input_dir)
	{
		player->pose = STANDING ;
		player->orient = input_dir ;
	}
	else
		move_player(game, player, input_dir);
	player->last_action_time = mlx_get_time();
	update_player_sprite(game, player);
}

void	get_input_dir(keys_t key_press, t_game *game)
{
	if (key_press == MLX_KEY_D || key_press == MLX_KEY_RIGHT)
		align_or_move_player(game, game->maps->player, EAST);
	else if (key_press == MLX_KEY_S || key_press == MLX_KEY_DOWN)
		align_or_move_player(game, game->maps->player, SOUTH);
	else if (key_press == MLX_KEY_A || key_press == MLX_KEY_LEFT)
		align_or_move_player(game, game->maps->player, WEST);
	else if (key_press == MLX_KEY_W || key_press == MLX_KEY_UP)
		align_or_move_player(game, game->maps->player, NORTH);
}

void	player_attack(t_game *game, t_player *player)
{
	if (player->orient == EAST
		&& is_enemy(game->maps->map[player->y][player->x + 1]))
		enemy_del_coord(game, &game->maps->enemies, player->y, player->x + 1);
	if (player->orient == SOUTH
		&& is_enemy(game->maps->map[player->y + 1][player->x]))
		enemy_del_coord(game, &game->maps->enemies, player->y + 1, player->x);
	if (player->orient == WEST
		&& is_enemy(game->maps->map[player->y][player->x - 1]))
		enemy_del_coord(game, &game->maps->enemies, player->y, player->x - 1);
	if (player->orient == NORTH
		&& is_enemy(game->maps->map[player->y - 1][player->x]))
		enemy_del_coord(game, &game->maps->enemies, player->y - 1, player->x);
	player->pose = SWALLOWING ;
	player->last_action_time = mlx_get_time();
	update_player_sprite(game, player);
}
