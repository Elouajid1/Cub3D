#include "../cub3d.h"

int is_valid_rgb_line(char *rgb_line)
{
    int i;

    i = 0;
    printf("%s", rgb_line);
    while (rgb_line[i])
    {
        if (!ft_isalnum(rgb_line[i]) || rgb_line[i] != ',' || rgb_line[i] != ' '
            || rgb_line[i] != '\t')
        {
            ft_putendl_fd("Error", 2);
            ft_putendl_fd("Invalid RGB line !", 2);
            return (ERROR);
        }
        i++;
    }
    return (SUCCESS);
}

int     has_only_digits(char *red, char *blue, char *green)
{
    int i;

    i = 0;
    while (red[i])
    {
        if (!ft_isdigit(red[i]))
            return (ERROR);
        i++;
    }
    i = 0;
    while (green[i])
    {
        if (!ft_isdigit(green[i]))
            return (ERROR);
        i++;
    }
    i = 0;
    while (blue[i])
    {
        if (!ft_isdigit(blue[i]))
            return (ERROR);
        i++;
    }
    return (SUCCESS);
}

int     check_rgb_values(int red, int green, int blue)
{
    if ((red < 0 || red > 255) || (blue < 0 || blue > 255) || (green < 0 || green > 255))
        return (ERROR);
    return (SUCCESS);
}

int parse_rgb(t_rgb *rgb, char *rgb_line)
{
    char    **rgb_colors;
    char    *red = NULL;
    char    *green = NULL;
    char    *blue = NULL;

    if (!rgb || !rgb_line)
        return (ERROR);
    rgb_colors = ft_split(rgb_line, ',');
    if (!rgb_colors || !rgb_colors[0] || !rgb_colors[1] || !rgb_colors[2])
    {
        if (rgb_colors)
            free_array(rgb_colors);
        return (ERROR);
    }
    red = ft_strtrim(rgb_colors[0], " \t");
    green = ft_strtrim(rgb_colors[1], " \t");
    blue = ft_strtrim(rgb_colors[2], " \t");
    if (!red || !blue || !green || has_only_digits(red, blue, green) != SUCCESS)
        return (free_if_malloc_failed(red, blue, green, rgb_colors));
    rgb->r = ft_atoi(red);
    rgb->g = ft_atoi(green);
    rgb->b = ft_atoi(blue);
    free(blue);
    free(red);
    free(green);
    free_array(rgb_colors);
    return (check_rgb_values(rgb->r, rgb->g, rgb->b));
}


int get_ceiling_rgb(t_game *game, char *line)
{
    if (game->config.seen_id[5] > 0)
        return (ERROR);
    char *rgb_start = line + 1;
    while (*rgb_start == ' ' || *rgb_start == '\t')
        rgb_start++;
    if (parse_rgb(&game->config.ceiling, rgb_start) != SUCCESS)
    {
        ft_putendl_fd("Error", 2);
        ft_putendl_fd("invalid ceiling rgb line format!", 2);
        return (ERROR);
    }
    game->config.seen_id[5]++;
    game->config.ceiling_flag++;
    return (SUCCESS);
}

int get_floor_rgb(t_game *game, char *line)
{
    if (game->config.seen_id[4] > 0)
    {   
        ft_putendl_fd("Error", 2);
        ft_putendl_fd("Duplicated floor rgb line !", 2);
        return (ERROR);
    }
    char *rgb_start = line + 1;
    while (*rgb_start == ' ' || *rgb_start == '\t')
        rgb_start++;
    if (parse_rgb(&game->config.floor, rgb_start) != SUCCESS)
    {
        ft_putendl_fd("Error", 2);
        ft_putendl_fd("invalid floor rgb line format!", 2);
        return (ERROR);
    }
    game->config.seen_id[4]++;
    game->config.floor_flag++;
    return (SUCCESS);
}