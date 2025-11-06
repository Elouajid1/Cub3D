#include "../cub3d.h"

char    *skip_identifier_and_spaces(char *line, int index, int id_len)
{   
    if (line[index + 1] == 32 || line[index + 1] == '\t')
        id_len = 1;
    line = line + index + id_len;
    while (*line == ' ' || *line == '\t')
        line++;
    return (line);
}