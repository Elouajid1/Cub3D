#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <strings.h>
#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# define ERROR 1
# define SUCCESS 0
# define MAX_WIDTH 512
# define MAX_HEIGHT 512
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define speed 1
# define rot 0.05
# define screen_width 1000
# define screen_height 800


typedef struct s_tex
{
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
}   t_tex;

typedef struct	s_data
{
    t_tex   tex_no;
    t_tex   tex_so;
    t_tex   tex_ea;
    t_tex   tex_we;
    t_tex   *wall_tex;
	int		map_height;
	int		map_width;
	int		w;
	int		a;
	int		s;
	int		d;
	int		right;
	int		left;
	char	**map;
	void	*mlx;
	void	*mlx_window;
	double	x_pos;
	double	y_pos;
	double	x_dir;
	double	y_dir;
	double	x_plane;
	double	y_plane;
	double	ray_dir_x;
	double	ray_dir_y;
	double	deltadir_x;
	double	deltadir_y;
	double	sidestep_x;
	double	sidestep_y;
	double 	player_x;
	double	player_y;
	double	wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	camera_x;
	void	*img;
	char	*addr;
	int		line_length;
	int		bpp;
	int		endian;
	int		side;
    int     texNum;
    double  Wall_x;
    double  fWallx;
    double  texPos;
    double  texStep;
    int     texX;
    int     texY;
}	t_data;

typedef struct s_rgb
{
    int r;
    int g;
    int b;
}   t_rgb;

typedef struct s_map
{
    char    **map_grid;
    char    **flood_fill_copy;
    size_t     width;
    size_t     height;
}   t_map;

typedef struct s_config
{
    char    *north;
    char    *south;
    char    *west;
    char    *east;
    int     seen_id[6];
    int     floor_flag;
    int     ceiling_flag;
    t_rgb   floor;
    t_rgb   ceiling;
    t_map   map;
}   t_config;

typedef struct s_player
{
    int     index;
}   t_player;

typedef struct s_game
{
    t_config    config;
    t_player    player;
    t_data      *data;
    size_t      line_length;
    int         textures_data_count;
    int         player_seen;
    int         map_exist_flag;
}   t_game;
////////////////////////////////////////////////////////////////////////
//                             PARSING FUNCTIONS                      //
////////////////////////////////////////////////////////////////////////

int     parse_map(t_game *game, char *filename);
int     get_south_path(char *line, int index, t_game *game);
int     get_north_path(char *line, int index, t_game *game);
int     get_west_path(char *line, int index, t_game *game);
int     get_east_path(char *line, int index, t_game *game);
int     get_floor_rgb(t_game *game, char *line);
int     get_ceiling_rgb(t_game *game, char *line);
char    *skip_identifier_and_spaces(char *line, int index, int id_len);
int     is_valid_rgb_line(char *rgb_line);
int     has_only_digits(char *red, char *blue, char *green);
int     start_game(t_game *game);
int     validate_map_grid(t_game *game);
int     player_is_duplicated(char *line, t_game *game);
void    load_textures(t_data *data, t_tex *tex, char *path);
int     check_north_texture_name(char *texture_line);
int     check_south_texture_name(char *texture_line);
int     check_east_texture_name(char *texture_line);
int     check_west_texture_name(char *texture_line);

////////////////////////////////////////////////////////////////////////
//                             FREE FUNCTIONS                         //
////////////////////////////////////////////////////////////////////////

void    free_array(char **double_array);
int     free_all_data(t_game *game);
int     free_if_malloc_failed(char *red, char *blue, char *green, char **rgb_colors);
int     free_if_malloc_failed(char *red, char *blue, char *green, char **rgb_colors);

////////////////////////////////////////////////////////////////////////
//                             MAP CHECK FUNCTIONS                    //
////////////////////////////////////////////////////////////////////////

int     check_for_duplicate_id(t_game *game);
int     textures_before_map(t_game *game);
int     is_map_line(char *line);

////////////////////////////////////////////////////////////////////////
//                             ERROR MESSAGES FUNCTIONS               //
////////////////////////////////////////////////////////////////////////


int     file_not_found(char *filename);
int     malloc_failed(void);
int     invalid_extension(char *filename);
int     empty_map(void);
int     id_is_duplicate(int which_dir);
int     map_is_not_last(void);
int     is_identifier(char c, t_game *game);
int     invalid_map(char *line);
int     texture_missing(void);
int     east_direction_missing();
int     west_direction_missing();
int     north_direction_missing();
int     south_direction_missing();
int     ceiling_is_missing();
int     floor_is_missing();
int     textures_not_found();
int     map_is_short();
int     line_isnt_start_walled(int line_index);
int     line_isnt_end_walled(int line_index);
int     map_is_not_fully_walled();
int     stranger_element();
int     duplicated_player();
int     player_not_found();
int     invalid_north_path(char *north_path);
int     invalid_south_path(char *south_path);
int     invalid_west_path(char *west_path);
int     invalid_east_path(char *east_path);
int     forbidden_north_line(char *north_line);
int     forbidden_south_line(char *south_line);
int     forbidden_east_line(char *east_line);
int     forbidden_west_line(char *west_line);
int     map_row_is_short();
int     space_isnt_walled(void);

////////////////////////////////////////////////////////////////////////
//                             RAYCASTING FUNCTIONS                   //
////////////////////////////////////////////////////////////////////////

void	draw_tiles(t_data *data, int size);
void	draw_map(t_game *game);
void	read_map(char **map, char *str);
void	my_pixel_put(t_data *img, int x, int y, int	color);
void	player_pos(t_data *data);
void	draw_player(t_data *data);
void	free_all(t_data *data);
void 	draw_line(t_data *data, int x_end, int y_end, int color);
void	player_dir(t_data *data);
void	draw_direction(t_data *data);
void	rotate_left(t_data *data, double angle);
void	rotate_right(t_data *data, double angle);
void	rotation(t_data *data, double angle);
int		keyrelease(int keycode, t_data *data);
int		keyhook(void *data);
int		keypress(int keycode, t_data *data);
void	cast_rays(t_data *data);
void	calculation(t_data *data);
void	dda(t_data *data);
void	map_dimensions(t_data *data);
void	draw_walls(t_data *data, int x);
void	coloring(t_data *data);
void	free_maps(t_data *data);
void	load_all_textures(t_game *game);
void	load_texture(t_data *data, t_tex *tex, char *path);
void    draw_textured_wall(t_data *data, int x);
#endif

