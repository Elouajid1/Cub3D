/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_directions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:38:44 by moel-aid          #+#    #+#             */
/*   Updated: 2025/11/17 15:38:48 by moel-aid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cub3d.h"

int	get_north_path(char *line, int index, t_game *game)
{
	char	*path;
	char	*trimmed_path;
	size_t	i;

	i = 0;
	if (game->config.seen_id[0] == 1)
		return (id_is_duplicate(0));
	path = skip_identifier_and_spaces(line, index, 2);
	trimmed_path = ft_strtrim(path, " \t\n\r");
	if (!trimmed_path)
		return (ERROR);
	game->config.north = ft_strdup(trimmed_path);
	free(trimmed_path);
	if (!game->config.north)
		return (ERROR);
	game->config.seen_id[0]++;
	return (SUCCESS);
}

int	get_south_path(char *line, int index, t_game *game)
{
	char	*path;
	char	*trimmed_path;

	if (game->config.seen_id[1] == 1)
		return (id_is_duplicate(1));
	path = skip_identifier_and_spaces(line, index, 2);
	trimmed_path = ft_strtrim(path, " \t\n\r");
	if (!trimmed_path)
		return (ERROR);
	game->config.south = ft_strdup(trimmed_path);
	free(trimmed_path);
	if (!game->config.south)
		return (ERROR);
	game->config.seen_id[1]++;
	return (SUCCESS);
}

int	get_west_path(char *line, int index, t_game *game)
{
	char	*path;
	char	*trimmed_path;

	if (game->config.seen_id[2] == 1)
		return (id_is_duplicate(2));
	path = skip_identifier_and_spaces(line, index, 2);
	trimmed_path = ft_strtrim(path, " \t\n\r");
	if (!trimmed_path)
		return (ERROR);
	game->config.west = ft_strdup(trimmed_path);
	free(trimmed_path);
	if (!game->config.west)
		return (ERROR);
	game->config.seen_id[2]++;
	return (SUCCESS);
}

int	get_east_path(char *line, int index, t_game *game)
{
	char	*path;
	char	*trimmed_path;

	if (game->config.seen_id[3] == 1)
		return (id_is_duplicate(3));
	path = skip_identifier_and_spaces(line, index, 2);
	trimmed_path = ft_strtrim(path, " \t\n\r");
	if (!trimmed_path)
		return (ERROR);
	game->config.east = ft_strdup(trimmed_path);
	free(trimmed_path);
	if (!game->config.east)
		return (ERROR);
	game->config.seen_id[3]++;
	return (SUCCESS);
}
