NAME = cub3D
CC = cc
REQUIRED_FLAGS = -Wall -Werror -Wextra
LINKING_FLAGS = -lXext -lX11 -lm
LIBRARIES = libft/libft.a minilibx-linux/libmlx_Linux.a
OBJECTS = obj/main.o obj/cleaning.o obj/parsing/process_file.o obj/parsing/utils.o

.PHONY: all clean fclean re

all: $(NAME)

$(LIBRARIES):
	$(MAKE) -C ./libft
	$(MAKE) -C ./minilibx-linux

obj/%.o: %.c
	mkdir -p obj
	$(CC) $(REQUIRED_FLAGS) -c $< -o $@

$(NAME): $(LIBRARIES) $(OBJECTS)
	$(CC) $(REQUIRED_FLAGS) $(OBJECTS) $(LIBRARIES) $(LINKING_FLAGS) -o $@

clean:
	$(MAKE) -C ./libft clean
	rm -rf minilibx-linux/obj
	rm -rf obj

fclean:
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./minilibx-linux clean
	rm -rf obj $(NAME)

re: fclean all
