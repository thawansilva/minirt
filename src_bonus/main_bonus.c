#include "validation_bonus.h"
#include "free_memory_bonus.h"
#include "parser_bonus.h"
#include "libft.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_scene	scene;

//	printf("%zu t_vec4\n", sizeof(t_vec4));
//	printf("%zu t_ambient\n", sizeof(t_ambient));
//	printf("%zu t_camera\n", sizeof(t_camera));
//	printf("%zu t_light\n", sizeof(t_light));
//	printf("%zu t_specular\n", sizeof(t_specular));
//	printf("%zu t_surface_parameters\n", sizeof(t_surface_parameters));
//	printf("%zu t_surface_type\n", sizeof(t_surface_type));
//	printf("%zu t_obj\n", sizeof(t_obj));
//	printf("%zu t_ray\n", sizeof(t_ray));
//	printf("%zu t_scene\n", sizeof(t_scene));
//	printf("%zu t_list\n", sizeof(t_list));
//	printf("%zu t_color\n", sizeof(t_color));
	scene = (t_scene){};
	if (argc != 2)
	{
		show_error("Usage: ./miniRT_bonus <file>");
		return (0);
	}
	if (is_valid_input(argv[1], &scene))
		parse_elements(&scene);
	free_scene(&scene);
	return (0);
}

