/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:20:36 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/29 12:02:32 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_setup_temp_map(t_game *game, char ***temp_map);
void	ft_flood_fill(char **map, int x, int y, t_flood_fill_data *data);
void	ft_check_paths_and_cleanup(t_game *game, t_flood_fill_data *data,
			char **temp_map);

void	ft_check_player_paths(t_game *game, t_flood_fill_data *data)
{
	char	**temp_map;

	data->game = game;
	data->collectibles = 0;
	data->exit = 0;
	ft_setup_temp_map(game, &temp_map);
	ft_flood_fill(temp_map, game->flood_x, game->flood_y, data);
	ft_check_paths_and_cleanup(game, data, temp_map);
}

void	ft_setup_temp_map(t_game *game, char ***temp_map)
{
	int		i;
	int		j;

	*temp_map = malloc(game->height_map * sizeof(char *));
	if (*temp_map == NULL)
		ft_error_exit(game, "Error\nMemory allocation failed");
	i = -1;
	while (++i < game->height_map)
	{
		(*temp_map)[i] = strdup(game->map[i]);
		if ((*temp_map)[i] == NULL)
		{
			j = -1;
			while (++j < i)
				free((*temp_map)[j]);
			free(*temp_map);
			ft_error_exit(game, "Error\nMemory allocation failed");
		}
	}
}

void	ft_check_paths_and_cleanup(t_game *game, t_flood_fill_data *data,
		char **temp_map)
{
	int	i;

	i = -1;
	while (++i < game->height_map)
		free(temp_map[i]);
	free(temp_map);
	if (data->collectibles != game->c_c && data->exit == 0)
		ft_error_exit(game,
			"Error\nExit and collectible(s) are not reachable!");
	if (data->collectibles != game->c_c)
		ft_error_exit(game, "Error\nCollectible(s) are not reachable!");
	if (data->exit == 0)
		ft_error_exit(game, "Error\nExit is not reachable!");
}

void	ft_flood_fill(char **map, int x, int y, t_flood_fill_data *data)
{
	if (x < 0 || x >= data->game->height_map
		|| y < 0 || y >= data->game->width_map)
		return ;
	if (map[x][y] == '1')
		return ;
	if (map[x][y] == 'E')
	{
		data->exit++;
		return ;
	}
	if (map[x][y] == 'C')
		data->collectibles++;
	map[x][y] = '1';
	ft_flood_fill(map, x - 1, y, data);
	ft_flood_fill(map, x + 1, y, data);
	ft_flood_fill(map, x, y - 1, data);
	ft_flood_fill(map, x, y + 1, data);
}

void	ft_error_exit(t_game *game, const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	if (game->mlx)
		mlx_terminate(game->mlx);
	free_map(game);
	exit(EXIT_FAILURE);
}
