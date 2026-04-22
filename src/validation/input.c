/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 10:11:05 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/22 20:26:01 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "validation.h"
#include "free_memory.h"
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

void	show_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

int	read_file(char *file, t_scene *scene)
{
	int		fd;
	char	*line;

	if (!file || !scene)
		return (show_error("Missing file or invalid scene"), 0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (show_error(strerror(errno)), 0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strcmp(line, "\n") == 0)
			free(line);
		else
			ft_lstadd_back(&(scene->objs), ft_lstnew(line));
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	is_allowed_object(char **arr, int idx)
{
	const t_hash_item	func_objs[] = {
	{"A", &is_valid_ambient, "Invalid ambient"},
	{"C", &is_valid_camera, "Invalid camera"},
	{"L", &is_valid_light, "Invalid light"},
	{"sp", &is_valid_sphere, "Invalid sphere"},
	{"pl", &is_valid_plane, "Invalid plane"},
	{"cy", &is_valid_cylinder, "Invalid cylinder"},
	{NULL, NULL, "Non-existent object"}};

	while (func_objs[idx].key)
	{
		if (ft_strcmp(func_objs[idx].key, arr[0]) == 0)
		{
			if (!func_objs[idx].is_valid_obj(arr))
				return (show_error(func_objs[idx].error_msg), 0);
			break ;
		}
		idx++;
	}
	if (func_objs[idx].key == NULL)
		return (show_error(func_objs[idx].error_msg), 0);
	return (1);
}

int	is_valid_object(t_list *objs, t_obj_count *obj_count)
{
	char	**arr;
	int		i;

	arr = ft_split(objs->content, ' ');
	if (!arr)
		return (0);
	i = 0;
	if (!is_allowed_object(arr, i))
	{
		free_arr(arr);
		return (0);
	}
	if (ft_strcmp(arr[0], "A") == 0)
		obj_count->ambient++;
	else if (ft_strcmp(arr[0], "C") == 0)
		obj_count->camera++;
	else if (ft_strcmp(arr[0], "L") == 0)
		obj_count->light++;
	else
		obj_count->obj++;
	free_arr(arr);
	return (1);
}

int	is_valid_input(char *file, t_scene *scene)
{
	t_list		*aux;
	t_obj_count	obj_count;

	if (!is_valid_extension(file) || read_file(file, scene) == 0
		|| !scene->objs)
		return (0);
	obj_count = (t_obj_count){.ambient = 0, .camera = 0, .light = 0, .obj = 0};
	aux = scene->objs;
	while (aux)
	{
		if (!is_valid_object(aux, &obj_count))
			return (0);
		aux = aux->next;
	}
	if (obj_count.ambient != 1 || obj_count.camera != 1
		|| obj_count.light != 1 || obj_count.obj == 0)
		return (0);
	scene->num_lights = obj_count.light;
	scene->num_objs = obj_count.obj;
	return (1);
}
