/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:00:03 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/18 15:21:43 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H
# include "libft.h"
# include "objects.h"
# include "scene.h"

typedef struct s_scene
{
	t_list			*objs;
	t_camera		camera;
	t_ambient		ambient;
	t_light			*light;
	t_surface		*surfaces;
	t_specular		*specular;
	unsigned int	num_objs;
	unsigned int	num_lights;
}	t_scene;

typedef struct s_obj_count
{
	unsigned char	camera;
	unsigned char	ambient;
	unsigned char	light;
}	t_obj_count;

typedef struct s_hash_item
{
	char	*key;
	int		(*is_valid_obj)(char **);
	char	*error_msg;
}	t_hash_item;

int		is_valid_input(char *file, t_scene *scene);
int		read_file(char *file, t_scene *scene);
int		is_valid_extension(char *file);
void	show_error(char *msg);
// Validate properties
int		is_valid_float(const char *str);
int		is_valid_coordinates(char *str);
int		is_valid_ratio(char *str);
int		is_valid_color(char *str);
int		is_valid_fov(char *str);
int		is_valid_normalized_vector(char *str);
int		is_valid_coordinates(char *str);
int		is_valid_float(const char *str);
int		is_valid_int(const char *str);
// Validate objects
int		is_valid_ambient(char **arr);
int		is_valid_camera(char **arr);
int		is_valid_light(char **arr);
int		is_valid_sphere(char **arr);
int		is_valid_plane(char **arr);
int		is_valid_cylinder(char **arr);
// Free Memory
void	free_arr(char **arr);
void	free_content(void *content);
#endif
