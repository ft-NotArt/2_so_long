/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_enemies.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 05:46:22 by anoteris          #+#    #+#             */
/*   Updated: 2024/12/16 06:46:09 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_enemy	*enemy_last(t_enemy *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	enemy_add_back(t_enemy **lst, t_enemy *new)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = new ;
	else
		enemy_last(*lst)->next = new ;
}

void	enemy_del_coord(t_game *game, t_enemy **enemy, int y, int x)
{
	t_enemy	*cur ;
	t_enemy	*nxt ;

	cur = *enemy ;
	if (cur->y == y && cur->x == x)
	{
		*enemy = cur->next ;
		game->maps->map[y][x] = '0' ;
		game->maps->enemy_number-- ;
		return (mlx_delete_image(game->mlx, cur->image), free_enemy(cur));
	}
	nxt = cur->next ;
	while (cur)
	{
		if (nxt->y == y && nxt->x == x)
		{
			cur->next = nxt->next ;
			game->maps->map[y][x] = '0' ;
			game->maps->enemy_number-- ;
			return (mlx_delete_image(game->mlx, nxt->image), free_enemy(nxt));
		}
		cur = nxt ;
		nxt = cur->next ;
	}
}
