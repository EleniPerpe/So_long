/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:31:26 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/27 13:56:13 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42.h"
#include "../so_long.h"

// void key_hook(mlx_key_data_t keycode, void *param);

void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	ft_printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}


int	main(int argc, char **argv)
{
	int argv_len;
	t_game game;
	
	if (argc != 2)
	{
		ft_printf("NOT THE RIGHT AMOUNT OF ARGUMENTS\n");
		exit(EXIT_FAILURE);
	}
	argv_len = ft_strlen(argv[1]);	
	if (ft_strncmp(argv[1]+ argv_len - 4, ".ber", 5) != 0)
	{
		ft_printf("NOT A MAP\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(&game, 0, sizeof(t_game));
	game.steps = 0;
	map_reader(&game, argv[1]);
	if (game.map ==  NULL)
		printf("empty\n");
	check_map_walls(&game, 0, 0);
	game.mlx = mlx_init(game.width_map * 40, game.height_map * 40, "Carlos_on_fire", true);
	if (!game.mlx)
		ft_error();
	load_images(&game);
	ft_put_image_to_window(&game);
	mlx_key_hook(game.mlx, keys_moves, &game);
	ft_hook(game.mlx);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_map(&game);
	return (EXIT_SUCCESS);
}
