# include "../cub3d.h"

int	get_map_directions_rgb(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (get_north_path(line, i, game));
	if (line[i] == 'S' && line[i + 1] == 'O' && (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (get_south_path(line, i, game));
	if (line[i] == 'W' && line[i + 1] == 'E' && (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (get_west_path(line, i, game));
	if (line[i] == 'E' && line[i + 1] == 'A' && (line[i + 2] == ' ' || line[i + 2] == '\t'))
		return (get_east_path(line, i, game));
	if (line[i] == 'F' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (get_floor_rgb(game, line + i));
	if (line[i] == 'C' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (get_ceiling_rgb(game, line + i ));
	return (ERROR);
}

int fill_map_grid(t_game *game, char *line)
{
    game->config.map.map_grid[game->player.index] = ft_strdup(line);
    if (!game->config.map.map_grid[game->player.index])
        return (ERROR);
    if (ft_strlen(line) > game->line_length)
        game->line_length = ft_strlen(line);
    return (SUCCESS);
}

int check_for_ids_existence(t_game *game)
{
    if (!game->config.seen_id[0] || !game->config.seen_id[1]
        || !game->config.seen_id[2] || !game->config.seen_id[3]
        || !game->config.seen_id[4] || !game->config.seen_id[5])
        return (map_is_not_last());
    if (!game->config.north)
        return (north_direction_missing());
    if (!game->config.south)
        return (south_direction_missing());
    if (!game->config.west)
        return (west_direction_missing());
    if (!game->config.east)
        return (east_direction_missing());
    if (!game->config.floor_flag)
        return (floor_is_missing());
    if (!game->config.ceiling_flag)
        return (ceiling_is_missing());
    return (SUCCESS);
}

int process_line(t_game *game, char *line)
{
    if (ft_strlen(line) == 1)
        return (map_row_is_short());
    if (is_map_line(line) == SUCCESS)
    {
        if (player_is_duplicated(line, game) != SUCCESS)
            return (duplicated_player());
        game->map_exist_flag++;
        if (!game->config.north && !game->config.south
            && !game->config.east && !game->config.west
            && !game->config.ceiling_flag && !game->config.floor_flag)
                return (map_is_not_last());
        if (check_for_ids_existence(game) != SUCCESS)
            return (ERROR);
        if (textures_before_map(game) != SUCCESS)
            return (map_is_not_last());
        if (fill_map_grid(game, line) != SUCCESS)
            return (ERROR);
        game->player.index++;
        return (SUCCESS);
    }
    return (get_map_directions_rgb(game, line));
}

// int get_map_copy_demensions(t_game *game, int fd)
// {
//     char    *line;
//     size_t  line_count;

//     game->player.index = 0;
//     line_count = 0;
//     game->line_length = 0;
//     line = get_next_line(fd);
//     while (line)
//     {
//         printf("%s", line);
//         // if ((line && line[0] == '\n'))
//         // {
//         //     free(line);
//         //     line = get_next_line(fd);
//         //     continue;
//         // }
//         size_t len = ft_strlen(line);
//         if (len > 0 && line[len - 1] == '\n')
//             line[len - 1] = '\0';
//         if (len > 1 && line[len - 2] == '\r')
//             line[len - 2] = '\0';
//         // printf("%s", line);
//         if (process_line(game, line) != SUCCESS)
//         {
//             free(line);
//             return (ERROR);
//         }
//         if (is_map_line(line) == SUCCESS)
//             line_count++;
//         free(line);
//         line = get_next_line(fd);
//     }
//     game->config.map.map_grid[game->player.index] = NULL;
//     return (SUCCESS);
// }

int get_map_copy_demensions(t_game *game, int fd)
{
    char    *line;
    size_t  line_count;

    game->player.index = 0;
    line_count = 0;
    game->line_length = 0;

    line = get_next_line(fd);
    while (line)
    {
        size_t len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        if (len > 1 && line[len - 2] == '\r')
            line[len - 2] = '\0';
        if (line[0] == '\0')
        {
            free(line);
            line = get_next_line(fd);
            continue;
        }
        if (process_line(game, line) != SUCCESS)
        {
            free(line);
            return (ERROR);
        }
        if (is_map_line(line) == SUCCESS)
            line_count++;
        free(line);
        line = get_next_line(fd);
    }
    game->config.map.map_grid[game->player.index] = NULL;
    return (SUCCESS);
}

static int measure_map(size_t *height, size_t *max_width, char *filename)
{
    char    *line;
    size_t  len;
    int     fd;

    fd = open (filename, O_RDONLY);
    if (fd < 0)
        return (file_not_found(filename));
    line = get_next_line(fd);
    while (line)
    {
        if (is_map_line(line) == SUCCESS)
        {
            len = ft_strlen(line);
            if (len > *max_width)
                *max_width = len;
            (*height)++;
        }
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (SUCCESS);
}

int check_cub_extension(char *filename)
{
    int len;
    
    if (!filename)
        return (ERROR);
    len = strlen(filename);
    if (len < 4)
        return (ERROR);
    if (strcmp(filename + len - 4, ".cub") == 0)
        return (SUCCESS);
    return (ERROR);
}

int parse_map(t_game *game, char *filename)
{
    int     fd;

    if (check_cub_extension(filename) != SUCCESS)
        return (invalid_extension(filename));
    measure_map(&game->config.map.height, &game->config.map.width, filename);
    fd = open (filename, O_RDONLY);
    if (fd < 0)
        return (file_not_found(filename));
    if (get_map_copy_demensions(game, fd) != SUCCESS)
    {
        close(fd);
        return (ERROR);
    }
    close(fd);
    if (game->map_exist_flag == 0 || game->map_exist_flag < 3)
        return (map_is_short());
    if (game->config.map.height <= 2 && game->config.map.width <= 2)
        return (ERROR);
    if (validate_map_grid(game) != SUCCESS)
        return (ERROR);
    return (SUCCESS);
}




