NAME = cub3D
CC = cc
REQUIRED_FLAGS = -Wall -Werror -Wextra -g
LINKING_FLAGS = -lXext -lX11 -lm
LIBRARIES = libft/libft.a minilibx-linux/libmlx_Linux.a
OBJECTS = obj/main.o obj/cleaning.o obj/parsing/process_file.o obj/parsing/utils.o obj/parsing/store_textures_and_colors.o \
obj/parsing/field_utils.o obj/parsing/store_map.o obj/parsing/parse_map.o


.PHONY: all clean fclean re

all: $(NAME)

$(LIBRARIES):
	$(MAKE) -C ./libft
	$(MAKE) -C ./minilibx-linux

obj/%.o: %.c
	mkdir -p obj
	mkdir -p obj/parsing
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
