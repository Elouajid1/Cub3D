#include "../cub3d.h"

int is_identifier(char c, t_game *game)
{
    if (c == 'N')
        game->config.seen_id[0]++;
    else if (c == 'S')
        game->config.seen_id[1]++;
    else if (c == 'W')
        game->config.seen_id[2]++;
    else if (c == 'E')
        game->config.seen_id[3]++;
    else if (c == 'C')
        game->config.seen_id[4]++;
    else if (c == 'F')
        game->config.seen_id[5]++;
    else
        return (ERROR);
    return (SUCCESS);
}

int line_is_walled(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '1')
            return (ERROR);
        i++;
    }
    return (SUCCESS);
}

int all_lines_are_walled(size_t height, char **map_grid)
{
    int j;

    if (!map_grid || !map_grid[0]
        || line_is_walled(map_grid[0]) != SUCCESS
        || line_is_walled(map_grid[height - 1]) != SUCCESS)
        return (map_is_not_fully_walled());
    j = 0;
    while (map_grid[j])
    {
        int i = 0;
        size_t len = ft_strlen(map_grid[j]);
        while (map_grid[j][i] == ' ' || map_grid[j][i] == '\t')
            i++;
        if (map_grid[j][i] != '1')
            return (line_isnt_start_walled(j));
        int end = len - 1;
        while (end >= 0 && (map_grid[j][end] == ' ' || map_grid[j][end] == '\t'))
            end--;
        if (end >= 0 && map_grid[j][end] != '1')
            return (line_isnt_end_walled(j));
        j++;
    }
    return (SUCCESS);
}

char *pad_line(char *line, size_t max_len)
{
    size_t  len;
    size_t  i;

    len = ft_strlen(line);
    if (len >= max_len)
        return ft_strdup(line);
    char *padded = malloc(max_len + 1);
    if (!padded)
        return NULL;
    ft_strcpy(padded, line);
    i = len;
    while (i < max_len)
        padded[i++] = ' ';

    padded[max_len] = '\0';
    return padded;
}


int     pad_map(t_game *game)
{
    size_t  i;
    
    i = 0;
    game->config.map.flood_fill_copy = malloc(sizeof(char *) * game->config.map.height + 1);
    if (!game->config.map.flood_fill_copy)
        return (malloc_failed());
    while (i < game->config.map.height)
    {
        game->config.map.flood_fill_copy[i] = pad_line(game->config.map.map_grid[i], game->config.map.width);
        if (!game->config.map.flood_fill_copy[i])
            return (malloc_failed());
        i++;
    }
    game->config.map.flood_fill_copy[i] = NULL;
    return (SUCCESS);
}

bool is_walkable(char c)
{
    return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool if_next_char_isnt_wall(char **map, int i, int j, int height, int width)
{
    if (i > 0 && is_walkable(map[i - 1][j]))
        return (true);
    if (i < height - 1 && is_walkable(map[i + 1][j]))
        return (true);
    if (j > 0 && is_walkable(map[i][j - 1]))
        return (true);
    if (j < width - 1 && is_walkable(map[i][j + 1]))
        return (true);
    return (false);
}

int if_space_is_walled(char **map, size_t height, size_t width)
{
    size_t  i;
    size_t  j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            if (map[i][j] == ' ')
            {
                if (if_next_char_isnt_wall(map, i, j, height, width))
                    return ERROR;
            }
            j++;
        }
        i++;
    }
    return SUCCESS;
}

int player_is_duplicated(char *line, t_game *game)
{
    int i;

    i = 0;
    if (!line)
        return (ERROR);
    while (line[i])
    {
        if (line[i] == 'N' || line[i] == 'S'
            || line[i] == 'E' || line[i] == 'W')
            game->player_seen++;
        if (game->player_seen > 1)
            return(ERROR);
        i++;
    }
    return (SUCCESS);
}

int is_map_line(char *line)
{
    int i;

    i = 0;    
    if (!line || !(*line))
        return (ERROR);
    while (line[i])
    {
        if (line[i] != 'N' && line[i] != 'S' && line[i] != '1'
            && line[i] != 'E' && line[i] != 'W' && line[i] != '0'
            && line[i] != ' '  && line[i] != '\t'
            && line[i] != '\n')
            return (ERROR);
        i++;
    }
    return (SUCCESS);
}

void mark_border_spaces(char **map, int height, int width)
{
    int i;
    int x;

    i = 0;
    while (i < height)
    {
        x = 0;
        while (x < width && map[i][x] == ' ') {
            map[i][x] = 'v';
            x++;
        }
        x = width - 1;
        while (x >= 0 && map[i][x] == ' ')
        {
            map[i][x] = 'v';
            x--;
        }
        i++;
    }
}



int	is_valid_xpm_path(char *path)
{
	char	*dot;

	if (!path || !(*path))
		return (ERROR);
	dot = NULL;
	char *p = path;
	while (*p)
	{
		if (*p == '.')
			dot = p;
		p++;
	}
	if (!dot)
		return (ERROR);
	if (ft_strcmp(dot, ".xpm") == 0)
		return (SUCCESS);
	return (ERROR);
}

int	validate_texture_paths(t_config *config)
{
	if (!config->north || is_valid_xpm_path(config->north) != SUCCESS)
		return (invalid_north_path(config->north));
	if (!config->west || is_valid_xpm_path(config->west) != SUCCESS)
		return (invalid_west_path(config->west));
	if (!config->south || is_valid_xpm_path(config->south) != SUCCESS)
		return (invalid_south_path(config->south));
	if (!config->east || is_valid_xpm_path(config->east) != SUCCESS)
		return (invalid_east_path(config->east));
	return (SUCCESS);
}

int     map_is_walled(char **map, size_t height, size_t width)
{
    size_t  i;
    size_t  j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            if (map[i][j] == '0' &&
                (map[i+1][j] == 'v' || map[i-1][j] == 'v' ||
                 map[i][j+1] == 'v' || map[i][j-1] == 'v'))
                return (ERROR);
            j++;
        }
        i++;
    }
    return (SUCCESS);
}

int     validate_map_grid(t_game *game)
{
    int height;

    height = game->config.map.height;
    if (all_lines_are_walled(game->config.map.height, game->config.map.map_grid) != SUCCESS)
        return (ERROR);
    if (game->player_seen == 0)
        return (player_not_found());
    if (validate_texture_paths(&game->config) != SUCCESS)
        return (ERROR);
    pad_map(game);
    mark_border_spaces(game->config.map.flood_fill_copy, game->config.map.height, game->config.map.width);
    if (map_is_walled(game->config.map.flood_fill_copy, height, game->config.map.width) != SUCCESS)
        return (map_is_not_fully_walled());
    if (if_space_is_walled(game->config.map.flood_fill_copy, height, game->config.map.width) != SUCCESS)
        return (space_isnt_walled());
    return (SUCCESS);
}