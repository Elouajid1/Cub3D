#include "../cub3d.h"

int check_for_duplicate_id(t_game *game)
{
    int i;

    i = 0;
    while (i < 6)
    {
        if (game->config.seen_id[i] > 1)
            return (ERROR);
        i++;
    }
    return (SUCCESS);
}
