/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:58:47 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/27 19:30:12 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "Libft/libft.h"
# include "Get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include "MLX42.h"

typedef struct s_game
{
	int			map_fd;
	int			height_map;
	int			width_map;
	int			p_c;
	int			c_c;
	int			e_c;
	int			steps;
	int			x;
	int			y;
	int			flood_x;
	int			flood_y;
	char		**map;
	mlx_image_t	*player;
	mlx_image_t	*collectible;
	mlx_image_t	*exit;
	mlx_image_t	*floor;
	mlx_image_t	*wall;
	mlx_t		*mlx;
}	t_game;

void	ft_put_image_to_window(t_game *game);
void	ft_load_image(t_game *game, mlx_image_t **image, const char *file_path);
void	ft_error(void);
void	map_reader(t_game *game, char *map);
int		map_width(char *first_line);
void	keys_moves(mlx_key_data_t keydata, void *param);
void	check_map_walls(t_game *game, int i, int j);
void	free_map(t_game *game);
void	load_images(t_game *game);
void	ft_check_player_paths(t_game *game);
void	ft_error_exit(t_game *game, const char *msg);

#endif