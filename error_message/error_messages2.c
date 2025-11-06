#include "../cub3d.h"

int     player_not_found()
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd("Player was not found !", 2);
    return (ERROR);
}

int     invalid_north_path(char *north_path)
{
    ft_putendl_fd("Error", 2);
    ft_putstr_fd(north_path, 2);
    ft_putendl_fd(" : is invalid xpm file path!", 2);
    return (ERROR);
}

int invalid_south_path(char *south_path)
{
    ft_putendl_fd("Error", 2);
    ft_putstr_fd(south_path, 2);
    ft_putendl_fd(" : is invalid xpm file path!", 2);
    return (ERROR);
}

int invalid_west_path(char *west_path)
{
    ft_putendl_fd("Error", 2);
    ft_putstr_fd(west_path, 2);
    ft_putendl_fd(" : is invalid xpm file path!", 2);
    return (ERROR);
}

int invalid_east_path(char *east_path)
{
    ft_putendl_fd("Error", 2);
    ft_putstr_fd(east_path, 2);
    ft_putendl_fd(" : is invalid xpm file path!", 2);
    return (ERROR);
}