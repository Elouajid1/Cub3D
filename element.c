/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:16:16 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/08/31 15:19:41 by mel-ouaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_pixel_put(t_data *img, int x, int y, int	color)
{
	char	*dest;

	dest = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dest = color;
}

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
	if (data->mlx_window)
	{
		mlx_destroy_window(data->mlx, data->mlx_window);
		data->mlx_window = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		data->mlx = NULL;
	}
	free(data);
}

void	draw_player(t_data *data)
{
	double		cx = data->x_pos;
	double		cy = data->y_pos;
	double		x;
	double		y;
	int		radius = 7;

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
			}
			if (data->map[i][j] == 'W')
			{
				data->x_dir = -1;
				data->y_dir = 0;
			}
			if (data->map[i][j] == 'N')
			{
				data->x_dir = 0;
				data->y_dir = -1;
			}
			if (data->map[i][j] == 'S')
			{
				data->x_dir = 0;
				data->y_dir = 1;
			}
			j++;
		}
		i++;
	}
}

void	rotation(t_data *data, double angle)
{
	double	old_x_dir;

	old_x_dir = data->x_dir;
	data->x_dir = data->x_dir * cos(angle) - data->y_dir * sin(angle);
	data->y_dir = old_x_dir * sin(angle) + data->y_dir * cos(angle);
}