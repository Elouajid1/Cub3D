#include "../cub3d.h"

int    invalid_extension(char *filename)
{
    ft_putstr_fd("Error\n", 2);
    ft_putstr_fd(filename, 2);
    ft_putendl_fd(" wrong file type!", 2);
    return (ERROR);
}
int     file_not_found(char *filename)
{
    ft_putstr_fd("Error\n", 2);
    if (filename)
        ft_putstr_fd(filename, 2);
    ft_putendl_fd(" file not found!", 2);
    return (ERROR);
}

int     textures_not_found()
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd("No textures found !", 2);
    return (ERROR);
}

int missing_direction(void)
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd("a missing direction !", 2);
    return (ERROR);
}

int     floor_is_missing()
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd("Floor rgb line is missing", 2);
    return (ERROR);
}
