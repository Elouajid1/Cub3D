#include "../cub3d.h"


int     north_direction_missing()
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd("North direction is missing", 2);
    return (ERROR);
}

int     west_direction_missing()
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd("West direction is missing", 2);
    return (ERROR);
}

int     map_is_not_fully_walled()
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd("Map is not fully walled !", 2);
    return (ERROR);
}

int     east_direction_missing()
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd("East direction is missing", 2);
    return (ERROR);
}

int     south_direction_missing()
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd("South direction is missing", 2);
    return (ERROR);
}
