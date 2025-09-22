/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:39:19 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/09/22 15:11:18 by mel-ouaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

int	keyrelease(int keycode, t_data *data)
{
	if (keycode == 'w')
		data->w = 0;
	if (keycode == 'a')
		data->a = 0;
	if (keycode == 'd')
		data->d = 0;
	if (keycode == 's')
		data->s = 0;
	if (keycode == 65361)
		data->left = 0;
	if (keycode == 65363)
		data->right = 0;
	return (0);
}

int	keyhook(void *data)
{
	t_data *keys;
	double	new_xpos;
	double	new_ypos;
	int		radius;
	
	new_xpos = 0;
	new_ypos = 0;
	radius = 5;
	keys = (t_data *)data;
	if (keys->w == 1)
	{
		new_xpos += keys->x_dir * 0.5;
		new_ypos += keys->y_dir * 0.5;
	}
	if (keys->a == 1)
	{
		new_xpos -= keys->y_dir * 0.5;
		new_ypos += keys->x_dir * 0.5;
	}
	if (keys->d == 1)
	{
		new_xpos += keys->y_dir * 0.5;
		new_ypos -= keys->x_dir * 0.5;
	}
	if (keys->s == 1)
	{
		new_xpos -= keys->x_dir * 0.5;
		new_ypos -= keys->y_dir * 0.5;
	}
	if (keys->right == 1)
		rotation(data, 0.01);
	if (keys->left == 1)
		rotation(data, -0.01);
	if ((new_xpos + keys->x_pos) >= radius && (new_ypos + keys->y_pos) >= radius 
		&& (new_xpos + keys->x_pos) < (8 * 64 - radius) && (new_ypos + keys->y_pos) < (7 * 64 - radius))
	{
		keys->x_pos += new_xpos;
		keys->y_pos += new_ypos;
	}
	draw_tiles(keys, 64);
	draw_player(keys);
	// draw_direction(keys);
	cast_rays(keys);
	// printf("x: %d, y: %d", keys->map_y, keys->map_x);
	mlx_put_image_to_window(keys->mlx, keys->mlx_window, keys->img, 0, 0);
	return (0);
}

int	keypress(int keycode, t_data *data)
{
	if (keycode == 'w')
		data->w = 1;
	if (keycode == 'a')
		data->a = 1;
	if (keycode == 'd')
		data->d = 1;
	if (keycode == 's')
		data->s = 1;
	if (keycode == 65307)
	{
		free_all(data);
		exit (0);
	}
	if (keycode == 65361)
		data->left = 1;
	if (keycode == 65363)
		data->right = 1;
	return (0);
}

void	calculation(t_data *data)
{
	data->player_x = data->x_pos / 64.0;
	data->player_y = data->y_pos / 64.0;
	data->deltadir_x = fabs(1/data->ray_dir_x);
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
	printf("player_x=%.2f player_y=%.2f map_x=%d map_y=%d step_x=%d step_y=%d sideX=%.2f sideY=%.2f\n",
    data->player_x, data->player_y,
    data->map_x, data->map_y,
    data->step_x, data->step_y,
    data->sidestep_x, data->sidestep_y);

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
		if (data->map_x < 0 || data->map_x > 7
			|| data->map_y < 0 || data->map_y > 6)
			break;
		if (data->map[data->map_y][data->map_x] == '1')
			hit = 1;
	}
	if (side == 0)
		data->wall_dist = (data->map_x - data->player_x + (1 - data->step_x) / 2.0) / data->ray_dir_x;
	else
		data->wall_dist = (data->map_y - data->player_y + (1 - data->step_y) / 2.0) / data->ray_dir_y;
}