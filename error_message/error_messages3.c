#include "../cub3d.h"

int id_is_duplicate(int which_dir)
{
    ft_putendl_fd("Error", 2);
    if (which_dir == 0)
        ft_putendl_fd("North direction line is duplicated", 2);
    if (which_dir == 1)
        ft_putendl_fd("South direction line is duplicated", 2);
    if (which_dir == 2)
        ft_putendl_fd("West direction line is duplicated", 2);
    if (which_dir == 3)
        ft_putendl_fd("East direction line is duplicated", 2);
    return (ERROR);
}

int map_is_not_last(void)
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd("map must be last !", 2);
    return (ERROR);
}

int invalid_map(char *line)
{
    free(line);
    ft_putendl_fd("Error", 2);
    ft_putendl_fd("Invalid map element!", 2);
    return (ERROR);
}

int     stranger_element()
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd("Stranger element inside the map !", 2);
    return (ERROR);
}

int     ceiling_is_missing()
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd("Ceiling rgb line is missing", 2);
    return (ERROR);
}