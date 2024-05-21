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
		int x;
		int y;

		load_images(game);
		i = 0;
		j = 0;

		// mlx_resize_image(game->player, 60, 60);
		while (i < game->height_map)
		{
			j = 0;
			while (j < game->width_map)
			{
				x = j * TILE_SIZE;
				y = i * TILE_SIZE;
				if (game->map[i][j] == '1')
					mlx_image_to_window(game->mlx, game->wall, x, y);
				else if (game->map[i][j] == '0')
					mlx_image_to_window(game->mlx, game->floor, x, y);
				else if (game->map[i][j] == 'P')
					move_player(game, i, j);
				else if (game->map[i][j] == 'C')
				{
					game->colletible_count++;
					mlx_image_to_window(game->mlx, game->floor, x, y);
					mlx_image_to_window(game->mlx, game->collectible, x, y);
				}
				else if (game->map[i][j] == 'E')
				{
					mlx_image_to_window(game->mlx, game->floor, x, y);
					mlx_image_to_window(game->mlx, game->exit, x, y);
				}
				j++;
			}
			i++;
		}
	}

void move_player(t_game *game, int height, int width)
{
	mlx_image_to_window(game->mlx, game->floor, width * TILE_SIZE, height * TILE_SIZE);
	mlx_image_to_window(game->mlx, game->player, width * TILE_SIZE, height * TILE_SIZE);
	game->y = height;
	game->x = width;
}