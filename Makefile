NAME = Cube
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c element.c
MLX_DIR = minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -I$(MLX_DIR)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all