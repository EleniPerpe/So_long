/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:39:27 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/21 16:55:36 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42.h"
#include "../so_long.h"

int left_and_right_movement(t_game *game, int button);
int up_and_down_movement(t_game *game, int button);

void keys_moves(mlx_key_data_t keydata, t_game *game)
{
	int move;

	move = 0;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{	
		mlx_terminate(game->mlx);
		exit(EXIT_SUCCESS);
	}
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		&& keydata.action == MLX_PRESS)
	{
		move = up_and_down_movement(game, keydata.key);
	}
	if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		&& keydata.action == MLX_PRESS)
	{
		move = left_and_right_movement(game, keydata.key);
	}
	if (move)
		ft_put_image_to_window(game);
}
int up_and_down_movement(t_game *game, int button)
{
	int temp;

	temp = game->y;
	if (button == MLX_KEY_W || button == MLX_KEY_UP)
		temp--;
	else if (button == MLX_KEY_S || button == MLX_KEY_DOWN)
		temp++;
	if (temp >= 0 && temp < game->height_map && game->map[temp][game->x] != '1')
	{
		game->map[game->y][game->x] = '0';
		game->y = temp;
		game->map[game->y][game->x] = 'P';
		if (game->map[temp][game->x] == 'C')
		{
			game->colletible_count--;
			printf("Collectibles : %d", game->colletible_count);
		}
		return (1);
	}
	return (0);
}

int left_and_right_movement(t_game *game, int button)
{
	int temp;

	temp = game->x;
	if (button == MLX_KEY_A || button == MLX_KEY_LEFT)
		temp--;
	else if (button == MLX_KEY_D || button == MLX_KEY_RIGHT)
		temp++;
	if (temp >= 0 && temp < game->width_map && game->map[game->y][temp] != '1')
	{
		game->map[game->y][game->x] = '0';
		game->x = temp;
		game->map[game->y][game->x] = 'P';
		if (game->map[game->y][game->x] == 'C')
		{
			game->colletible_count--;
			printf("Collectibles : %d", game->colletible_count);
		}
		return (1);
	}
	return (0);
}