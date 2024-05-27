/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:16:26 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/27 20:32:54 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "../MLX42.h"

void	check_map_square(t_game *game);
void	check_valid_assets(t_game *game);
void	find_player_position(t_game *game);

void	check_map_walls(t_game *game, int i, int j, t_flood_fill_data *data)
{
	while (i < game->height_map)
	{
		j = 0;
		while (j < game->width_map)
		{
			if ((i == 0 || i == game->height_map - 1) && game->map[i][j] != '1')
				ft_error_exit(game, "There are no walls around!");
			if ((j == 0 || j == game->width_map - 1) && game->map[i][j] != '1')
				ft_error_exit(game, "There are no walls around!");
			j++;
		}
		i++;
	}
	check_map_square(game);
	check_valid_assets(game);
	find_player_position(game);
	ft_check_player_paths(game, data);
}

void	check_map_square(t_game *game)
{
	int	i;
	int	j;

	i = 0;
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

void	check_valid_assets(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->height_map)
	{
		j = -1;
		while (++j < game->width_map)
		{
			if (game->map[i][j] == 'E')
				game->e_c++;
			else if (game->map[i][j] == 'P')
				game->p_c++;
			else if (game->map[i][j] == 'C')
				game->c_c++;
		}
	}
	if (game->e_c != 1 || game->p_c != 1 || game->c_c < 1)
	{
		ft_printf("Not the correct amount of assets so the game to start!\n");
		if (game->mlx)
			mlx_terminate(game->mlx);
		free_map(game);
		exit(EXIT_FAILURE);
	}
}

void	find_player_position(t_game *game)
{
	int	i;
	int	j;

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
}
