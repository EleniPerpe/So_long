#include "../so_long.h"

void map_reader(t_game *game, char *map)
{
	char *reader;

	game->map_fd = open(map, O_RDONLY);

	if (game->map_fd < 0)
	{
		printf("Couldn't load the map!\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		reader = get_next_line(game->map_fd);
		if (add_map_line(game, reader) == 0)
			break ; 
	}
	close(game->map_fd);
	game->width_map = map_width(game->map[1]);
}

int add_map_line(t_game *game, char *next_line)
{
	char **temp_map;
	int i;

	if (next_line == NULL)
		return (0);
	game->height_map++;
	temp_map = (char **)malloc((game->height_map + 1) * sizeof(char *));
	temp_map[game->height_map] = NULL;
	i = 0;
	while (i < game->height_map - 1)
	{
		temp_map[i] = game->map[i];
		i++;
	}
	temp_map[i] = next_line;
	game->map = temp_map;
	return (1);
}

int map_width(char *first_line)
{
	int i;

	i = 0;
	while (first_line[i] != '\n')
		i++;
	return (i);
}