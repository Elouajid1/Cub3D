/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:15:54 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/08/31 15:20:14 by mel-ouaj         ###   ########.fr       */
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
	mlx_put_image_to_window(data->mlx, data->mlx_window, data->img, 0, 0);
}

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
	
	keys = (t_data *)data;
	if (keys->w == 1)
	{
		keys->x_pos += keys->x_dir * 0.5;
		keys->y_pos += keys->y_dir * 0.5;
	}
	if (keys->a == 1)
	{
		keys->x_pos -= keys->y_dir * 0.5;
		keys->y_pos += keys->x_dir * 0.5;
	}
	if (keys->d == 1)
	{
		keys->x_pos += keys->y_dir * 0.5;
		keys->y_pos -= keys->x_dir * 0.5;
	}
	if (keys->s == 1)
	{
		keys->x_pos -= keys->x_dir * 0.5;
		keys->y_pos -= keys->y_dir * 0.5;
	}
	if (keys->right == 1)
		rotation(data, -0.02);
	if (keys->left == 1)
		rotation(data, 0.02);
	draw_tiles(keys, 64);
	draw_player(keys);
	draw_direction(data);
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