#include "./cub3d.h"

int    initilaize_data(t_game *game)
{
    int i;

    i = 0;
    game->player.index = 0;
    game->line_length = 0;
    game->config.map.map_grid = malloc((sizeof(char *) * MAX_HEIGHT));
    if (!game->config.map.map_grid)
        return (ERROR);
    if (!game->config.map.map_grid)
        return (ERROR);
    while (i < 256)
    {
        i++;
        game->config.map.map_grid[i] = NULL;
    }
    return (SUCCESS);
}

void	print_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->config.map.map_grid[i])
	{
        if (game->config.map.map_grid[i])
		    printf("%s\n", game->config.map.map_grid[i]);
		i++;
	}
}

int main(int ac, char **av)
{
    t_game *game;

    if (ac < 2)
    {
        ft_putendl_fd("Error: missing map file", 2);
        return (ERROR);
    }
    if (!av[1])
        return (file_not_found(av[1]));
        
    game = malloc(sizeof(t_game));
    if (!game)
        return (ERROR);
        
    ft_bzero(game, sizeof(t_game));
    if (initilaize_data(game) != SUCCESS)
    {
        free_all_data(game);
        free(game);
        return (ERROR);
    }
    if (parse_map(game, av[1]) != SUCCESS)
    {
        free_all_data(game);
        free(game);
        return (ERROR);
    }
    start_game(game);
    if (game->config.north)
        printf("North texture : %s\n", game->config.north);
    else
        printf("North texture : (null)\n");

    if (game->config.south)
        printf("South texture : %s\n", game->config.south);
    else
        printf("South texture : (null)\n");

    if (game->config.west)
        printf("West texture  : %s\n", game->config.west);
    else
        printf("West texture  : (null)\n");

    if (game->config.east)
        printf("East texture  : %s\n", game->config.east);
    else
        printf("East texture  : (null)\n");

    printf("Floor flag    : %d\n", game->config.floor_flag);
    printf("Ceiling flag  : %d\n", game->config.ceiling_flag);

    printf("Floor RGB     : R=%d, G=%d, B=%d\n",
        game->config.floor.r, game->config.floor.g, game->config.floor.b);
    printf("Ceiling RGB   : R=%d, G=%d, B=%d\n",
        game->config.ceiling.r, game->config.ceiling.g, game->config.ceiling.b);

    printf("Map width     : %zu\n", game->config.map.width);
    printf("Map height    : %zu\n", game->config.map.height);

    if (game->config.map.map_grid)
    {
        printf("Map grid:\n");
        for (size_t i = 0; i < game->config.map.height; i++)
        {
            if (game->config.map.map_grid[i])
                printf("%s\n", game->config.map.map_grid[i]);
            else
                printf("(null)\n");
        }
    }
    else
        printf("Map grid is NULL\n");

    printf("Seen IDs      : ");
    for (int i = 0; i < 6; i++)
        printf("%d ", game->config.seen_id[i]);
    printf("\n");

    free_all_data(game);
    free(game);
    return (ERROR);
}