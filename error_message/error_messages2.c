/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:09:49 by moel-aid          #+#    #+#             */
/*   Updated: 2025/11/17 17:09:52 by moel-aid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cub3d.h"

int	player_not_found(void)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd("Player was not found !", 2);
	return (ERROR);
}

int	invalid_north_path(char *north_path)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(north_path, 2);
	ft_putendl_fd(" : is invalid xpm file path!", 2);
	return (ERROR);
}

int	invalid_south_path(char *south_path)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(south_path, 2);
	ft_putendl_fd(" : is invalid xpm file path!", 2);
	return (ERROR);
}

int	invalid_west_path(char *west_path)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(west_path, 2);
	ft_putendl_fd(" : is invalid xpm file path!", 2);
	return (ERROR);
}

int	invalid_east_path(char *east_path)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(east_path, 2);
	ft_putendl_fd(" : is invalid xpm file path!", 2);
	return (ERROR);
}


// int	invalid_north_path(char *north_path)
// {
// 	size_t i;

// 	i = 0;
// 	ft_putendl_fd("Error", 2);
// 	while (north_path[i] == ' ' || north_path[i] == '\t')
// 		i++;
// 	if (i == ft_strlen(north_path))
// 	{
// 		ft_putendl_fd("North direction path wasn't provided !", 2);
// 		return (ERROR);
// 	}
// 	ft_putstr_fd(north_path, 2);
// 	ft_putendl_fd(" : is invalid xpm file path!", 2);
// 	return (ERROR);
// }

// int	invalid_south_path(char *south_path)
// {
// 	size_t	i;

// 	i = 0;	
// 	ft_putendl_fd("Error", 2);
// 	while (south_path[i] == ' ' || south_path[i] == '\t')
//     	i++;
// 	if (i == ft_strlen(south_path))
// 	{
// 		ft_putendl_fd("South direction path wasn't provided !", 2);
// 		return (ERROR);
// 	}

// 	ft_putstr_fd(south_path, 2);
// 	ft_putendl_fd(" : is invalid xpm file path!", 2);
// 	return (ERROR);
// }

// int	invalid_west_path(char *west_path)
// {
// 	size_t	i;

// 	i = 0;
// 	ft_putendl_fd("Error", 2);
// 	while (west_path[i] == ' ' || west_path[i] == '\t')
//     	i++;
// 	if (i == ft_strlen(west_path))
// 	{
// 		ft_putendl_fd("West direction path wasn't provided !", 2);
// 		return (ERROR);
// 	}
// 	ft_putstr_fd(west_path, 2);
// 	ft_putendl_fd(" : is invalid xpm file path!", 2);
// 	return (ERROR);
// }

// int	invalid_east_path(char *east_path)
// {
// 	size_t	i;

// 	i = 0;
// 	ft_putendl_fd("Error", 2);
// 	while (east_path[i] == ' ' || east_path[i] == '\t')
//     	i++;
// 	if (i == ft_strlen(east_path))
// 	{
// 		ft_putendl_fd("East direction path wasn't provided !", 2);
// 		return (ERROR);
// 	}
// 	ft_putstr_fd(east_path, 2);
// 	ft_putendl_fd(" : is invalid xpm file path!", 2);
// 	return (ERROR);
// }
