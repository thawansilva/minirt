/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 13:26:58 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/22 20:33:25 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "validation.h"
#include "free_memory.h"

void	parse_ambient(char **arr, t_scene *scene)
{
	scene->ambient.lightness = ft_atod(arr[1]);
	save_color(arr[2], &scene->ambient.color);
}

void	parse_camera(char **arr, t_scene *scene)
{
	save_vec4(arr[1], &scene->camera.coordinate);
	save_vec4(arr[2], &scene->camera.norm_vector);
	scene->camera.fov = (unsigned char)ft_atoi(arr[3]);
}

void	parse_light(char **arr, t_scene *scene)
{
	save_vec4(arr[1], &scene->light->coordinate);
	scene->light->brightness = ft_atod(arr[2]);
	save_color(arr[3], &scene->light->color);
}

void	init_elements_of_scene(t_scene *scene)
{
	scene->light = (t_light *)ft_calloc(sizeof(t_light), scene->num_lights + 1);
	scene->surfaces = (t_surface *)ft_calloc(sizeof(t_surface),
			scene->num_objs + 1);
}

void	parse_elements(t_scene *scene)
{
	int							i;
	t_list						*aux;
	char						**arr;
	const t_hash_item_parser	parse_objs[] = {{"A", &parse_ambient},
	{"C", &parse_camera}, {"L", &parse_light}, {"sp", &parse_sphere},
	{"pl", &parse_plane}, {"cy", &parse_cylinder}, {NULL, NULL}};

	aux = scene->objs;
	init_elements_of_scene(scene);
	while (aux)
	{
		i = 0;
		arr = ft_split(aux->content, ' ');
		while (parse_objs[i].key)
		{
			if (ft_strcmp(parse_objs[i].key, arr[0]) == 0)
			{
				parse_objs[i].parse(arr, scene);
				break ;
			}
			i++;
		}
		free_arr(arr);
		aux = aux->next;
	}
}
