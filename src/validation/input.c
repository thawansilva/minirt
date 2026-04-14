/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 10:11:05 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/13 22:12:07 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "validation.h"
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

static void	print_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

int	is_valid_extension(char *file)
{
	int		len;
	char	*extension;

	if (!file)
		return (0);
	len = ft_strlen(file);
	extension = ft_strrchr(file, '.');
	if (!extension || len <= 3 || ft_strcmp(".rt", extension) != 0)
		return (0);
	return (1);
}

int	read_file(char *file, t_scene *scene)
{
	int		fd;
	char	*line;

	if (!file)
	{
		print_error("Missing file");
		return (0);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error(strerror(errno));
		return (0);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_lstadd_back(&(scene->objs), ft_lstnew(line));
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	is_valid_input(char *file, t_scene *scene)
{
	t_list		*aux;
	char		**arr;
	int			i;
	t_obj_count	obj_count;
	const t_hash_item	func_objs[] = {{"A", &is_valid_ambient,
	"Invalid ambient"}, {"C", &is_valid_camera, "Invalid camera"},
	{"L", &is_valid_light, "Invalid light"},
	{"sp", &is_valid_sphere, "Invalid sphere"},
	{"pl", &is_valid_plane, "Invalid plane"},
	{"cy", &is_valid_cylinder, "Invalid cylinder"}, {NULL, NULL, NULL}};

	obj_count.ambient = 0;
	obj_count.camera = 0;
	obj_count.light = 0;
	if (!is_valid_extension(file))
	{
		print_error("Invalid extension");
		return (0);
	}
	if (read_file(file, scene) == 0)
		return (0);
	aux = scene->objs;
	if (!aux)
		return (0);
	while (aux)
	{
		arr = ft_split(aux->content, ' ');
		i = 0;
		while (func_objs[i].key)
		{
			if (ft_strcmp(func_objs[i].key, arr[0]) == 0)
			{
				if (!func_objs[i].is_valid_obj(arr))
				{
					free_arr(arr);
					print_error(func_objs[i].error_msg);
					return (0);
				}
				break ;
			}
			i++;
		}
		if (ft_strcmp(arr[0], "A") == 0)
			obj_count.ambient++;
		else if (ft_strcmp(arr[0], "C") == 0)
			obj_count.camera++;
		else if (ft_strcmp(arr[0], "L") == 0)
			obj_count.light++;
		aux = aux->next;
		free_arr(arr);
	}
	if (obj_count.ambient != 1 || obj_count.camera != 1
			|| obj_count.light != 1)
		return (0);
	return (1);
}
