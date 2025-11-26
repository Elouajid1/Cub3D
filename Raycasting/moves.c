/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:39:19 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/11/26 16:35:14 by mel-ouaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	movements(t_data *data, double *new_xpos, double *new_ypos)
{
	if (data->w == 1)
	{
		*new_xpos += data->x_dir * speed;
		*new_ypos += data->y_dir * speed;
	}
	if (data->a == 1)
	{
		*new_xpos += data->y_dir * speed;
		*new_ypos -= data->x_dir * speed;
	}
	if (data->d == 1)
	{
		*new_xpos -= data->y_dir * speed;
		*new_ypos += data->x_dir * speed;
	}
	if (data->s == 1)
	{
		*new_xpos -= data->x_dir * speed;
		*new_ypos -= data->y_dir * speed;
	}
	if (data->right == 1)
		rotation(data, rot);
	if (data->left == 1)
		rotation(data, -rot);
}

int	check_tile(t_data *data, int tile_x, int tile_y)
{
	if (tile_x < 0 || tile_x >= data->map_width / 64 || tile_y < 0
		|| tile_y >= data->map_height / 64)
		return (0);
	if (data->map[tile_y][tile_x] == '1')
		return (0);
	return (1);
}

int	is_valid(t_data *data, double x, double y)
{
	int	buffer;
	int	tile_x;
	int	tile_y;

	buffer = 10;
	tile_x = (int)((x + buffer) / 64);
	tile_y = (int)((y + buffer) / 64);
	if (!check_tile(data, tile_x, tile_y))
		return (0);
	tile_x = (int)((x + buffer) / 64);
	tile_y = (int)((y - buffer) / 64);
	if (!check_tile(data, tile_x, tile_y))
		return (0);
	tile_x = (int)((x - buffer) / 64);
	tile_y = (int)((y + buffer) / 64);
	if (!check_tile(data, tile_x, tile_y))
		return (0);
	tile_x = (int)((x - buffer) / 64);
	tile_y = (int)((y - buffer) / 64);
	if (!check_tile(data, tile_x, tile_y))
		return (0);
	return (1);
}

int	keyhook(void *data)
{
	t_game	*keys;
	double	new_xpos;
	double	new_ypos;

	new_xpos = 0;
	new_ypos = 0;
	keys = (t_game *)data;
	movements(keys->data, &new_xpos, &new_ypos);
	if (is_valid(keys->data, keys->data->x_pos + new_xpos, keys->data->y_pos))
		keys->data->x_pos += new_xpos;
	if (is_valid(keys->data, keys->data->x_pos, keys->data->y_pos + new_ypos))
		keys->data->y_pos += new_ypos;
	coloring(keys->data, &keys->config);
	cast_rays(keys->data);
	mlx_put_image_to_window(keys->data->mlx, keys->data->mlx_window,
		keys->data->img, 0, 0);
	return (0);
}

int	keypress(int keycode, t_game *game)
{
	if (keycode == 'w')
		game->data->w = 1;
	if (keycode == 'a')
		game->data->a = 1;
	if (keycode == 'd')
		game->data->d = 1;
	if (keycode == 's')
		game->data->s = 1;
	if (keycode == 65307)
	{
		cleanup_mlx(game);
		exit(1);
	}
	if (keycode == 65361)
		game->data->left = 1;
	if (keycode == 65363)
		game->data->right = 1;
	return (0);
}

int	keyrelease(int keycode, t_game *game)
{
	if (keycode == 'w')
		game->data->w = 0;
	if (keycode == 'a')
		game->data->a = 0;
	if (keycode == 'd')
		game->data->d = 0;
	if (keycode == 's')
		game->data->s = 0;
	if (keycode == 65361)
		game->data->left = 0;
	if (keycode == 65363)
		game->data->right = 0;
	return (0);
}
