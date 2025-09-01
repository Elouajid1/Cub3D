/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <mel-ouaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:13:25 by mel-ouaj          #+#    #+#             */
/*   Updated: 2025/08/30 18:49:13 by mel-ouaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H

#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <math.h>
#include <mlx.h>

typedef struct	s_data
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		right;
	int		left;
	char	**map;
	void	*mlx;
	void	*mlx_window;
	double		x_pos;
	double		y_pos;
	double		x_dir;
	double		y_dir;
	void	*img;
	char	*addr;
	int		line_length;
	int		bpp;
	int		endian;
}	t_data;

void	draw_tiles(t_data *data, int size);
void	draw_map(t_data *data);
void	read_map(char **map, char *str);
void	my_pixel_put(t_data *img, int x, int y, int	color);
void	player_pos(t_data *data);
void	draw_player(t_data *data);
void	free_all(t_data *data);
void 	draw_line(t_data *data, int x_end, int y_end, int color);
void	player_dir(t_data *data);
void	draw_direction(t_data *data);
void	rotate_left(t_data *data, double angle);
void	rotate_right(t_data *data, double angle);
void	rotation(t_data *data, double angle);

#endif