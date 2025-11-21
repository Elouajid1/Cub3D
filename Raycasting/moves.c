/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:39:19 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/11/21 15:35:15 by mel-ouaj         ###   ########.fr       */
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

int	keyhook(void *data)
{
	t_data	*keys;
	double	new_xpos;
	double	new_ypos;
	int		next_x;
	int		next_y;

	new_xpos = 0;
	new_ypos = 0;
	keys = (t_data *)data;
	movements(keys, &new_xpos, &new_ypos);
	next_x = (int)(keys->x_pos + new_xpos) / 64;
	next_y = (int)(keys->y_pos + new_ypos) / 64;
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
