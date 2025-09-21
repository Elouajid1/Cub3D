/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:38:01 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/09/21 18:33:53 by mel-ouaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_tiles(t_data *data, int size)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	color;
	int	og_color;
	
	i = 0;
	j = 0;
	x = 0;
	y = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				og_color = 0x808080;
			else
				og_color = 0xFFFFFFFF;
			y = 0;
			while (y < size)
			{
				x = 0;
				while (x < size)
				{
					if ((x == 0 || x == size - 1) || (y == 0 || y == size - 1))
						color = 0x000000;
					else
						color = og_color;
					int	start_x = j * size + x;
					int	start_y = i * size + y;
					my_pixel_put(data, start_x, start_y, color);
					x++;
				}
				y++;
			}
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_window = mlx_new_window(data->mlx, 8 * 64, 7 * 64, "test");
	data->img = mlx_new_image(data->mlx, 8 * 64, 7 * 64);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);
	draw_tiles(data, 64);
	player_pos(data);
	player_dir(data);
	draw_player(data);
	draw_direction(data);
	// cast_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_window, data->img, 0, 0);
}

void	draw_player(t_data *data)
{
	double		cx = data->x_pos;
	double		cy = data->y_pos;
	double		x;
	double		y;
	int		radius = 5;

	y = cy - radius;
	while (y < cy + radius)
	{
		x = cx - radius;
		while (x < cx + radius)
		{
			int dx = x - cx;
			int dy = y - cy;
			if (dx*dx + dy*dy <= radius*radius)
				my_pixel_put(data, (int)x, (int)y, 0x00FF00);
			x++;
		}
		y++;
	}
}

void draw_direction(t_data *data)
{
	double	x_end;
	double	y_end;

	x_end = data->x_pos + data->x_dir * 50;
	y_end = data->y_pos + data->y_dir * 50;
	draw_line(data, (int)x_end, (int)y_end, 0x00ff0000);
}

void	draw_line(t_data *data, int x_end, int y_end, int color)
{
	int	i;
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	steps;

	i = 0;
	x = data->x_pos;
	y = data->y_pos;
	dx = x_end - x;
	dy = y_end - y;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	while (i <= steps)
	{
		my_pixel_put(data, (int)x, (int)y, color);
		x += dx / steps;
		y += dy / steps; 
		i++;
	}
}