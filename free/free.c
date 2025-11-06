#include "../cub3d.h"

int free_if_malloc_failed(char *red, char *blue, char *green, char **rgb_colors)
{
    if (red)
        free(red);
    if (blue)  
        free(blue);
    if (green)
        free(green);
    if (rgb_colors)
        free_array(rgb_colors);
    return (ERROR);
}

void free_array(char **double_array)
{
    int i;

    if (!double_array)
        return;
        
    i = 0;
    while (double_array[i])
    {
        free(double_array[i]);
        double_array[i] = NULL;
        i++;
    }
    free(double_array);
}

int free_all_data(t_game *game)
{
    if (!game)
        return (ERROR);
    if (game->config.map.map_grid && game->config.map.flood_fill_copy)
    {
        free_array(game->config.map.map_grid);
        free_array(game->config.map.flood_fill_copy);
        game->config.map.flood_fill_copy = NULL;
        game->config.map.map_grid = NULL;
    }
    if (game->config.north)
    {
        free(game->config.north);
        game->config.north = NULL;
    }
    if (game->config.south)
    {
        free(game->config.south);
        game->config.south = NULL;
    }
    if (game->config.west)
    {
        free(game->config.west);
        game->config.west = NULL;
    }
    if (game->config.east)
    {
        free(game->config.east);
        game->config.east = NULL;
    }
    return (ERROR);
}