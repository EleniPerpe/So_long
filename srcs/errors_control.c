/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:16:26 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/27 14:20:24 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "../MLX42.h"

void check_map_walls(t_game *game, int i, int j)
{
	while (i < game->height_map)
	{
		j = 0;
		while (j < game->width_map)
		{
			if ((i == 0 || i == game->height_map - 1) && game->map[i][j] != '1')
			{
				ft_printf("No walls! 2\n");
				if (game->mlx)
					mlx_terminate(game->mlx);
				free_map(game);
				exit(EXIT_FAILURE);
			}
			if ((j == 0 || j == game->width_map - 1) && game->map[i][j] != '1')
			{
				if (game->mlx)
					mlx_terminate(game->mlx);
				ft_printf("No walls! 1\n");
				free_map(game);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	printf("hey\n");
	check_map_square(game);
	check_valid_assets(game);
	find_player_position(game);
}

void check_map_square(t_game *game)
{
	int i = 0;
	int j = 0;
	
	while (i < game->height_map)
	{
		j = 0;
		while (game->map[i][j] != '\n' && game->map[i][j] != '\0')
		{
			j++;
		}
		if (j != game->width_map)
		{
			ft_printf("No square!\n");
			if (game->mlx)
					mlx_terminate(game->mlx);
			free_map(game);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void check_valid_assets(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->height_map)
	{
		j = 0;
		while (j < game->width_map)
		{
			if (game->map[i][j] == 'E')
				game->exit_count++;
			else if (game->map[i][j] == 'P')
				game->player_count++;
			else if (game->map[i][j] == 'C')
				game->colletible_count++;
			j++;
		}
		i++;
		ft_printf("P = %d, C = %d, E = %d\n", game->player_count, game->colletible_count, game->exit_count);
	}
	if (game->exit_count != 1 || game->player_count != 1 || game->colletible_count < 1)
	{
			ft_printf("Not the right amount of assets so the game to start!\n");
			if (game->mlx)
					mlx_terminate(game->mlx);
			free_map(game);
			exit(EXIT_FAILURE);
	}
}

void find_player_position(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->height_map)
	{
		j = 0;
		while (j < game->width_map)
		{
			if (game->map[i][j] == 'P')
			{
				game->flood_x = i;
				game->flood_y = j;
			}
			j++;
		}
		i++;
	}
	ft_printf("Position heigth : %d, Position width : %d\n", game->flood_x, game->flood_y);
}