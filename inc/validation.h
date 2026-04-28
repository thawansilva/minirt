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
# include "scene.h"

typedef struct s_obj_count
{
	unsigned int	obj;
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
int		has_comment_or_spaces(char *line);
// Validate objects
int		is_valid_ambient(char **arr);
int		is_valid_camera(char **arr);
int		is_valid_light(char **arr);
int		is_valid_sphere(char **arr);
int		is_valid_plane(char **arr);
int		is_valid_cylinder(char **arr);
int		has_enough_elements(t_obj_count count);
#endif
