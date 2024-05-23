#include "../so_long.h"

void map_reader(t_game *game, char *map)
{
	char *reader;

	game->map_fd = open(map, O_RDONLY);

	if (game->map_fd < 0)
	{
		ft_printf("Couldn't load the map!\n");
		exit(EXIT_FAILURE);
	}
	int y = 0;
	game->map = ft_calloc(200, sizeof(char *));
	while (1)
	{
		reader = get_next_line(game->map_fd);
		if (!reader)
			break;
		game->height_map++;
		game->map[y] = ft_strdup(reader);
		free(reader);
		y++;
	}
	close(game->map_fd);
	game->width_map = map_width(game->map[1]);
}

int map_width(char *first_line)
{
	int i;

	i = 0;
	while (first_line[i] != '\n')
		i++;
	return (i);
}

void free_map(t_game *game)
{
	int i;

	i = 0;
	while (i < game->height_map)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}