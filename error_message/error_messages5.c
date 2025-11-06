#include "../cub3d.h"

int space_isnt_walled(void)
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd("Invalid map: space not properly enclosed by walls.", 2);
    ft_putendl_fd("Hint: all spaces inside the map must be surrounded by walls (no void leaks).", 2);
    return (ERROR);
}

int malloc_failed(void)
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd("Malloc failed !!", 2);
    return (ERROR);
}