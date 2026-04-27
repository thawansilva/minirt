/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_elements_integration.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 10:00:00 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/26 13:11:28 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "parser_bonus.h"
#include "objects_bonus.h"
#include "scene_bonus.h"
#include "libft.h"

/* ========================================================= */
/* HELPER FUNCTIONS */
/* ========================================================= */

static t_scene	*make_empty_scene(void)
{
	t_scene	*scene;

	scene = (t_scene *)calloc(1, sizeof(t_scene));
	scene->objs = NULL;
	scene->light = NULL;
	scene->surfaces = NULL;
	scene->idx_obj = 0;
	scene->num_objs = 0;
	scene->num_lights = 0;
	return (scene);
}

static void	add_object_to_scene(t_scene *scene, const char *obj_line)
{
	t_list	*new_node;
	char	*content;

	content = strdup(obj_line);
	new_node = ft_lstnew(content);
	ft_lstadd_back(&scene->objs, new_node);
}

static void	free_scene_complete(t_scene *scene)
{
	t_list	*current;
	t_list	*next;

	if (!scene)
		return ;
	current = scene->objs;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	free(scene->light);
	free(scene->surfaces);
	free(scene);
}

static int	count_list_items(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

/* ========================================================= */
/* BASIC INTEGRATION TESTS */
/* ========================================================= */

void	test_parse_elements_single_ambient(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 0;
	scene->num_lights = 0;
	add_object_to_scene(scene, "A 0.2 255,255,255");

	parse_elements(scene);

	assert_double_equal(scene->ambient.lightness, 0.2, 0.0001);
	assert_int_equal(scene->ambient.color.r, 255);
	assert_int_equal(scene->ambient.color.g, 255);
	assert_int_equal(scene->ambient.color.b, 255);

	free_scene_complete(scene);
}

void	test_parse_elements_single_camera(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 0;
	scene->num_lights = 0;
	add_object_to_scene(scene, "C 0,0,0 0,0,1 70");

	parse_elements(scene);

	assert_true(fabs(scene->camera.coordinate.x) < 0.0001);
	assert_true(fabs(scene->camera.coordinate.y) < 0.0001);
	assert_true(fabs(scene->camera.coordinate.z) < 0.0001);
	assert_true(fabs(scene->camera.norm_vector.z - 1.0) < 0.0001);
	assert_int_equal(scene->camera.fov, 70);

	free_scene_complete(scene);
}

void	test_parse_elements_single_light(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 0;
	scene->num_lights = 1;
	add_object_to_scene(scene, "L 10,10,10 0.8 255,255,255");

	parse_elements(scene);

	assert_true(fabs(scene->light[0].coordinate.x - 10.0) < 0.0001);
	assert_true(fabs(scene->light[0].coordinate.y - 10.0) < 0.0001);
	assert_true(fabs(scene->light[0].coordinate.z - 10.0) < 0.0001);
	assert_double_equal(scene->light[0].brightness, 0.8, 0.0001);
	assert_int_equal(scene->light[0].color.r, 255);

	free_scene_complete(scene);
}

void	test_parse_elements_single_sphere(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 1;
	scene->num_lights = 0;
	add_object_to_scene(scene, "sp 0,0,0 2.0 255,0,0");

	parse_elements(scene);

	assert_int_equal(scene->surfaces[0].type, SPHERE);
	assert_int_equal(scene->surfaces[0].obj.color.r, 255);
	assert_int_equal(scene->idx_obj, 1);

	free_scene_complete(scene);
}

void	test_parse_elements_single_plane(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 1;
	scene->num_lights = 0;
	add_object_to_scene(scene, "pl 0,0,0 0,1,0 100,100,100");

	parse_elements(scene);

	assert_int_equal(scene->surfaces[0].type, PLANE);
	assert_true(fabs(scene->surfaces[0].obj.orientation.y - 1.0) < 0.0001);
	assert_int_equal(scene->idx_obj, 1);

	free_scene_complete(scene);
}

void	test_parse_elements_single_cylinder(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 1;
	scene->num_lights = 0;
	add_object_to_scene(scene, "cy 0,0,0 0,1,0 1.0 5.0 200,200,200");

	parse_elements(scene);

	assert_int_equal(scene->surfaces[0].type, CYLINDER);
	assert_int_equal(scene->idx_obj, 1);

	free_scene_complete(scene);
}

/* ========================================================= */
/* COMPLETE SCENE TESTS */
/* ========================================================= */

void	test_parse_elements_complete_basic_scene(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 3;
	scene->num_lights = 1;
	add_object_to_scene(scene, "A 0.3 255,255,255");
	add_object_to_scene(scene, "C 0,0,5 0,0,-1 70");
	add_object_to_scene(scene, "L 5,5,5 0.6 255,255,255");
	add_object_to_scene(scene, "sp 0,0,0 2.0 255,0,0");
	add_object_to_scene(scene, "pl 0,-1,0 0,1,0 0,255,0");
	add_object_to_scene(scene, "cy 0,0,-5 0,1,0 1.0 10.0 0,0,255");

	parse_elements(scene);

	assert_double_equal(scene->ambient.lightness, 0.3, 0.0001);
	assert_int_equal(scene->camera.fov, 70);
	assert_int_equal(scene->light[0].color.r, 255);
	assert_int_equal(scene->surfaces[0].type, SPHERE);
	assert_int_equal(scene->surfaces[1].type, PLANE);
	assert_int_equal(scene->surfaces[2].type, CYLINDER);
	assert_int_equal(scene->idx_obj, 3);

	free_scene_complete(scene);
}

void	test_parse_elements_all_bonus_objects(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 3;
	scene->num_lights = 0;
	add_object_to_scene(scene, "co 0,0,0 2.0 255,0,0");
	add_object_to_scene(scene, "hy 10,10,10 0,1,0 0,255,0");
	add_object_to_scene(scene, "pa 20,20,20 0,1,0 0,0,255");

	parse_elements(scene);

	assert_int_equal(scene->surfaces[0].type, CONE);
	assert_int_equal(scene->surfaces[1].type, HYPERBOLOID);
	assert_int_equal(scene->surfaces[2].type, PARABOLOID);
	assert_int_equal(scene->idx_obj, 3);
	assert_int_equal(scene->surfaces[0].obj.color.r, 255);
	assert_int_equal(scene->surfaces[1].obj.color.g, 255);
	assert_int_equal(scene->surfaces[2].obj.color.b, 255);

	free_scene_complete(scene);
}

void	test_parse_elements_multiple_lights(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 0;
	scene->num_lights = 3;
	add_object_to_scene(scene, "L 0,0,0 0.5 255,0,0");
	add_object_to_scene(scene, "L 10,10,10 0.6 0,255,0");
	add_object_to_scene(scene, "L -10,-10,-10 0.7 0,0,255");

	parse_elements(scene);

	assert_double_equal(scene->light[0].brightness, 0.5, 0.0001);
	assert_double_equal(scene->light[1].brightness, 0.6, 0.0001);
	assert_double_equal(scene->light[2].brightness, 0.7, 0.0001);
	assert_int_equal(scene->light[0].color.r, 255);
	assert_int_equal(scene->light[1].color.g, 255);
	assert_int_equal(scene->light[2].color.b, 255);

	free_scene_complete(scene);
}

void	test_parse_elements_multiple_spheres(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 3;
	scene->num_lights = 0;
	add_object_to_scene(scene, "sp 0,0,0 1.0 255,0,0");
	add_object_to_scene(scene, "sp 5,5,5 2.0 0,255,0");
	add_object_to_scene(scene, "sp -5,-5,-5 3.0 0,0,255");

	parse_elements(scene);

	assert_int_equal(scene->surfaces[0].type, SPHERE);
	assert_int_equal(scene->surfaces[1].type, SPHERE);
	assert_int_equal(scene->surfaces[2].type, SPHERE);
	assert_int_equal(scene->idx_obj, 3);
	assert_int_equal(scene->surfaces[0].obj.color.r, 255);
	assert_int_equal(scene->surfaces[1].obj.color.g, 255);
	assert_int_equal(scene->surfaces[2].obj.color.b, 255);

	free_scene_complete(scene);
}

void	test_parse_elements_mixed_objects(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 6;
	scene->num_lights = 0;
	add_object_to_scene(scene, "sp 0,0,0 1.0 255,0,0");
	add_object_to_scene(scene, "pl 0,-1,0 0,1,0 128,128,128");
	add_object_to_scene(scene, "cy 0,0,-5 0,1,0 0.5 5.0 64,64,64");
	add_object_to_scene(scene, "co 5,5,5 1.5 200,100,50");
	add_object_to_scene(scene, "hy 10,10,10 0,1,0 100,100,100");
	add_object_to_scene(scene, "pa -5,-5,-5 0,1,0 150,150,150");

	parse_elements(scene);

	assert_int_equal(scene->surfaces[0].type, SPHERE);
	assert_int_equal(scene->surfaces[1].type, PLANE);
	assert_int_equal(scene->surfaces[2].type, CYLINDER);
	assert_int_equal(scene->surfaces[3].type, CONE);
	assert_int_equal(scene->surfaces[4].type, HYPERBOLOID);
	assert_int_equal(scene->surfaces[5].type, PARABOLOID);
	assert_int_equal(scene->idx_obj, 6);

	free_scene_complete(scene);
}

/* ========================================================= */
/* EDGE CASE TESTS */
/* ========================================================= */

void	test_parse_elements_negative_coordinates(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 1;
	scene->num_lights = 1;
	add_object_to_scene(scene, "C -10,-20,-30 0,0,1 90");
	add_object_to_scene(scene, "L -5,-10,-15 0.5 100,100,100");
	add_object_to_scene(scene, "sp -5,-10,-15 1.0 50,50,50");

	parse_elements(scene);

	assert_true(fabs(scene->camera.coordinate.x + 10.0) < 0.0001);
	assert_true(fabs(scene->camera.coordinate.y + 20.0) < 0.0001);
	assert_true(fabs(scene->camera.coordinate.z + 30.0) < 0.0001);
	assert_true(fabs(scene->light[0].coordinate.x + 5.0) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.x + 5.0) < 0.0001);

	free_scene_complete(scene);
}

void	test_parse_elements_decimal_values(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 1;
	scene->num_lights = 1;
	add_object_to_scene(scene, "A 0.5 200,150,100");
	add_object_to_scene(scene, "sp 1.5,2.7,3.9 2.5 255,200,150");

	parse_elements(scene);

	assert_double_equal(scene->ambient.lightness, 0.5, 0.0001);
	assert_int_equal(scene->ambient.color.r, 200);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.x - 1.5) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.y - 2.7) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.z - 3.9) < 0.0001);

	free_scene_complete(scene);
}

void	test_parse_elements_large_values(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 1;
	scene->num_lights = 0;
	add_object_to_scene(scene, "sp 1000,2000,3000 100.0 255,255,255");

	parse_elements(scene);

	assert_true(fabs(scene->surfaces[0].obj.coordinate.x - 1000.0) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.y - 2000.0) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.z - 3000.0) < 0.0001);

	free_scene_complete(scene);
}

void	test_parse_elements_zero_values(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 1;
	scene->num_lights = 0;
	add_object_to_scene(scene, "sp 0,0,0 0.0 0,0,0");

	parse_elements(scene);

	assert_true(fabs(scene->surfaces[0].obj.coordinate.x) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.y) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.z) < 0.0001);
	assert_int_equal(scene->surfaces[0].obj.color.r, 0);
	assert_int_equal(scene->surfaces[0].obj.color.g, 0);
	assert_int_equal(scene->surfaces[0].obj.color.b, 0);

	free_scene_complete(scene);
}

void	test_parse_elements_scene_ordering(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 3;
	scene->num_lights = 0;
	add_object_to_scene(scene, "sp 0,0,0 1.0 255,0,0");
	add_object_to_scene(scene, "sp 1,1,1 2.0 0,255,0");
	add_object_to_scene(scene, "sp 2,2,2 3.0 0,0,255");

	parse_elements(scene);

	assert_int_equal(scene->surfaces[0].obj.color.r, 255);
	assert_int_equal(scene->surfaces[1].obj.color.g, 255);
	assert_int_equal(scene->surfaces[2].obj.color.b, 255);
	assert_int_equal(scene->idx_obj, 3);

	free_scene_complete(scene);
}

/* ========================================================= */
/* INTEGRATION WITH INITIALIZATION */
/* ========================================================= */

void	test_parse_elements_initializes_light_array(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 0;
	scene->num_lights = 2;
	add_object_to_scene(scene, "L 0,0,0 0.5 255,255,255");
	add_object_to_scene(scene, "L 10,10,10 0.8 100,100,100");

	parse_elements(scene);

	assert_non_null(scene->light);
	assert_double_equal(scene->light[0].brightness, 0.5, 0.0001);
	assert_double_equal(scene->light[1].brightness, 0.8, 0.0001);

	free_scene_complete(scene);
}

void	test_parse_elements_initializes_surfaces_array(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 2;
	scene->num_lights = 0;
	add_object_to_scene(scene, "sp 0,0,0 1.0 255,0,0");
	add_object_to_scene(scene, "pl 0,-1,0 0,1,0 0,255,0");

	parse_elements(scene);

	assert_non_null(scene->surfaces);
	assert_int_equal(scene->surfaces[0].type, SPHERE);
	assert_int_equal(scene->surfaces[1].type, PLANE);

	free_scene_complete(scene);
}

/* ========================================================= */
/* COMPLEX SCENE SCENARIOS */
/* ========================================================= */

void	test_parse_elements_realistic_scene(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 5;
	scene->num_lights = 2;
	add_object_to_scene(scene, "A 0.2 255,255,255");
	add_object_to_scene(scene, "C 0,0,10 0,0,-1 70");
	add_object_to_scene(scene, "L 10,10,20 0.8 255,255,255");
	add_object_to_scene(scene, "L -10,5,-10 0.5 200,200,200");
	add_object_to_scene(scene, "sp 0,0,0 2.0 255,0,0");
	add_object_to_scene(scene, "sp 5,5,-5 1.5 0,255,0");
	add_object_to_scene(scene, "pl 0,-5,0 0,1,0 100,100,100");
	add_object_to_scene(scene, "cy 0,0,-10 0,1,0 1.0 8.0 50,50,200");

	parse_elements(scene);

	assert_double_equal(scene->ambient.lightness, 0.2, 0.0001);
	assert_int_equal(scene->camera.fov, 70);
	assert_double_equal(scene->light[0].brightness, 0.8, 0.0001);
	assert_double_equal(scene->light[1].brightness, 0.5, 0.0001);
	assert_int_equal(scene->surfaces[0].type, SPHERE);
	assert_int_equal(scene->surfaces[1].type, SPHERE);
	assert_int_equal(scene->surfaces[2].type, PLANE);
	assert_int_equal(scene->surfaces[3].type, CYLINDER);
	assert_int_equal(scene->idx_obj, 4);

	free_scene_complete(scene);
}

void	test_parse_elements_all_types_mixed(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 9;
	scene->num_lights = 1;
	add_object_to_scene(scene, "A 0.3 255,255,255");
	add_object_to_scene(scene, "C 0,0,0 0,0,1 75");
	add_object_to_scene(scene, "L 5,5,5 0.7 255,255,255");
	add_object_to_scene(scene, "sp 0,0,0 1.0 255,0,0");
	add_object_to_scene(scene, "pl 0,-10,0 0,1,0 128,128,128");
	add_object_to_scene(scene, "cy 0,0,-5 0,1,0 0.5 5.0 64,64,64");
	add_object_to_scene(scene, "co 5,5,5 1.0 200,100,50");
	add_object_to_scene(scene, "hy 10,10,10 0,1,0 100,100,100");
	add_object_to_scene(scene, "pa -5,-5,-5 0,1,0 150,150,150");

	parse_elements(scene);

	assert_int_equal(scene->surfaces[0].type, SPHERE);
	assert_int_equal(scene->surfaces[1].type, PLANE);
	assert_int_equal(scene->surfaces[2].type, CYLINDER);
	assert_int_equal(scene->surfaces[3].type, CONE);
	assert_int_equal(scene->surfaces[4].type, HYPERBOLOID);
	assert_int_equal(scene->surfaces[5].type, PARABOLOID);
	assert_int_equal(scene->idx_obj, 6);

	free_scene_complete(scene);
}

void	test_parse_elements_color_preservation(void **state)
{
	(void)state;
	t_scene	*scene = make_empty_scene();

	scene->num_objs = 4;
	scene->num_lights = 0;
	add_object_to_scene(scene, "sp 0,0,0 1.0 255,0,0");
	add_object_to_scene(scene, "sp 1,1,1 1.0 0,255,0");
	add_object_to_scene(scene, "sp 2,2,2 1.0 0,0,255");
	add_object_to_scene(scene, "sp 3,3,3 1.0 128,128,128");

	parse_elements(scene);

	assert_int_equal(scene->surfaces[0].obj.color.r, 255);
	assert_int_equal(scene->surfaces[0].obj.color.g, 0);
	assert_int_equal(scene->surfaces[0].obj.color.b, 0);

	assert_int_equal(scene->surfaces[1].obj.color.r, 0);
	assert_int_equal(scene->surfaces[1].obj.color.g, 255);
	assert_int_equal(scene->surfaces[1].obj.color.b, 0);

	assert_int_equal(scene->surfaces[2].obj.color.r, 0);
	assert_int_equal(scene->surfaces[2].obj.color.g, 0);
	assert_int_equal(scene->surfaces[2].obj.color.b, 255);

	assert_int_equal(scene->surfaces[3].obj.color.r, 128);
	assert_int_equal(scene->surfaces[3].obj.color.g, 128);
	assert_int_equal(scene->surfaces[3].obj.color.b, 128);

	free_scene_complete(scene);
}