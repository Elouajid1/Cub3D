/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:15:54 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/11/12 11:42:18 by mel-ouaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int    initilaize_data(t_game *game)
{
    int i;

    i = 0;
    game->player.index = 0;
    game->line_length = 0;
    game->config.map.map_grid = malloc((sizeof(char *) * MAX_HEIGHT));
    if (!game->config.map.map_grid)
        return (ERROR);
    while (i < MAX_HEIGHT)
    {
        game->config.map.map_grid[i] = NULL;
        i++;
    }
    return (SUCCESS);
}

int main(int ac, char **av)
{
	t_game *game;

    if (ac < 2)
    {
        ft_putendl_fd("Error: missing map file argument", 2);
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
	game->data = malloc(sizeof(t_data));
	game->data->map = game->config.map.map_grid;
	map_dimensions(game->data);
	draw_map(game);
	mlx_hook(game->data->mlx_window, 2, 1L<<0, keypress, game->data);
	mlx_hook(game->data->mlx_window, 3, 1L<<1, keyrelease, game->data);
	mlx_loop_hook(game->data->mlx, keyhook, game->data);
	mlx_loop(game->data->mlx);
    free_all_data(game);
    free(game);
    return (SUCCESS);
}
