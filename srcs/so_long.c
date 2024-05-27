/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:31:26 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/27 20:42:16 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42.h"
#include "../so_long.h"

int		arg_check(int argc, char *arg);
void	ft_load_image(t_game *game, mlx_image_t **image, const char *file_path);

void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_game				game;
	t_flood_fill_data	data;

	arg_check(argc, argv[1]);
	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&data, 0, sizeof(t_flood_fill_data));
	game.steps = 0;
	map_reader(&game, argv[1]);
	if (game.map == NULL)
		printf("empty\n");
	check_map_walls(&game, 0, 0, &data);
	game.mlx = mlx_init(game.width_map * 40, game.height_map * 40,
			"Carlos_on_fire", true);
	if (!game.mlx)
		ft_error();
	load_images(&game);
	ft_put_image_to_window(&game);
	mlx_key_hook(game.mlx, keys_moves, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_map(&game);
	return (EXIT_SUCCESS);
}

int	arg_check(int argc, char *arg)
{
	int	argv_len;

	if (argc != 2)
	{
		ft_printf("NOT THE RIGHT AMOUNT OF ARGUMENTS\n");
		exit(EXIT_FAILURE);
	}
	argv_len = ft_strlen(arg);
	if (ft_strncmp(arg + argv_len - 4, ".ber", 5) != 0)
	{
		ft_printf("NOT A MAP\n");
		exit(EXIT_FAILURE);
	}
	return (1);
}

void	ft_load_image(t_game *game, mlx_image_t **image, const char *file_path)
{
	mlx_texture_t	*temp_texture;

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
