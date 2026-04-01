#include "libft.h"
#include "validation.h"

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
	scene->lines = ft_split_charset(file, " \t");
	if (!scene->lines)
		print_error("Split info scenes", 1);
	
}

void	validate_input(char *file, t_scene *scene)
{
	if (!is_valid_extension(file))
		print_error("Invalid extension", 1);
//	read_file(char *file, t_scene *scene);
}
