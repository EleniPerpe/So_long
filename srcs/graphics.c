/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:16:50 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/27 19:11:59 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42.h"
#include "../so_long.h"

#define TILE_SIZE 40

void	move_player(t_game *game, int height, int width);
void	put_collectible(t_game *game, int height, int width);
void	put_exit(t_game *game, int height, int width);

void	load_images(t_game *game)
{
	ft_load_image(game, &game->player, "images/player.png");
	ft_load_image(game, &game->collectible, "images/collect.png");
	ft_load_image(game, &game->exit, "images/exit.png");
	ft_load_image(game, &game->floor, "images/floor.png");
	ft_load_image(game, &game->wall, "images/wall.png");
}

void	ft_put_image_to_window(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	game->c_c = 0;
	while (++i < game->height_map)
	{
		j = -1;
		while (++j < game->width_map)
		{
			if (game->map[i][j] == '1')
				mlx_image_to_window(game->mlx, game->wall,
					j * TILE_SIZE, i * TILE_SIZE);
			else if (game->map[i][j] == '0')
				mlx_image_to_window(game->mlx, game->floor,
					j * TILE_SIZE, i * TILE_SIZE);
			else if (game->map[i][j] == 'P')
				move_player(game, i, j);
			else if (game->map[i][j] == 'C')
				put_collectible(game, i, j);
			else if (game->map[i][j] == 'E')
				put_exit(game, i, j);
		}
	}
	ft_printf("Collectibles : %d\n", game->c_c);
}

void	move_player(t_game *game, int height, int width)
{
	mlx_image_to_window(game->mlx, game->floor, width * TILE_SIZE,
		height * TILE_SIZE);
	mlx_image_to_window(game->mlx, game->player, width * TILE_SIZE,
		height * TILE_SIZE);
	game->y = height;
	game->x = width;
}

void	put_collectible(t_game *game, int height, int width)
{
	game->c_c++;
	mlx_image_to_window(game->mlx, game->floor, width * TILE_SIZE,
		height * TILE_SIZE);
	mlx_image_to_window(game->mlx, game->collectible, width * TILE_SIZE,
		height * TILE_SIZE);
}

void	put_exit(t_game *game, int height, int width)
{
	mlx_image_to_window(game->mlx, game->floor, width * TILE_SIZE,
		height * TILE_SIZE);
	mlx_image_to_window(game->mlx, game->exit, width * TILE_SIZE,
		height * TILE_SIZE);
}
