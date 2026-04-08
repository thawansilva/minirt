/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 10:11:05 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/05 13:21:58 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ft_putstr_fd("\n", 2);
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

int	read_file(char *file, t_scene *scene)
{
	int		fd;
	char	*line;

	if (!file)
		print_error("Missing file", 2);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_lstadd_back(&(scene->objs), ft_lstnew(line));
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_content(void *content)
{
	free(content);
}

void	validate_input(char *file, t_scene *scene)
{
	t_list	*aux;
//	char	**arr;
//	const t_hash_item	func_objs[] = {{ "A", &validate_ambient,
//		"Invalid ambient" }, { "C", &validate_camera, "Invalid camera"},
//		 { "L": &validate_light, "Invalid light"},
//		 { "sp", &validate_light, "Invalid light"},
//		 { "pl", &validate_plane, "Invalid plane"},
//		 { "cy", &validate_cylinder, "Invalid cylinder"}};

	if (!is_valid_extension(file))
		print_error("Invalid extension", 1);
	if (read_file(file, scene) == 0)
	{
		perror(strerror(errno));
		exit(1);
	}
	aux = scene->objs;
	(void) aux;
//	while (aux)
//	{
//		arr = ft_split(aux->content, ' ');
//		if (ft_strcmp(arr[0], "A") == 0)
//		{
//			if (!is_valid_ambient(arr))
//			{
//				free_arr(arr);
//				ft_lstclear(scene->objs, &free_content);
//				print_error("Invalid ambient", 1);
//			}
//			ft_putstr_fd("Valid", 1);
//		}
//		else if (ft_strcmp(arr[0], "C") == 0)
//		{
//			if (!is_valid_camera(arr))
//			{
//				free_arr(arr);
//				ft_lstclear(scene->objs, &free_content);
//				print_error("Invalid camera", 1);
//			}
//			ft_putstr_fd("Valid", 1);
//		}
//		else if (ft_strcmp(arr[0], "L") == 0)
//		{
//			if (!is_valid_light(arr))
//			{
//				free_arr(arr);
//				ft_lstclear(scene->objs, &free_content);
//				print_error("Invalid light", 1);
//			}
//			ft_putstr_fd("Valid", 1);
//		}
//		else if (ft_strcmp(arr[0], "sp") == 0)
//		{
//			if (!is_valid_sphere(arr))
//			{
//				free_arr(arr);
//				ft_lstclear(scene->objs, &free_content);
//				print_error("Invalid sphere", 1);
//			}
//			ft_putstr_fd("Valid", 1);
//		}
//		else if (ft_strcmp(arr[0], "pl") == 0)
//		{
//			if (!is_valid_plane(arr))
//			{
//				free_arr(arr);
//				ft_lstclear(scene->objs, &free_content);
//				print_error("Invalid plane", 1);
//			}
//			ft_putstr_fd("Valid", 1);
//		}
//		else if (ft_strcmp(arr[0], "cy") == 0)
//		{
//			if (!is_valid_cylinder(arr))
//			{
//				free_arr(arr);
//				ft_lstclear(scene->objs, &free_content);
//				print_error("Invalid cylinder", 1);
//			}
//			ft_putstr_fd("Valid", 1);
//		}
//		else
//		{
//			free_arr(arr);
//			ft_lstclear(scene->objs, &free_content);
//			print_error("Invalid object", 1);
//		}
//		aux = aux->next;
//		free_arr(arr);
//	}
}
