/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:15:54 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/10/06 16:17:31 by mel-ouaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	read_map(char **map, char *str)
{
	int		fd;
	int		i;

	i = 0;
	fd = open("./map.cub", O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		map[i] = ft_strdup(str);
		free(str);
		str = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	close(fd);
}

int main()
{
	char	**map;
	char	*str;
	int		i;
	t_data	*data;

	i = 0;
	data = malloc(sizeof(t_data));
	map = malloc(sizeof(char *) * 12);
	str = NULL;
	bzero(data, sizeof(t_data));
	read_map(map, str);
	data->map = map;
	map_dimensions(data);
	draw_map(data);
	mlx_hook(data->mlx_window, 2, 1L<<0, keypress, data);
	mlx_hook(data->mlx_window, 3, 1L<<1, keyrelease, data);
	mlx_loop_hook(data->mlx, keyhook, data);
	mlx_loop(data->mlx);
}
