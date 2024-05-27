/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:34:46 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/27 21:11:18 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	map_reader(t_game *game, char *map)
{
	char	*reader;
	int		y;

	game->map_fd = open(map, O_RDONLY);
	if (game->map_fd < 0)
	{
		ft_printf("Error\nCouldn't load the map!\n");
		exit(EXIT_FAILURE);
	}
	y = 0;
	game->map = ft_calloc(200, sizeof(char *));
	reader = get_next_line(game->map_fd);
	while (reader != NULL)
	{
		game->map[y] = ft_strdup(reader);
		free(reader);
		reader = get_next_line(game->map_fd);
		y++;
		game->height_map++;
	}
	close(game->map_fd);
	game->width_map = map_width(game->map[0]);
}

int	map_width(char *first_line)
{
	int	i;

	i = 0;
	while (first_line[i] != '\n')
		i++;
	return (i);
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->height_map)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}
