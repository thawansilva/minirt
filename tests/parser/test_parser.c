/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 10:00:00 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/21 10:00:00 by thaperei         ###   ########.fr       */
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

#include "parser.h"
#include "objects.h"
#include "scene.h"
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
/* SAVE_COLOR TESTS */
/* ========================================================= */

void	test_save_color_basic(void **state)
{
	(void)state;
	t_color	color;

	save_color("255,128,64", &color);
	assert_int_equal(color.r, 255);
	assert_int_equal(color.g, 128);
	assert_int_equal(color.b, 64);
}

void	test_save_color_black(void **state)
{
	(void)state;
	t_color	color;

	save_color("0,0,0", &color);
	assert_int_equal(color.r, 0);
	assert_int_equal(color.g, 0);
	assert_int_equal(color.b, 0);
}

void	test_save_color_white(void **state)
{
	(void)state;
	t_color	color;

	save_color("255,255,255", &color);
	assert_int_equal(color.r, 255);
	assert_int_equal(color.g, 255);
	assert_int_equal(color.b, 255);
}

void	test_save_color_red(void **state)
{
	(void)state;
	t_color	color;

	save_color("255,0,0", &color);
	assert_int_equal(color.r, 255);
	assert_int_equal(color.g, 0);
	assert_int_equal(color.b, 0);
}

void	test_save_color_green(void **state)
{
	(void)state;
	t_color	color;

	save_color("0,255,0", &color);
	assert_int_equal(color.r, 0);
	assert_int_equal(color.g, 255);
	assert_int_equal(color.b, 0);
}

void	test_save_color_blue(void **state)
{
	(void)state;
	t_color	color;

	save_color("0,0,255", &color);
	assert_int_equal(color.r, 0);
	assert_int_equal(color.g, 0);
	assert_int_equal(color.b, 255);
}

void	test_save_color_mid_values(void **state)
{
	(void)state;
	t_color	color;

	save_color("128,128,128", &color);
	assert_int_equal(color.r, 128);
	assert_int_equal(color.g, 128);
	assert_int_equal(color.b, 128);
}

/* ========================================================= */
/* SAVE_VEC4 TESTS */
/* ========================================================= */

void	test_save_vec4_basic(void **state)
{
	(void)state;
	t_vec4	vec;

	save_vec4("1.5,2.5,3.5", &vec);
	assert_true(fabs(vec.x - 1.5) < 0.0001);
	assert_true(fabs(vec.y - 2.5) < 0.0001);
	assert_true(fabs(vec.z - 3.5) < 0.0001);
	assert_true(fabs(vec.k - 0.0) < 0.0001);
}

void	test_save_vec4_integers(void **state)
{
	(void)state;
	t_vec4	vec;

	save_vec4("1,2,3", &vec);
	assert_true(fabs(vec.x - 1.0) < 0.0001);
	assert_true(fabs(vec.y - 2.0) < 0.0001);
	assert_true(fabs(vec.z - 3.0) < 0.0001);
	assert_true(fabs(vec.k - 0.0) < 0.0001);
}

void	test_save_vec4_zeros(void **state)
{
	(void)state;
	t_vec4	vec;

	save_vec4("0,0,0", &vec);
	assert_true(fabs(vec.x) < 0.0001);
	assert_true(fabs(vec.y) < 0.0001);
	assert_true(fabs(vec.z) < 0.0001);
	assert_true(fabs(vec.k) < 0.0001);
}

void	test_save_vec4_negative(void **state)
{
	(void)state;
	t_vec4	vec;

	save_vec4("-1.0,-2.0,-3.0", &vec);
	assert_true(fabs(vec.x + 1.0) < 0.0001);
	assert_true(fabs(vec.y + 2.0) < 0.0001);
	assert_true(fabs(vec.z + 3.0) < 0.0001);
	assert_true(fabs(vec.k) < 0.0001);
}

void	test_save_vec4_unit_vector(void **state)
{
	(void)state;
	t_vec4	vec;

	save_vec4("0.0,1.0,0.0", &vec);
	assert_true(fabs(vec.x) < 0.0001);
	assert_true(fabs(vec.y - 1.0) < 0.0001);
	assert_true(fabs(vec.z) < 0.0001);
	assert_true(fabs(vec.k) < 0.0001);
}

void	test_save_vec4_normalized_diagonal(void **state)
{
	(void)state;
	t_vec4	vec;

	save_vec4("0.57735,-0.57735,0.57735", &vec);
	assert_true(fabs(vec.x - 0.57735) < 0.001);
	assert_true(fabs(vec.y + 0.57735) < 0.001);
	assert_true(fabs(vec.z - 0.57735) < 0.001);
	assert_true(fabs(vec.k) < 0.0001);
}

void	test_save_vec4_large_values(void **state)
{
	(void)state;
	t_vec4	vec;

	save_vec4("1000.5,2000.25,-3000.75", &vec);
	assert_true(fabs(vec.x - 1000.5) < 0.0001);
	assert_true(fabs(vec.y - 2000.25) < 0.0001);
	assert_true(fabs(vec.z + 3000.75) < 0.0001);
	assert_true(fabs(vec.k) < 0.0001);
}

/* ========================================================= */
/* PARSE_AMBIENT TESTS */
/* ========================================================= */

void	test_parse_ambient_basic(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("A", "0.5", "255,255,255", NULL);

	parse_ambient(arr, scene);
	assert_true(fabs(scene->ambient.lightness - 0.5) < 0.0001);
	assert_int_equal(scene->ambient.color.r, 255);
	assert_int_equal(scene->ambient.color.g, 255);
	assert_int_equal(scene->ambient.color.b, 255);

	free(arr);
	free_scene(scene);
}

void	test_parse_ambient_zero_lightness(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("A", "0.0", "0,0,0", NULL);

	parse_ambient(arr, scene);
	assert_true(fabs(scene->ambient.lightness) < 0.0001);
	assert_int_equal(scene->ambient.color.r, 0);
	assert_int_equal(scene->ambient.color.g, 0);
	assert_int_equal(scene->ambient.color.b, 0);

	free(arr);
	free_scene(scene);
}

void	test_parse_ambient_full_lightness(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("A", "1.0", "128,64,32", NULL);

	parse_ambient(arr, scene);
	assert_true(fabs(scene->ambient.lightness - 1.0) < 0.0001);
	assert_int_equal(scene->ambient.color.r, 128);
	assert_int_equal(scene->ambient.color.g, 64);
	assert_int_equal(scene->ambient.color.b, 32);

	free(arr);
	free_scene(scene);
}

void	test_parse_ambient_mid_values(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("A", "0.75", "192,192,192", NULL);

	parse_ambient(arr, scene);
	assert_true(fabs(scene->ambient.lightness - 0.75) < 0.0001);
	assert_int_equal(scene->ambient.color.r, 192);
	assert_int_equal(scene->ambient.color.g, 192);
	assert_int_equal(scene->ambient.color.b, 192);

	free(arr);
	free_scene(scene);
}

void	test_parse_ambient_different_colors(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("A", "0.3", "50,100,150", NULL);

	parse_ambient(arr, scene);
	assert_true(fabs(scene->ambient.lightness - 0.3) < 0.0001);
	assert_int_equal(scene->ambient.color.r, 50);
	assert_int_equal(scene->ambient.color.g, 100);
	assert_int_equal(scene->ambient.color.b, 150);

	free(arr);
	free_scene(scene);
}

/* ========================================================= */
/* PARSE_CAMERA TESTS */
/* ========================================================= */

void	test_parse_camera_basic(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("C", "0,0,0", "0.0,1.0,0.0", "90", NULL);

	parse_camera(arr, scene);
	assert_true(fabs(scene->camera.coordinate.x) < 0.0001);
	assert_true(fabs(scene->camera.coordinate.y) < 0.0001);
	assert_true(fabs(scene->camera.coordinate.z) < 0.0001);
	assert_true(fabs(scene->camera.norm_vector.y - 1.0) < 0.0001);
	assert_int_equal(scene->camera.fov, 90);

	free(arr);
	free_scene(scene);
}

void	test_parse_camera_different_position(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("C", "10.5,20.3,-15.7", "0.0,1.0,0.0",
		"45", NULL);

	parse_camera(arr, scene);
	assert_true(fabs(scene->camera.coordinate.x - 10.5) < 0.0001);
	assert_true(fabs(scene->camera.coordinate.y - 20.3) < 0.0001);
	assert_true(fabs(scene->camera.coordinate.z + 15.7) < 0.0001);
	assert_true(fabs(scene->camera.norm_vector.y - 1.0) < 0.0001);
	assert_int_equal(scene->camera.fov, 45);

	free(arr);
	free_scene(scene);
}

void	test_parse_camera_different_direction(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("C", "0,0,0", "-1.0,0.0,1.0", "60", NULL);

	parse_camera(arr, scene);
	assert_true(fabs(scene->camera.coordinate.x) < 0.0001);
	assert_true(fabs(scene->camera.coordinate.y) < 0.0001);
	assert_true(fabs(scene->camera.coordinate.z) < 0.0001);
	assert_true(fabs(scene->camera.norm_vector.x + 1.0) < 0.0001);
	assert_true(fabs(scene->camera.norm_vector.z - 1.0) < 0.0001);
	assert_int_equal(scene->camera.fov, 60);

	free(arr);
	free_scene(scene);
}

void	test_parse_camera_min_fov(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("C", "0,0,0", "0.0,1.0,0.0", "0", NULL);

	parse_camera(arr, scene);
	assert_int_equal(scene->camera.fov, 0);

	free(arr);
	free_scene(scene);
}

void	test_parse_camera_max_fov(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("C", "0,0,0", "0.0,1.0,0.0", "180", NULL);

	parse_camera(arr, scene);
	assert_int_equal(scene->camera.fov, 180);

	free(arr);
	free_scene(scene);
}

void	test_parse_camera_negative_coordinates(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("C", "-100,-200,-300", "0.0,1.0,0.0", "120",
		NULL);

	parse_camera(arr, scene);
	assert_true(fabs(scene->camera.coordinate.x + 100.0) < 0.0001);
	assert_true(fabs(scene->camera.coordinate.y + 200.0) < 0.0001);
	assert_true(fabs(scene->camera.coordinate.z + 300.0) < 0.0001);

	free(arr);
	free_scene(scene);
}

/* ========================================================= */
/* PARSE_LIGHT TESTS */
/* ========================================================= */

void	test_parse_light_basic(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("L", "0,0,0", "0.5", "255,255,255", NULL);

	parse_light(arr, scene);
	assert_true(fabs(scene->light->coordinate.x) < 0.0001);
	assert_true(fabs(scene->light->coordinate.y) < 0.0001);
	assert_true(fabs(scene->light->coordinate.z) < 0.0001);
	assert_true(fabs(scene->light->brightness - 0.5) < 0.0001);
	assert_int_equal(scene->light->color.r, 255);
	assert_int_equal(scene->light->color.g, 255);
	assert_int_equal(scene->light->color.b, 255);

	free(arr);
	free_scene(scene);
}

void	test_parse_light_different_position(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("L", "10.5,20.0,-5.5", "0.8", "200,200,200",
		NULL);

	parse_light(arr, scene);
	assert_true(fabs(scene->light->coordinate.x - 10.5) < 0.0001);
	assert_true(fabs(scene->light->coordinate.y - 20.0) < 0.0001);
	assert_true(fabs(scene->light->coordinate.z + 5.5) < 0.0001);
	assert_true(fabs(scene->light->brightness - 0.8) < 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_light_zero_brightness(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("L", "0,0,0", "0.0", "100,100,100", NULL);

	parse_light(arr, scene);
	assert_true(fabs(scene->light->brightness) < 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_light_full_brightness(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("L", "0,0,0", "1.0", "255,255,255", NULL);

	parse_light(arr, scene);
	assert_true(fabs(scene->light->brightness - 1.0) < 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_light_different_color(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("L", "5,10,15", "0.6", "100,150,200", NULL);

	parse_light(arr, scene);
	assert_true(fabs(scene->light->coordinate.x - 5.0) < 0.0001);
	assert_true(fabs(scene->light->coordinate.y - 10.0) < 0.0001);
	assert_true(fabs(scene->light->coordinate.z - 15.0) < 0.0001);
	assert_true(fabs(scene->light->brightness - 0.6) < 0.0001);
	assert_int_equal(scene->light->color.r, 100);
	assert_int_equal(scene->light->color.g, 150);
	assert_int_equal(scene->light->color.b, 200);

	free(arr);
	free_scene(scene);
}

void	test_parse_light_negative_coordinates(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("L", "-50,-100,50", "0.9", "50,50,50", NULL);

	parse_light(arr, scene);
	assert_true(fabs(scene->light->coordinate.x + 50.0) < 0.0001);
	assert_true(fabs(scene->light->coordinate.y + 100.0) < 0.0001);
	assert_true(fabs(scene->light->coordinate.z - 50.0) < 0.0001);
	assert_true(fabs(scene->light->brightness - 0.9) < 0.0001);
	assert_int_equal(scene->light->color.r, 50);
	assert_int_equal(scene->light->color.g, 50);
	assert_int_equal(scene->light->color.b, 50);

	free(arr);
	free_scene(scene);
}

/* ========================================================= */
/* PARSE_SPHERE TESTS */
/* ========================================================= */

void	test_parse_sphere_basic(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("sp", "0,0,0", "2.0", "255,255,255");

	parse_sphere(arr, scene);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.x)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.y)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.z)
		< 0.0001);
	assert_int_equal(scene->surfaces[scene->num_objs].type, SPHERE);

	free(arr);
	free_scene(scene);
}

void	test_parse_sphere_different_position(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("sp", "10.5,20.3,-15.7", "5.0", "100,150,200");

	parse_sphere(arr, scene);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.x - 10.5)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.y - 20.3)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.z + 15.7)
		< 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_sphere_different_diameter(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("sp", "10.5,20.3,-15.7", "10.5", "50,100,150");

	parse_sphere(arr, scene);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.x - 10.5)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.y - 20.3)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.z + 15.7)
		< 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_sphere_red_color(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("sp", "5.5,10.0,-20.3", "2.0", "255,0,0");

	parse_sphere(arr, scene);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.x - 5.5)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.y - 10.0)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.z + 20.3)
		< 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_sphere_not_bounded(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("sp", "0,0,0", "2.0", "255,255,255");

	parse_sphere(arr, scene);
	assert_int_equal(scene->surfaces[scene->num_objs].is_bounded, 0);

	free(arr);
	free_scene(scene);
}

void	test_parse_sphere_large_diameter(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("sp", "0,0,0", "1000.5", "128,128,128");

	parse_sphere(arr, scene);
	assert_int_equal(scene->surfaces[scene->num_objs].type, SPHERE);
	assert_int_equal(scene->surfaces[scene->num_objs].is_bounded, 0);

	free(arr);
	free_scene(scene);
}

void	test_parse_sphere_small_diameter(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr("sp", "0,0,0", "0.001", "64,64,64");

	parse_sphere(arr, scene);
	assert_int_equal(scene->surfaces[scene->num_objs].type, SPHERE);
	assert_int_equal(scene->surfaces[scene->num_objs].is_bounded, 0);

	free(arr);
	free_scene(scene);
}

/* ========================================================= */
/* PARSE_PLANE TESTS */
/* ========================================================= */

void	test_parse_plane_basic(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("pl", "0,0,0", "0.0,1.0,0.0", "255,255,255",
		NULL);

	parse_plane(arr, scene);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.x)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.y)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.z)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.orientation.y - 1.0)
		< 0.0001);
	assert_int_equal(scene->surfaces[scene->num_objs].type, PLANE);

	free(arr);
	free_scene(scene);
}

void	test_parse_plane_different_position(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("pl", "5.5,10.0,-20.3", "0.0,1.0,0.0",
		"100,100,100", NULL);

	parse_plane(arr, scene);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.x - 5.5)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.y - 10.0)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.z + 20.3)
		< 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_plane_different_orientation(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("pl", "0,0,0", "1.0,0.0,0.0", "200,200,200",
		NULL);

	parse_plane(arr, scene);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.orientation.x - 1.0)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.orientation.y)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.orientation.z)
		< 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_plane_diagonal_orientation(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("pl", "0,0,0", "-1.0,-1.0,-1.0", "128,128,128",
		NULL);

	parse_plane(arr, scene);
	assert_int_equal(scene->surfaces[scene->num_objs].type, PLANE);
	assert_int_equal(scene->surfaces[scene->num_objs].is_bounded, 0);

	free(arr);
	free_scene(scene);
}

void	test_parse_plane_red_color(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("pl", "0,0,0", "0.0,1.0,0.0", "255,0,0", NULL);

	parse_plane(arr, scene);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.orientation.y - 1.0)
		< 0.0001);
	assert_int_equal(scene->surfaces[scene->num_objs].type, PLANE);

	free(arr);
	free_scene(scene);
}

void	test_parse_plane_not_bounded(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("pl", "0,0,0", "0.0,1.0,0.0", "255,255,255",
		NULL);

	parse_plane(arr, scene);
	assert_int_equal(scene->surfaces[scene->num_objs].is_bounded, 0);

	free(arr);
	free_scene(scene);
}

void	test_parse_plane_negative_coordinates(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_5("pl", "-100,-200,-300", "0.0,1.0,0.0",
		"50,100,150", NULL);

	parse_plane(arr, scene);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.x + 100.0)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.y + 200.0)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.z + 300.0)
		< 0.0001);

	free(arr);
	free_scene(scene);
}

/* ========================================================= */
/* PARSE_CYLINDER TESTS */
/* ========================================================= */

void	test_parse_cylinder_basic(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_6("cy", "0,0,0", "0.0,1.0,0.0", "2.5", "5.0",
		"255,255,255");

	parse_cylinder(arr, scene);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.x)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.y)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.z)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.orientation.y - 1.0)
		< 0.0001);
	assert_int_equal(scene->surfaces[scene->num_objs].type, CYLINDER);

	free(arr);
	free_scene(scene);
}

void	test_parse_cylinder_different_position(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_6("cy", "10.5,20.0,-15.3", "0.0,1.0,0.0", "3.0",
		"10.0", "100,150,200");

	parse_cylinder(arr, scene);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.x - 10.5)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.y - 20.0)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.z + 15.3)
		< 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_cylinder_different_orientation(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_6("cy", "0,0,0", "1.0,0.0,0.0", "2.0", "8.0",
		"200,100,50");

	parse_cylinder(arr, scene);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.orientation.x - 1.0)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.orientation.y)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.orientation.z)
		< 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_cylinder_large_dimensions(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_6("cy", "0,0,0", "0.0,1.0,0.0", "50.5", "100.25",
		"128,128,128");

	parse_cylinder(arr, scene);
	assert_int_equal(scene->surfaces[scene->num_objs].type, CYLINDER);
	/* min and max are calculated from height by create_surface */
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.min + 50.125)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.max - 50.125)
		< 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_cylinder_small_dimensions(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_6("cy", "0,0,0", "0.0,1.0,0.0", "0.1", "0.5",
		"64,64,64");

	parse_cylinder(arr, scene);
	assert_int_equal(scene->surfaces[scene->num_objs].type, CYLINDER);
	/* min and max are calculated from height by create_surface: -height/2 and +height/2 */
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.min + 0.25)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.max - 0.25)
		< 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_cylinder_diagonal_orientation(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_6("cy", "0,0,0", "-1.0,-1.0,-1.0", "2.0", "5.0",
		"200,100,150");

	parse_cylinder(arr, scene);
	/* Type is set correctly by create_surface */
	assert_int_equal(scene->surfaces[scene->num_objs].type, CYLINDER);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.x)
		< 0.0001);

	free(arr);
	free_scene(scene);
}

void	test_parse_cylinder_is_bounded(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_6("cy", "0,0,0", "0.0,1.0,0.0", "2.0", "5.0",
		"255,255,255");

	parse_cylinder(arr, scene);
	assert_int_equal(scene->surfaces[scene->num_objs].type, CYLINDER);
	/* Verify the cylinder structure was created */
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.orientation.y - 1.0)
		< 0.0001);
	assert_int_equal(scene->surfaces[scene->num_objs].is_bounded, 1);

	free(arr);
	free_scene(scene);
}

void	test_parse_cylinder_red_color(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_6("cy", "10.5,20.3,-15.7", "0.0,1.0,0.0", "2.0",
		"5.0", "255,0,0");

	parse_cylinder(arr, scene);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.x - 10.5)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.y - 20.3)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.z + 15.7)
		< 0.0001);
	assert_int_equal(scene->surfaces[scene->num_objs].is_bounded, 1);
	assert_int_equal(scene->surfaces[scene->num_objs].obj.color.r, 255);
	assert_int_equal(scene->surfaces[scene->num_objs].obj.color.g, 0);
	assert_int_equal(scene->surfaces[scene->num_objs].obj.color.b, 0);

	free(arr);
	free_scene(scene);
}

void	test_parse_cylinder_negative_coordinates(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	**arr = make_arr_6("cy", "-50,-100,-150", "0.0,1.0,0.0", "5.0",
		"20.0", "75,75,75");

	parse_cylinder(arr, scene);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.x + 50.0)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.y + 100.0)
		< 0.0001);
	assert_true(fabs(scene->surfaces[scene->num_objs].obj.coordinate.z + 150.0)
		< 0.0001);
	assert_int_equal(scene->surfaces[scene->num_objs].is_bounded, 1);
	assert_int_equal(scene->surfaces[scene->num_objs].obj.color.r, 75);
	assert_int_equal(scene->surfaces[scene->num_objs].obj.color.g, 75);
	assert_int_equal(scene->surfaces[scene->num_objs].obj.color.b, 75);

	free(arr);
	free_scene(scene);
}
