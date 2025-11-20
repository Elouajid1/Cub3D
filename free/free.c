/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:08:41 by moel-aid          #+#    #+#             */
/*   Updated: 2025/11/19 09:37:50 by mel-ouaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	malloc_failed(t_rgb *rgb)
{
	if (rgb->red)
		free(rgb->red);
	if (rgb->blue)
		free(rgb->blue);
	if (rgb->green)
		free(rgb->green);
	if (rgb->rgb_colors)
		free_array(rgb->rgb_colors);
	return (ERROR);
}

int	safe_free(char *line)
{
	if (line)
		free(line);
	return (ERROR);
}

void	free_array(char **double_array)
{
	int	i;

	if (!double_array)
		return ;
	i = 0;
	while (double_array[i])
	{
		free(double_array[i]);
		double_array[i] = NULL;
		i++;
	}
	free(double_array);
}

void	free_rgb_array(char **rgb_array)
{
	int	i;

	if (!rgb_array)
		return ;
	i = 0;
	while (rgb_array[i])
	{
		free(rgb_array[i]);
		rgb_array[i] = NULL;
		i++;
	}
	free(rgb_array);
}



int	free_all_data(t_game *game)
{
	if (!game)
		return (ERROR);
	if (game->config.map.map_grid)
	{
		free_array(game->config.map.map_grid);
		game->config.map.map_grid = NULL;
	}
	if (game->config.map.flood_fill_copy)
	{
		free_array(game->config.map.flood_fill_copy);
		game->config.map.flood_fill_copy = NULL;
	}
	// free_mlx(game->data);
	free(game->config.north);
	free(game->config.south);
	free(game->config.west);
	free(game->config.east);
	free(game->data);
	game->config.north = NULL;
	game->config.south = NULL;
	game->config.west = NULL;
	game->config.east = NULL;
	return (SUCCESS);
}
