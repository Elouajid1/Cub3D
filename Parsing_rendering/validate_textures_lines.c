#include "../cub3d.h"

int	is_valid_rgb_char(char c)
{
	return (c >= '0' && c <= '9')  // digits
		|| c == ','                // comma separator
		|| c == ' '                // space
		|| c == '\t';
}


int textures_before_map(t_game *game)
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
