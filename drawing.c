/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:38:01 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/10/06 16:26:18 by mel-ouaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_map(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_window = mlx_new_window(data->mlx, screen_width, screen_height, "test");
	data->img = mlx_new_image(data->mlx, screen_width, screen_height);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->endian);
	// draw_tiles(data, 64);
	player_pos(data);
	player_dir(data);
	// draw_player(data);
	// draw_direction(data);
	coloring(data);
	cast_rays(data);
	mlx_put_image_to_window(data->mlx, data->mlx_window, data->img, 0, 0);
}
void	draw_vertical(t_data *data, int	x, int start, int end, int color)
{
	while (start < end)
	{
		my_pixel_put(data, x, start, color);
		start++;
	}
}

void	draw_walls(t_data *data, int x)
{
	int	lineheight;
	int	start;
	int	end;

	lineheight = (int)(screen_height / data->wall_dist);
	start = -lineheight / 2 + screen_height / 2;
	if (start < 0)
		start = 0;
	end = lineheight / 2 + screen_height / 2;
	if (end >= screen_height)
		end = screen_height - 1;
	draw_vertical(data, x, start, end, 0xFFFF00);
}

void	coloring(t_data *data)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < screen_height)
	{
		x = 0;
		while (x < screen_width)
		{
			if (y < screen_height / 2)
				color = 0x87CEEB;
			else
				color = 0x808080;
			my_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	my_pixel_put(t_data *img, int x, int y, int	color)
{
	char	*dest;

	if (x >= 0 && y >= 0 && x < screen_width && y < screen_height)
	{
		dest = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dest = color;
	}
}

// void	draw_player(t_data *data)
// {
// 	double		cx = data->x_pos;
// 	double		cy = data->y_pos;
// 	double		x;
// 	double		y;
// 	int		radius = 5;

// 	y = cy - radius;
// 	while (y < cy + radius)
// 	{
// 		x = cx - radius;
// 		while (x < cx + radius)
// 		{
// 			int dx = x - cx;
// 			int dy = y - cy;
// 			if (dx*dx + dy*dy <= radius*radius)
// 				my_pixel_put(data, (int)x, (int)y, 0x00FF00);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void draw_direction(t_data *data)
// {
// 	double	x_end;
// 	double	y_end;

// 	x_end = data->x_pos + data->x_dir * 50;
// 	y_end = data->y_pos + data->y_dir * 50;
// 	draw_line(data, (int)x_end, (int)y_end, 0x00ff0000);
// }

// void	draw_line(t_data *data, int x_end, int y_end, int color)
// {
// 	int	i;
// 	double	x;
// 	double	y;
// 	double	dx;
// 	double	dy;
// 	double	steps;

// 	i = 0;
// 	x = data->x_pos;
// 	y = data->y_pos;
// 	dx = x_end - x;
// 	dy = y_end - y;
// 	if (fabs(dx) > fabs(dy))
// 		steps = fabs(dx);
// 	else
// 		steps = fabs(dy);
// 	while (i <= steps)
// 	{
// 		my_pixel_put(data, (int)x, (int)y, color);
// 		x += dx / steps;
// 		y += dy / steps; 
// 		i++;
// 	}
// }

// void	draw_tiles(t_data *data, int size)
// {
// 	int	i;
// 	int	j;
// 	int	x;
// 	int	y;
// 	int	color;
// 	int	og_color;
	
// 	i = 0;
// 	j = 0;
// 	x = 0;
// 	y = 0;
// 	while (data->map[i])
// 	{
// 		j = 0;
// 		while (data->map[i][j])
// 		{
// 			if (data->map[i][j] == '1')
// 				og_color = 0x808080;
// 			else
// 				og_color = 0xFFFFFFFF;
// 			y = 0;
// 			while (y < size)
// 			{
// 				x = 0;
// 				while (x < size)
// 				{
// 					if ((x == 0 || x == size - 1) || (y == 0 || y == size - 1))
// 						color = 0x000000;
// 					else
// 						color = og_color;
// 					int	start_x = j * size + x;
// 					int	start_y = i * size + y;
// 					my_pixel_put(data, start_x, start_y, color);
// 					x++;
// 				}
// 				y++;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }
