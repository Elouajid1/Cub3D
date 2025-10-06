/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:16:16 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/10/06 16:28:30 by mel-ouaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	player_pos(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'E' || data->map[i][j] == 'W'
				|| data->map[i][j] == 'N'|| data->map[i][j] == 'S')
			{
				data->y_pos = i * 64 + 32;
				data->x_pos = j * 64 + 32;
			}
			j++;
		}
		i++;
	}
}

void	free_all(t_data *data)
{
	free_maps(data);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mlx_window)
	{
		mlx_destroy_window(data->mlx, data->mlx_window);
		data->mlx_window = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
	free(data);
}

void	free_maps(t_data *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
	}
	free(data->map);
}

void	map_dimensions(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
		i++;
	data->map_height = i * 64;
	while (data->map[0][j])
		j++;
	data->map_width = j * 64;
}

void	player_dir(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'E')
			{
				data->x_dir = 1;
				data->y_dir = 0;
				data->x_plane = -(data->y_dir) * 0.66;
				data->y_plane = data->x_dir * 0.66;
			}
			if (data->map[i][j] == 'W')
			{
				data->x_dir = -1;
				data->y_dir = 0;
				data->x_plane = -(data->y_dir) * 0.66;
				data->y_plane = data->x_dir * 0.66;
			}
			if (data->map[i][j] == 'N')
			{
				data->x_dir = 0;
				data->y_dir = -1;
				data->x_plane = -(data->y_dir) * 0.66;
				data->y_plane = data->x_dir * 0.66;
			}
			if (data->map[i][j] == 'S')
			{
				data->x_dir = 0;
				data->y_dir = 1;
				data->x_plane = -(data->y_dir) * 0.66;
				data->y_plane = data->x_dir * 0.66;
			}
			j++;
		}
		i++;
	}
}

void	rotation(t_data *data, double angle)
{
	double	old_x_dir;
	double	old_x_plane;

	old_x_dir = data->x_dir;
	data->x_dir = data->x_dir * cos(angle) - data->y_dir * sin(angle);
	data->y_dir = old_x_dir * sin(angle) + data->y_dir * cos(angle);
	old_x_plane = data->x_plane;
	data->x_plane = data->x_plane * cos(angle) - data->y_plane * sin(angle);
	data->y_plane = old_x_plane * sin(angle) + data->y_plane * cos(angle);
}
