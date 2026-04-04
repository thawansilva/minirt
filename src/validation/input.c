#include "libft.h"
#include "validation.h"
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

static void	print_error(char *msg, int exit_code)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	exit(exit_code);
}

int	is_valid_extension(char *file)
{
	int	len;
	
	if (!file)
		return (0);
	len = ft_strlen(file);
	if (len <= 3 || ft_strcmp(".rt", file + (len - 3)) != 0)
		return (0);
	return (1);
}

void	read_file(char *file, t_scene *scene)
{
	int		fd;
	char	*line;

	if (!file)
		print_error("Missing file", 2);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(strerror(errno));
		exit(1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_lstadd_back(&(scene->objs), ft_lstnew(line));
		line = get_next_line(fd);
	}
	close(fd);
}

void	validate_input(char *file, t_scene *scene)
{
	if (!is_valid_extension(file))
		print_error("Invalid extension", 1);
	read_file(file, scene);
}
