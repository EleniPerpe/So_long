/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:31:26 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/16 19:41:16 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../so_long.h"

// Written by Bruh

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../MLX42.h"
#define WIDTH 260
#define HEIGHT 160

void key_hook(mlx_key_data_t keycode, void *param);

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}


int32_t	main(void)
{
	mlx_texture_t *texture;
	mlx_image_t *image;

	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Carlos_on_fire", true);
	if (!mlx)
		ft_error();
		
	texture = mlx_load_png("lala.png");
	if (texture == NULL)
	{
		mlx_terminate(mlx);
		ft_error();
	}
	
	image = mlx_texture_to_image(mlx, texture);
	if (image == NULL)
	{
		mlx_terminate(mlx);
		ft_error();
	}
	
	mlx_delete_texture(texture);
	/* Do stuff */

	// mlx_image_t* image = mlx_new_image(mlx, 256, 256);
	if (!image || (mlx_image_to_window(mlx, image, 0, 0) < 0))
	{
		mlx_delete_image(mlx, image);
		mlx_terminate(mlx);
		ft_error();
	}

	mlx_key_hook(mlx, key_hook, mlx);	
	// mlx_key_hook(mlx, key_hook, mlx);

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

void key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t *mlx = (mlx_t *)param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{	
		mlx_terminate(mlx);
		exit(EXIT_SUCCESS);
	}
}
// int	main(int argc, char **argv)
// {
// 	int	argv_len;
// 	int	map_fd;

// 	// argv_len = ft_strlen(argv[1]);
// 	// if (argc != 2)
// 	// {
// 	// 	printf("NOT THE RIGHT AMOUNT OF ARGUMENTS\n");
// 	// 	exit(EXIT_FAILURE);
// 	// }
// 	// if (ft_strncmp(argv[1][argv_len - 4], ".ber", 5) != 0)
// 	// {
// 	// 	printf("NOT A MAP\n");
// 	// 	exit(EXIT_FAILURE);
// 	// }
// 	// map_fd = open(argv[1], O_RDONLY);
// 	// if (map_fd < 0)
// 	// {
// 	// 	printf("COULD NOT OPEN FILE.\n");
// 	// 	exit(EXIT_FAILURE);
// 	// }
	
// }

