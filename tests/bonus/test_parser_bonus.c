/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 10:00:00 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/25 10:00:00 by thaperei         ###   ########.fr       */
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

static t_scene	*make_scene(void)
{
	t_scene	*scene;

	scene = (t_scene *)calloc(1, sizeof(t_scene));
	scene->light = (t_light *)calloc(1, sizeof(t_light));
	scene->surfaces = (t_surface *)calloc(1000, sizeof(t_surface));
	scene->idx_obj = 0;
	scene->num_objs = 0;
	return (scene);
}

static void	free_scene(t_scene *scene)
{
	if (scene)
	{
		free(scene->light);
		free(scene->surfaces);
		free(scene);
	}
}

/* Helper to create token array */

static char	**make_arr(const char *str1, const char *str2, const char *str3,
		const char *str4)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * 5);
	arr[0] = (char *)str1;
	arr[1] = (char *)str2;
	arr[2] = (char *)str3;
	arr[3] = (char *)str4;
	arr[4] = NULL;
	return (arr);
}

static char	**make_arr_5(const char *str1, const char *str2,
		const char *str3, const char *str4, const char *str5)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * 6);
	arr[0] = (char *)str1;
	arr[1] = (char *)str2;
	arr[2] = (char *)str3;
	arr[3] = (char *)str4;
	arr[4] = (char *)str5;
	arr[5] = NULL;
	return (arr);
}

static char	**make_arr_6(const char *str1, const char *str2,
		const char *str3, const char *str4, const char *str5,
		const char *str6)
{
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * 7);
	arr[0] = (char *)str1;
	arr[1] = (char *)str2;
	arr[2] = (char *)str3;
	arr[3] = (char *)str4;
	arr[4] = (char *)str5;
	arr[5] = (char *)str6;
	arr[6] = NULL;
	return (arr);
}

/* ========================================================= */
/* PARSE_CONE TESTS (uses sphere parser logic) */
/* ========================================================= */

void	test_parse_cone_basic(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("co", "0,0,0", "2.0", "255,255,255");

	parse_sphere(arr, scene);
	assert_int_equal(scene->surfaces[0].type, CONE);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.x) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.y) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.z) < 0.0001);
	assert_int_equal(scene->surfaces[0].obj.color.r, 255);
	assert_int_equal(scene->surfaces[0].obj.color.g, 255);
	assert_int_equal(scene->surfaces[0].obj.color.b, 255);
//	assert_int_equal(scene->idx_obj, 1);

	free(arr);
	free_scene(scene);
}

void	test_parse_cone_offset_position(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("co", "10.5,20.3,-15.7", "3.5", "128,64,32");

	parse_sphere(arr, scene);
	assert_int_equal(scene->surfaces[0].type, CONE);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.x - 10.5) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.y - 20.3) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.z + 15.7) < 0.0001);
	assert_int_equal(scene->surfaces[0].obj.color.r, 128);
	assert_int_equal(scene->surfaces[0].obj.color.g, 64);
	assert_int_equal(scene->surfaces[0].obj.color.b, 32);

	free(arr);
	free_scene(scene);
}

void	test_parse_cone_diameter_variations(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("co", "5,5,5", "8.5", "100,100,100");

	parse_sphere(arr, scene);
	assert_int_equal(scene->surfaces[0].type, CONE);

	free(arr);
	free_scene(scene);
}

void	test_parse_cone_red_color(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("co", "0,0,0", "2.0", "255,0,0");

	parse_sphere(arr, scene);
	assert_int_equal(scene->surfaces[0].obj.color.r, 255);
	assert_int_equal(scene->surfaces[0].obj.color.g, 0);
	assert_int_equal(scene->surfaces[0].obj.color.b, 0);

	free(arr);
	free_scene(scene);
}

void	test_parse_cone_black_color(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("co", "0,0,0", "2.0", "0,0,0");

	parse_sphere(arr, scene);
	assert_int_equal(scene->surfaces[0].obj.color.r, 0);
	assert_int_equal(scene->surfaces[0].obj.color.g, 0);
	assert_int_equal(scene->surfaces[0].obj.color.b, 0);

	free(arr);
	free_scene(scene);
}

void	test_parse_cone_negative_coordinates(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("co", "-50,-100,-150", "5.0",
		"75,75,75");

	parse_sphere(arr, scene);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.x + 50.0) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.y + 100.0) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.z + 150.0) < 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_cone_decimal_coordinates(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("co", "1.5,2.7,3.9", "2.0",
		"150,150,150");

	parse_sphere(arr, scene);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.x - 1.5) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.y - 2.7) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.z - 3.9) < 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_cone_unbounded(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("co", "0,0,0", "2.0", "255,255,255");

	parse_sphere(arr, scene);
	/* Cones are unbounded like spheres */
	assert_int_equal(scene->surfaces[0].is_bounded, 0);

	free(arr);
	free_scene(scene);
}

void	test_parse_cone_multiple_cones(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr1 = make_arr("co", "0,0,0", "2.0", "255,0,0");
	char	**arr2 = make_arr("co", "10,10,10", "3.0", "0,255,0");

	parse_sphere(arr1, scene);
	parse_sphere(arr2, scene);

	assert_int_equal(scene->surfaces[0].type, CONE);
	assert_int_equal(scene->surfaces[1].type, CONE);
	assert_int_equal(scene->surfaces[0].obj.color.r, 255);
	assert_int_equal(scene->surfaces[1].obj.color.g, 255);
	assert_int_equal(scene->idx_obj, 2);

	free(arr1);
	free(arr2);
	free_scene(scene);
}

/* ========================================================= */
/* PARSE_HYPERBOLOID TESTS (uses plane parser logic) */
/* ========================================================= */

void	test_parse_hyperboloid_basic(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("hy", "0,0,0", "0.0,1.0,0.0", "255,255,255");

	parse_plane(arr, scene);
	assert_int_equal(scene->surfaces[0].type, HYPERBOLOID);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.x) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.y) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.z) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.orientation.y - 1.0) < 0.0001);
	assert_int_equal(scene->surfaces[0].obj.color.r, 255);
	assert_int_equal(scene->surfaces[0].obj.color.g, 255);
	assert_int_equal(scene->surfaces[0].obj.color.b, 255);
	assert_int_equal(scene->idx_obj, 1);

	free(arr);
	free_scene(scene);
}

void	test_parse_hyperboloid_offset_position(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("hy", "5.5,10.3,-8.7", "1.0,0.0,0.0",  "100,150,200");

	parse_plane(arr, scene);
	assert_int_equal(scene->surfaces[0].type, HYPERBOLOID);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.x - 5.5) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.y - 10.3) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.z + 8.7) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.orientation.x - 1.0) < 0.0001);
	assert_int_equal(scene->surfaces[0].obj.color.r, 100);
	assert_int_equal(scene->surfaces[0].obj.color.g, 150);
	assert_int_equal(scene->surfaces[0].obj.color.b, 200);

	free(arr);
	free_scene(scene);
}

void	test_parse_hyperboloid_different_orientations(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("hy", "0,0,0", "0.0,0.0,1.0", "128,128,128");

	parse_plane(arr, scene);
	assert_true(fabs(scene->surfaces[0].obj.orientation.z - 1.0) < 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_hyperboloid_red_color(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("hy", "0,0,0", "0.0,1.0,0.0", "255,0,0");

	parse_plane(arr, scene);
	assert_int_equal(scene->surfaces[0].obj.color.r, 255);
	assert_int_equal(scene->surfaces[0].obj.color.g, 0);
	assert_int_equal(scene->surfaces[0].obj.color.b, 0);

	free(arr);
	free_scene(scene);
}

void	test_parse_hyperboloid_negative_coordinates(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("hy", "-25,-50,-75", "0.0,1.0,0.0", "50,50,50");

	parse_plane(arr, scene);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.x + 25.0) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.y + 50.0) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.z + 75.0) < 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_hyperboloid_diagonal_orientation(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("hy", "0,0,0", "-1.0,-1.0,-1.0", "200,100,150");

	parse_plane(arr, scene);
	assert_int_equal(scene->surfaces[0].type, HYPERBOLOID);

	free(arr);
	free_scene(scene);
}

void	test_parse_hyperboloid_unbounded(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("hy", "0,0,0", "0.0,1.0,0.0", "255,255,255");

	parse_plane(arr, scene);
	/* Hyperboloids are unbounded like planes */
	assert_int_equal(scene->surfaces[0].is_bounded, 0);

	free(arr);
	free_scene(scene);
}

void	test_parse_hyperboloid_multiple_hyperboloids(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr1 = make_arr("hy", "0,0,0", "0.0,1.0,0.0", "255,0,0");
	char	**arr2 = make_arr("hy", "20,20,20", "1.0,0.0,0.0", "0,255,0");

	parse_plane(arr1, scene);
	parse_plane(arr2, scene);

	assert_int_equal(scene->surfaces[0].type, HYPERBOLOID);
	assert_int_equal(scene->surfaces[1].type, HYPERBOLOID);
	assert_int_equal(scene->surfaces[0].obj.color.r, 255);
	assert_int_equal(scene->surfaces[1].obj.color.g, 255);
	assert_int_equal(scene->idx_obj, 2);

	free(arr1);
	free(arr2);
	free_scene(scene);
}

/* ========================================================= */
/* PARSE_PARABOLOID TESTS (uses plane parser logic) */
/* ========================================================= */

void	test_parse_paraboloid_basic(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("pa", "0,0,0", "0.0,1.0,0.0", "255,255,255");

	parse_plane(arr, scene);
	assert_int_equal(scene->surfaces[0].type, PARABOLOID);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.x) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.y) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.z) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.orientation.y - 1.0) < 0.0001);
	assert_int_equal(scene->surfaces[0].obj.color.r, 255);
	assert_int_equal(scene->surfaces[0].obj.color.g, 255);
	assert_int_equal(scene->surfaces[0].obj.color.b, 255);
	assert_int_equal(scene->idx_obj, 1);

	free(arr);
	free_scene(scene);
}

void	test_parse_paraboloid_offset_position(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("pa", "3.2,7.1,-9.4", "0.0,1.0,0.0", "50,100,200");

	parse_plane(arr, scene);
	assert_int_equal(scene->surfaces[0].type, PARABOLOID);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.x - 3.2) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.y - 7.1) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.z + 9.4) < 0.0001);
	assert_int_equal(scene->surfaces[0].obj.color.r, 50);
	assert_int_equal(scene->surfaces[0].obj.color.g, 100);
	assert_int_equal(scene->surfaces[0].obj.color.b, 200);

	free(arr);
	free_scene(scene);
}

void	test_parse_paraboloid_different_orientations(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("pa", "0,0,0", "1.0,0.0,0.0", "128,64,32");

	parse_plane(arr, scene);
	assert_true(fabs(scene->surfaces[0].obj.orientation.x - 1.0) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.orientation.y) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.orientation.z) < 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_paraboloid_green_color(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("pa", "0,0,0", "0.0,1.0,0.0", "0,255,0");

	parse_plane(arr, scene);
	assert_int_equal(scene->surfaces[0].obj.color.r, 0);
	assert_int_equal(scene->surfaces[0].obj.color.g, 255);
	assert_int_equal(scene->surfaces[0].obj.color.b, 0);

	free(arr);
	free_scene(scene);
}

void	test_parse_paraboloid_negative_coordinates(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("pa", "-100,-200,-300", "0.0,1.0,0.0", "200,200,200");

	parse_plane(arr, scene);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.x + 100.0) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.y + 200.0) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.coordinate.z + 300.0) < 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_paraboloid_z_axis_orientation(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("pa", "0,0,0", "0.0,0.0,1.0", "100,150,200");

	parse_plane(arr, scene);
	assert_true(fabs(scene->surfaces[0].obj.orientation.z - 1.0) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.orientation.x) < 0.0001);
	assert_true(fabs(scene->surfaces[0].obj.orientation.y) < 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_paraboloid_unbounded(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("pa", "0,0,0", "0.0,1.0,0.0", "255,255,255");

	parse_plane(arr, scene);
	/* Paraboloids are unbounded like planes */
	assert_int_equal(scene->surfaces[0].is_bounded, 0);

	free(arr);
	free_scene(scene);
}

void	test_parse_paraboloid_multiple_paraboloids(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr1 = make_arr("pa", "0,0,0", "0.0,1.0,0.0", "255,0,0");
	char	**arr2 = make_arr("pa", "15,15,15", "0.0,0.0,1.0", "0,0,255");

	parse_plane(arr1, scene);
	parse_plane(arr2, scene);

	assert_int_equal(scene->surfaces[0].type, PARABOLOID);
	assert_int_equal(scene->surfaces[1].type, PARABOLOID);
	assert_int_equal(scene->surfaces[0].obj.color.r, 255);
	assert_int_equal(scene->surfaces[1].obj.color.b, 255);
	assert_int_equal(scene->idx_obj, 2);

	free(arr1);
	free(arr2);
	free_scene(scene);
}

void	test_parse_paraboloid_blue_color(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("pa", "0,0,0", "0.0,1.0,0.0", "0,0,255");

	parse_plane(arr, scene);
	assert_int_equal(scene->surfaces[0].obj.color.r, 0);
	assert_int_equal(scene->surfaces[0].obj.color.g, 0);
	assert_int_equal(scene->surfaces[0].obj.color.b, 255);

	free(arr);
	free_scene(scene);
}

/* ========================================================= */
/* MIXED BONUS OBJECTS TESTS */
/* ========================================================= */

void	test_parse_mixed_bonus_objects(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr_cone = make_arr("co", "0,0,0", "2.0", "255,0,0");
	char	**arr_hy = make_arr("hy", "10,10,10", "0.0,1.0,0.0", "0,255,0");
	char	**arr_pa = make_arr("pa", "20,20,20", "0.0,1.0,0.0", "0,0,255");

	parse_sphere(arr_cone, scene);
	parse_plane(arr_hy, scene);
	parse_plane(arr_pa, scene);

	assert_int_equal(scene->surfaces[0].type, CONE);
	assert_int_equal(scene->surfaces[1].type, HYPERBOLOID);
	assert_int_equal(scene->surfaces[2].type, PARABOLOID);
	assert_int_equal(scene->idx_obj, 3);
	assert_int_equal(scene->surfaces[0].obj.color.r, 255);
	assert_int_equal(scene->surfaces[1].obj.color.g, 255);
	assert_int_equal(scene->surfaces[2].obj.color.b, 255);

	free(arr_cone);
	free(arr_hy);
	free(arr_pa);
	free_scene(scene);
}

void	test_parse_bonus_objects_color_variation(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr1 = make_arr("co", "0,0,0", "2.0", "100,100,100");
	char	**arr2 = make_arr("hy", "5,5,5", "0.0,1.0,0.0", "150,150,150");
	char	**arr3 = make_arr("pa", "10,10,10", "0.0,1.0,0.0", "200,200,200");

	parse_sphere(arr1, scene);
	parse_plane(arr2, scene);
	parse_plane(arr3, scene);

	assert_int_equal(scene->surfaces[0].obj.color.r, 100);
	assert_int_equal(scene->surfaces[1].obj.color.g, 150);
	assert_int_equal(scene->surfaces[2].obj.color.b, 200);

	free(arr1);
	free(arr2);
	free(arr3);
	free_scene(scene);
}
