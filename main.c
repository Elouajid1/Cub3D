/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:15:54 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/09/22 15:16:16 by mel-ouaj         ###   ########.fr       */
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

void	cast_rays(t_data *data)
{
	int	width = 8 * 64;
	int	x = 0;
	
	while (x < width)
	{
		data->camera_x = 2 * x / (double)width - 1;
		data->ray_dir_x = data->x_dir + data->x_plane * data->camera_x;
		data->ray_dir_y = data->y_dir + data->y_plane * data->camera_x;
		calculation(data);
		dda(data);
		int	x_ray = data->x_pos + data->ray_dir_x * data->wall_dist * 64;
		int	y_ray = data->y_pos + data->ray_dir_y * data->wall_dist * 64;
		draw_line(data, x_ray, y_ray, 0x008000);
		x+=20;
	}
}

int main()
{
	char	**map;
	char	*str;
	int		i;
	t_data	*data;

	i = 0;
	data = malloc(sizeof(t_data));
	map = malloc(sizeof(char *) * 9);
	str = NULL;
	read_map(map, str);
	data->map = map;
	draw_map(data);
	mlx_hook(data->mlx_window, 2, 1L<<0, keypress, data);
	mlx_hook(data->mlx_window, 3, 1L<<1, keyrelease, data);
	mlx_loop_hook(data->mlx, keyhook, data);
	mlx_loop(data->mlx);
}