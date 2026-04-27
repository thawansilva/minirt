/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 09:52:36 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/26 14:39:54 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation_bonus.h"
#include "free_memory_bonus.h"
#include "parser_bonus.h"
#include "libft.h"

int	main(int argc, char *argv[])
{
	t_scene	scene;

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
