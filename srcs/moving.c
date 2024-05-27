/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:39:27 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/27 14:04:45 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42.h"
#include "../so_long.h"

int left_and_right_movement(t_game *game, int button);
int up_and_down_movement(t_game *game, int button);
int check_exit_game(t_game *game, int y, int x);

void keys_moves(mlx_key_data_t keydata, void *param)
{
	int move;
	 t_game *game;

	 game = (t_game *)param;

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
	int exit_temp;

	if (game->map == NULL)
		exit(EXIT_FAILURE);
	temp = game->y;
	if (button == MLX_KEY_W || button == MLX_KEY_UP)
		temp--;
	else if (button == MLX_KEY_S || button == MLX_KEY_DOWN)
		temp++;
	if (temp >= 0 && temp < game->height_map && game->map[temp][game->x] != '1')
	{
		exit_temp = game->x;
		if (check_exit_game(game, temp, exit_temp) == 0)
			return (0);
		game->map[game->y][game->x] = '0';
		game->y = temp;
		game->map[game->y][game->x] = 'P';
		game->steps++;
		ft_printf("Steps: %d\n", game->steps);
		return (1);
	}
	return (0);
}

int left_and_right_movement(t_game *game, int button)
{
	int temp;
	int exit_temp;

	if (game->map == NULL)
		exit(EXIT_FAILURE);
	temp = game->x;
	if (button == MLX_KEY_A || button == MLX_KEY_LEFT)
		temp--;
	else if (button == MLX_KEY_D || button == MLX_KEY_RIGHT)
		temp++;
	if (temp >= 0 && temp < game->width_map && game->map[game->y][temp] != '1')
	{
		exit_temp = game->y;
		if (check_exit_game(game, exit_temp, temp) == 0)
			return (0);
		game->map[game->y][game->x] = '0';
		game->x = temp;
		game->map[game->y][game->x] = 'P';
		game->steps++;
		ft_printf("Steps: %d\n", game->steps);
		return (1);
	}
	return (0);
}
int check_exit_game(t_game *game, int y, int x)
{
	if (game->map[y][x] == 'E' && game->colletible_count == 0)
		{
			ft_printf("Congratulations Carlos!");
			mlx_terminate(game->mlx);
			free_map(game);
			exit(EXIT_SUCCESS);
		}
	else if (game->map[y][x] == 'E' && game->colletible_count != 0)
	{
		return (0);
	}
	return (1);
}