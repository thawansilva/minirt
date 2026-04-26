/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 16:00:03 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/22 20:00:05 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_MEMORY_H
# define FREE_MEMORY_H
# include "scene_bonus.h"

void	free_arr(char **arr);
void	free_content(void *content);
void	free_scene(t_scene *scene);
#endif
