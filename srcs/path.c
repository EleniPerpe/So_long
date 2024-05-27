/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:20:36 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/27 15:30:01 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_error_exit(const char *msg, int code);
void	ft_flood_fill(char **map, t_game *game, int x, int y, int *c, int *exit);

void	ft_check_player_paths(t_game *game)
{
	int		collect;
	int		exit;
	int		i;
	int		j;
	char	**tmp_map;

	collect = 0;
	exit = 0;
	malloc(game->height_map * sizeof(char *));
	if (tmp_map == NULL)
	{
		ft_error_exit("Memory allocation failed", 1);
		free_map(game);
	}
	i = 0;
	j = 0;
	while (i < game->height_map)
	{
		tmp_map[i] = strdup(game->map[i]);
		if (tmp_map[i] == NULL)
		{
			while (j < i)
			{
				free(tmp_map[i]);
				j++;
			}
			free(tmp_map);
		}
		i++;
	}
	ft_flood_fill(tmp_map, game, game->flood_x, game->flood_y, &collect, &exit);
	i = 0;
	while (i < game->height_map)
	{
		free(tmp_map[i]);
		i++;
	}
	free(tmp_map);
	if (collect != game->colletible_count && exit == 0)
	{
		ft_error_exit("exit and collectible(s) not reachable", 0);
	}
	if (collect != game->colletible_count)
	{
		ft_error_exit("collectible(s) not reachable", 0);
	}
	if (exit == 0)
	{
		ft_error_exit("exit is not reachable", 0);
	}
}

void	ft_flood_fill(char **map, t_game *game, int x, int y, int *c, int *exit)
{
	if (x < 0 || x >= game->height_map || y < 0 || y >= game->width_map)
	{
		return ;
	}
	if (map[x][y] == '1')
	{
		return ;
	}
	if (map[x][y] == 'E')
	{
		(*exit)++;
		return ;
	}
	if (map[x][y] == 'C')
	{
		(*c)++;
	}
	map[x][y] = '1';
	ft_flood_fill(map, game, x - 1, y, c, exit);
	ft_flood_fill(map, game, x + 1, y, c, exit);
	ft_flood_fill(map, game, x, y - 1, c, exit);
	ft_flood_fill(map, game, x, y + 1, c, exit);
}

void	ft_error_exit(const char *msg, int code)
{
	fprintf(stderr, "%s\n", msg);
	exit(code);
}
