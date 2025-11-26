/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:38:01 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/11/24 15:46:16 by mel-ouaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_map(t_game *game)
{
	t_data	*data;

	data = game->data;
	data->mlx = mlx_init();
	load_all_textures(game);
	data->mlx_window = mlx_new_window(data->mlx, screen_width, screen_height,
			"test");
	data->img = mlx_new_image(data->mlx, screen_width, screen_height);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_length,
			&data->endian);
	player_pos(data);
	player_dir(data);
	mlx_put_image_to_window(data->mlx, data->mlx_window, data->img, 0, 0);
}

int	get_tex_color(t_tex *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= tex->width || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

int	load_texture(t_data *data, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(data->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		fprintf(stderr, "Error: failed to load texture: %s\n", path);
		return (ERROR);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
	{
		fprintf(stderr, "Error: failed to get texture data: %s\n", path);
		return (ERROR);
	}
	return (SUCCESS);
}

void	draw_vertical(t_data *data, int x, int start, int end)
{
	int	color;

	while (start < end)
	{
		data->texY = (int)data->texPos;
		data->texPos = data->texPos + data->texStep;
		color = get_tex_color(data->wall_tex, data->texX, data->texY);
		my_pixel_put(data, x, start, color);
		start++;
	}
}

void	set_tex(t_data *data)
{
	if (data->map[data->map_y][data->map_x] == '1')
		data->texNum = 0;
	else
		return ;
	if (data->side == 0 && data->ray_dir_x > 0)
		data->wall_tex = &data->tex_ea;
	else if (data->side == 0 && data->ray_dir_x < 0)
		data->wall_tex = &data->tex_we;
	else if (data->side == 1 && data->ray_dir_y < 0)
		data->wall_tex = &data->tex_no;
	else
		data->wall_tex = &data->tex_so;
	if (data->side == 0)
		data->Wall_x = data->player_y + data->wall_dist * data->ray_dir_y;
	else
		data->Wall_x = data->player_x + data->wall_dist * data->ray_dir_x;
	data->fWallx = data->Wall_x - floor(data->Wall_x);
	data->texX = (int)(data->fWallx * data->wall_tex->width);
}

void	draw_walls(t_data *data, int x)
{
	int	lineheight;
	int	start;
	int	end;

	set_tex(data);
	if (data->side == 0 && data->ray_dir_x > 0)
		data->texX = data->wall_tex->width - data->texX - 1;
	else if (data->side == 1 && data->ray_dir_y < 0)
		data->texX = data->wall_tex->width - data->texX - 1;
	lineheight = (int)(screen_height / data->wall_dist);
	start = -lineheight / 2 + screen_height / 2;
	if (start < 0)
		start = 0;
	end = lineheight / 2 + screen_height / 2;
	if (end >= screen_height)
		end = screen_height - 1;
	data->texStep = data->wall_tex->height / (double)lineheight;
	data->texPos = (start - screen_height / 2 + lineheight / 2) * data->texStep;
	draw_vertical(data, x, start, end);
}

int	to_hex(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

void	coloring(t_data *data, t_config *config)
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
				color = to_hex(config->ceiling.r, config->ceiling.g,
						config->ceiling.b);
			else
				color = to_hex(config->floor.r, config->floor.g,
						config->floor.b);
			my_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	my_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dest;

	if (x >= 0 && y >= 0 && x < screen_width && y < screen_height)
	{
		dest = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dest = color;
	}
}
