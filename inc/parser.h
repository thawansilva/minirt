/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:00:23 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/22 20:00:26 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "scene.h"

typedef struct s_hash_item_parser
{
	char	*key;
	void	(*parse)(char **, t_scene *);
}	t_hash_item_parser;

void	parse_elements(t_scene *scene);

// Object parsers
void	parse_ambient(char **arr, t_scene *scene);
void	parse_camera(char **arr, t_scene *scene);
void	parse_light(char **arr, t_scene *scene);
void	parse_sphere(char **arr, t_scene *scene);
void	parse_plane(char **arr, t_scene *scene);
void	parse_cylinder(char **arr, t_scene *scene);

// Low-level savers
void	save_double(const char *token, double *dst);
void	save_color(const char *token, t_color *dst);
void	save_vec4(const char *token, t_vec4 *dst);
#endif
