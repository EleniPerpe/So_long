/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:16:50 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/23 16:29:18 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	#include "../MLX42.h"
	#include "../so_long.h"

	#define TILE_SIZE 40
	
	void move_player(t_game *game, int height, int width);

	void ft_load_image(t_game *game, mlx_image_t **image, const char *file_path)
	{
		mlx_texture_t *temp_texture;
		
		temp_texture = mlx_load_png(file_path);
		if (temp_texture == NULL)
		{
			mlx_terminate(game->mlx);
			ft_error();
		}
		
		*image = mlx_texture_to_image(game->mlx, temp_texture);
		if (game->player == NULL)
		{
			mlx_terminate(game->mlx);
			ft_error();
		}
		
		mlx_delete_texture(temp_texture);
	}

	void load_images(t_game *game)
	{
		ft_load_image(game, &game->player, "player.png");
		ft_load_image(game, &game->collectible, "collect.png");
		ft_load_image(game, &game->exit, "exit.png");
		ft_load_image(game, &game->floor, "floor.png");
		ft_load_image(game, &game->wall, "wall.png");
	}

	void ft_put_image_to_window(t_game *game)
	{
		int i;
		int j;

		load_images(game);
		i = 0;
		game->colletible_count = 0;

		while (i < game->height_map)
		{
			j = 0;
			while (j < game->width_map)
			{
				if (game->map[i][j] == '1') {
					mlx_image_to_window(game->mlx, game->wall, j * TILE_SIZE, i * TILE_SIZE);
				}
				else if (game->map[i][j] == '0')
					mlx_image_to_window(game->mlx, game->floor, j * TILE_SIZE, i * TILE_SIZE);
				else if (game->map[i][j] == 'P')
					move_player(game, i, j);
				else if (game->map[i][j] == 'C')
				{
					game->colletible_count++;
					mlx_image_to_window(game->mlx, game->floor, j * TILE_SIZE, i * TILE_SIZE);
					mlx_image_to_window(game->mlx, game->collectible, j * TILE_SIZE, i * TILE_SIZE);
				}
				else if (game->map[i][j] == 'E')
				{
					mlx_image_to_window(game->mlx, game->floor, j * TILE_SIZE, i * TILE_SIZE);
					mlx_image_to_window(game->mlx, game->exit, j * TILE_SIZE, i * TILE_SIZE);
				}
				j++;
			}
			i++;
		}
		ft_printf("Collectibles : %d\n", game->colletible_count);
	}

void move_player(t_game *game, int height, int width)
{
	mlx_image_to_window(game->mlx, game->floor, width * TILE_SIZE, height * TILE_SIZE);
	mlx_image_to_window(game->mlx, game->player, width * TILE_SIZE, height * TILE_SIZE);
	game->y = height;
	game->x = width;
}