/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:49:02 by moel-aid          #+#    #+#             */
/*   Updated: 2025/11/18 16:49:06 by moel-aid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cub3d.h"

void	free_maps(t_data *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
	}
	free(data->map);
}

void	free_textures(t_data *data)
{
	if (data->tex_no.img)
		mlx_destroy_image(data->mlx, data->tex_no.img);
	if (data->tex_so.img)
		mlx_destroy_image(data->mlx, data->tex_so.img);
	if (data->tex_ea.img)
		mlx_destroy_image(data->mlx, data->tex_ea.img);
	if (data->tex_we.img)
		mlx_destroy_image(data->mlx, data->tex_we.img);
}

void	cleanup_mlx(t_data *data)
{
	free_textures(data);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->mlx_window)
		mlx_destroy_window(data->mlx, data->mlx_window);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);  // Linux only
		free(data->mlx);
	}
    free_maps(data);
}
