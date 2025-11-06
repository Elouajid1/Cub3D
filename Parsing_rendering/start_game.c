#include "../cub3d.h"

int if_all_textures_exist(t_game *game)
{
    int i;

    i = 0;
    while (i < 6)
    {
        if (game->config.seen_id[i] != 1)
            return (ERROR);
        i++;
    }
    return (SUCCESS);
}

int start_game(t_game *game)
{
    // if (if_all_textures_exist(game) != SUCCESS)
    //     return (texture_missing());
    game->config.ceiling_flag = 0;
    return (SUCCESS);
}