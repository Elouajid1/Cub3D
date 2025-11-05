/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:07:56 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/10/16 10:28:53 by mel-ouaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	calculation(t_data *data)
{
	data->player_x = data->x_pos / 64.0;
	data->player_y = data->y_pos / 64.0;
	if (data->ray_dir_x == 0)
		data->deltadir_x = 1e30;
	else
		data->deltadir_x = fabs(1/data->ray_dir_x);
	if (data->ray_dir_y == 0)
		data->deltadir_y = 1e30;
	else	
		data->deltadir_y = fabs(1/data->ray_dir_y);
	data->map_x = (int)data->player_x;
	data->map_y = (int)data->player_y;
	if (data->ray_dir_x < 0)
	{
		data->step_x = -1;
		data->sidestep_x = (data->player_x - data->map_x) * data->deltadir_x;
	}
	else
	{
		data->step_x = 1;
		data->sidestep_x = (data->map_x + 1 - data->player_x) * data->deltadir_x;
	}
	if (data->ray_dir_y < 0)
	{
		data->step_y = -1;
		data->sidestep_y = (data->player_y - data->map_y) * data->deltadir_y;
	}
	else
	{
		data->step_y = 1;
		data->sidestep_y = (data->map_y + 1 - data->player_y) * data->deltadir_y;
	}
}

void	dda(t_data *data)
{
	int	hit = 0;
	int	side = 0;

	while (hit == 0)
	{
		if (data->sidestep_x < data->sidestep_y)
		{
			data->sidestep_x += data->deltadir_x;
			data->map_x += data->step_x;
			side = 0;
		}
		else
		{
			data->sidestep_y += data->deltadir_y;
			data->map_y += data->step_y;
			side = 1;
		}
		if (data->map_x < 0 || data->map_x >= (data->map_width / 64)
			|| data->map_y < 0 || data->map_y >= (data->map_height / 64))
			break;
		if (data->map[data->map_y][data->map_x] == '1')
			hit = 1;
	}
	data->side = side;
	if (side == 0)
		data->wall_dist = data->sidestep_x - data->deltadir_x;
	else
		data->wall_dist = data->sidestep_y - data->deltadir_y;
}

void	cast_rays(t_data *data)
{
	int	x = 0;
	
	while (x < screen_width)
	{
		data->camera_x = 2 * x / (double)screen_width - 1;
		data->ray_dir_x = data->x_dir + data->x_plane * data->camera_x;
		data->ray_dir_y = data->y_dir + data->y_plane * data->camera_x;
		calculation(data);
		dda(data);
		draw_walls(data, x);
		x++;
	}
}
