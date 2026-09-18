#include "cub3D.h"

bool	file_extension_check(char *file)
{
	size_t	file_name_len;
	char	*extension;

	file_name_len = ft_strlen(file);
	if (file_name_len < 5)
		return (0);
	extension = ft_strnstr(file, ".cub", file_name_len);
	if (!extension || *(extension + 4) != '\0')
		return (0);
	return (1);
}

int	main(int ac, char *av[])
{
	if (ac != 2 || !file_extension_check(av[1]))
	{
		printf("This program takes one argument: "
			"a scene description file with the .cub extension.\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
