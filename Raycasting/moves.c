/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:39:19 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/10/06 16:35:48 by mel-ouaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

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
		new_xpos += keys->y_dir * 0.5;
		new_ypos -= keys->x_dir * 0.5;
	}
	if (keys->d == 1)
	{
		new_xpos -= keys->y_dir * 0.5;
		new_ypos += keys->x_dir * 0.5;
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
	int	next_x = (int)(keys->x_pos + new_xpos) / 64;
	int	next_y = (int)(keys->y_pos + new_ypos) / 64;
	if (keys->map[(int)(keys->y_pos / 64)][(int)next_x] != '1')
		keys->x_pos += new_xpos;
	if (keys->map[(int)next_y][(int)(keys->x_pos / 64)] != '1')
		keys->y_pos += new_ypos;
	// draw_tiles(keys, 64);
	// draw_player(keys);
	// draw_direction(keys);
	coloring(keys);
	cast_rays(keys);
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
		exit (1);
	}
	if (keycode == 65361)
		data->left = 1;
	if (keycode == 65363)
		data->right = 1;
	return (0);
}

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
