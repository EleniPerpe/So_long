/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:31:26 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/23 12:34:26 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../so_long.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../MLX42.h"
#include "../so_long.h"
#define WIDTH 800
#define HEIGHT 800

void key_hook(mlx_key_data_t keycode, void *param);

void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}


int	main(int argc, char **argv)
{
	int argv_len;
	t_game game;
	
	if (argc != 2)
	{
		printf("NOT THE RIGHT AMOUNT OF ARGUMENTS\n");
		exit(EXIT_FAILURE);
	}
	argv_len = ft_strlen(argv[1]);	
	if (ft_strncmp(argv[1]+ argv_len - 4, ".ber", 5) != 0)
	{
		printf("NOT A MAP\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(&game, 0, sizeof(t_game));
	game.steps = 0;
	map_reader(&game, argv[1]);
	printf("Width : %d, Height : %d\n", game.width_map, game.height_map);
	game.mlx = mlx_init(game.height_map * 40, game.height_map * 40, "Carlos_on_fire", false);
	if (!game.mlx)
		ft_error();

	ft_put_image_to_window(&game);
	printf("asd!\n");
	
	mlx_key_hook(game.mlx, keys_moves, &game);	
	// mlx_key_hook(mlx, key_hook, mlx);

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	// mlx_loop_hook(game.mlx, ft_hook, game.mlx);
	ft_hook(game.mlx);
	mlx_loop(game.mlx);
	// free map
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
