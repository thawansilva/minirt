/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 08:54:51 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/22 20:30:26 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>

#include "validation.h"
#include "libft.h"

// HELPERS FUNCTIONS

void	free_node(void *line)
{
	free(line);
}

/* Writes content to a temporary .rt file and returns the path.
   Caller must free the returned string and unlink the file. */
static char	*make_rt_file(const char *content)
{
	char	*path;
	FILE	*f;

	path = strdup("/tmp/test_XXXXXX.rt");
	/* mkstemps would be ideal but for simplicity use a fixed name per test.
	   Each test uses a unique name to avoid collisions. */
	f = fopen(path, "w");
	if (!f)
		return (NULL);
	fputs(content, f);
	fclose(f);
	return (path);
}

static t_scene	*make_scene(void)
{
	t_scene	*scene;

	scene = calloc(1, sizeof(t_scene));
	return (scene);
}

static void	free_scene(t_scene *scene)
{
	t_list	*node;
	t_list	*next;

	node = scene->objs;
	while (node)
	{
		next = node->next;
		free(node->content);
		free(node);
		node = next;
	}
	free(scene);
}

/* EXTENSION VALIDATION TESTS */
void test_valid_extension(void **state)
{
	(void)state;
	assert_true(is_valid_extension("scene.rt"));
	assert_true(is_valid_extension("test_file.rt"));
}

void test_invalid_extension(void **state)
{
	(void)state;
	assert_false(is_valid_extension("scene.txt"));
	assert_false(is_valid_extension("scene.rt.bak"));
	assert_false(is_valid_extension(".rt"));
	assert_false(is_valid_extension("scene"));
	assert_false(is_valid_extension(NULL));
}

/* TOKENIZER / SPLIT BEHAVIOR TESTS */

void test_split_spaces(void **state)
{
	(void)state;

	char **tokens = ft_split_charset("  A \t\t\t 0.2\t255,255,255  ", " \t");

	assert_non_null(tokens);
	assert_string_equal(tokens[0], "A");
	assert_string_equal(tokens[1], "0.2");
	assert_string_equal(tokens[2], "255,255,255");
	for (int i = 0; i < 3; ++i)
		free(tokens[i]);
	free(tokens);
}

/* READ FILE VALIDATION TESTS */

void test_read_file_valid(void **state)
{
	(void) state;

	const char *filename = "test_valid.txt";
	FILE *f = fopen(filename, "w");
	assert_non_null(f);

	fprintf(f, "line1\nline2\nline3\n");
	fclose(f);

	t_scene scene;
	scene.objs = NULL;

	read_file((char *)filename, &scene);

	assert_non_null(scene.objs);
	assert_int_equal(ft_lstsize(scene.objs), 3);

	ft_lstclear(&(scene.objs), &free_node);
	remove(filename);
}

void test_read_file_invalid(void **state)
{
	(void) state;

	t_scene scene;
	scene.objs = NULL;

	read_file("non_existent_file.txt", &scene);
	assert_null(scene.objs);
}

void test_read_file_empty(void **state)
{
	(void) state;

	const char *filename = "test_empty.txt";
	FILE *f = fopen(filename, "w");
	assert_non_null(f);
	fclose(f);

	t_scene scene;
	scene.objs = NULL;

	read_file((char *)filename, &scene);

	assert_null(scene.objs);

	remove(filename);
}

void test_read_invalid_file(void **state)
{
	(void)state;

	t_scene scene;
	scene.objs = NULL;
	read_file("nonexistent", &scene);
	assert_null(scene.objs);
	ft_lstclear(&(scene.objs), &free_node);
}


/* VALIDATE FLOAT STRING  */

void    test_valid_float_integer(void **state)
{
    (void)state;
    assert_int_equal(is_valid_float("42"), 1);
}

void    test_valid_float_positive(void **state)
{
    (void)state;
    assert_int_equal(is_valid_float("3.14"), 1);
}

void    test_valid_float_negative(void **state)
{
    (void)state;
    assert_int_equal(is_valid_float("-1.5"), 1);
}

void    test_valid_float_explicit_plus(void **state)
{
    (void)state;
    assert_int_equal(is_valid_float("+1.5"), 1);
}

void    test_valid_float_leading_dot(void **state)
{
    (void)state;
    assert_int_equal(is_valid_float(".5"), 1);
}

void    test_valid_float_trailing_dot(void **state)
{
    (void)state;
    assert_int_equal(is_valid_float("1."), 1);
}

void    test_valid_float_only_dot(void **state)
{
    (void)state;
    assert_int_equal(is_valid_float("."), 0);
}

void    test_valid_float_only_sign(void **state)
{
    (void)state;
    assert_int_equal(is_valid_float("-"), 0);
}

void    test_valid_float_empty(void **state)
{
    (void)state;
    assert_int_equal(is_valid_float(""), 0);
}

void    test_valid_float_non_numeric(void **state)
{
    (void)state;
    assert_int_equal(is_valid_float("abc"), 0);
}

void    test_valid_float_spaces(void **state)
{
    (void)state;
    assert_int_equal(is_valid_float("1 .5"), 0);
}

void    test_valid_float_multiple_dots(void **state)
{
    (void)state;
    assert_int_equal(is_valid_float("1.2.3"), 0);
}

/* VALIDATE INT STRING  */

void    test_valid_int_positive(void **state)
{
    (void)state;
    assert_int_equal(is_valid_int("42"), 1);
}

void    test_valid_int_zero(void **state)
{
    (void)state;
    assert_int_equal(is_valid_int("0"), 1);
}

void    test_valid_int_null(void **state)
{
    (void)state;
    assert_int_equal(is_valid_int(NULL), 0);
}

void    test_valid_int_empty(void **state)
{
    (void)state;
    assert_int_equal(is_valid_int(""), 0);
}

void    test_valid_int_negative(void **state)
{
    (void)state;
    assert_int_equal(is_valid_int("-1"), 0);
}

void    test_valid_int_explicit_plus(void **state)
{
    (void)state;
    assert_int_equal(is_valid_int("+1"), 0);
}

void    test_valid_int_with_newline(void **state)
{
    (void)state;
    assert_int_equal(is_valid_int("42\n"), 1);
}

void    test_valid_int_non_numeric(void **state)
{
    (void)state;
    assert_int_equal(is_valid_int("abc"), 0);
}

void    test_valid_int_float(void **state)
{
    (void)state;
    assert_int_equal(is_valid_int("3.14"), 0);
}

void    test_valid_int_leading_zeros(void **state)
{
    (void)state;
    assert_int_equal(is_valid_int("007"), 1);
}

void    test_valid_int_max_int(void **state)
{
    (void)state;
    assert_int_equal(is_valid_int("2147483647"), 1);
}

void    test_valid_int_alphanumeric(void **state)
{
    (void)state;
    assert_int_equal(is_valid_int("42abc"), 0);
}

void    test_valid_int_only_newline_after_digits(void **state)
{
    (void)state;
    assert_int_equal(is_valid_int("1234\n"), 1);
}

/* VALIDATE RATIO NUMBER  */

void    test_valid_ratio_zero(void **state)
{
	(void)state;
	assert_int_equal(is_valid_ratio("0.0"), 1);
}

void    test_valid_ratio_one(void **state)
{
	(void)state;
	assert_int_equal(is_valid_ratio("1.0"), 1);
}

void    test_valid_ratio_mid(void **state)
{
	(void)state;
	assert_int_equal(is_valid_ratio("0.5"), 1);
}

void    test_valid_ratio_negative(void **state)
{
	(void)state;
	assert_int_equal(is_valid_ratio("-0.1"), 0);
}

void    test_valid_ratio_above_one(void **state)
{
	(void)state;
	assert_int_equal(is_valid_ratio("1.1"), 0);
}

void    test_valid_ratio_null(void **state)
{
	(void)state;
	assert_int_equal(is_valid_ratio(NULL), 0);
}

void    test_valid_ratio_non_numeric(void **state)
{
	(void)state;
	assert_int_equal(is_valid_ratio("abc"), 0);
}

void    test_valid_ratio_empty_string(void **state)
{
	(void)state;
	assert_int_equal(is_valid_ratio(""), 0);
}

/* COLOR VALIDATION TESTS */

void    test_valid_color_valid(void **state)
{
	(void)state;
	assert_int_equal(is_valid_color("0,128,255"), 1);
}

void    test_valid_color_null(void **state)
{
	(void)state;
	assert_int_equal(is_valid_color(NULL), 0);
}

void    test_valid_color_too_few_components(void **state)
{
	(void)state;
	assert_int_equal(is_valid_color("0,128"), 0);
}

void    test_valid_color_too_many_components(void **state)
{
	(void)state;
	assert_int_equal(is_valid_color("0,128,255,64"), 0);
}

void    test_valid_color_out_of_range_high(void **state)
{
	(void)state;
	assert_int_equal(is_valid_color("256,0,0"), 0);
}

void    test_valid_color_out_of_range_low(void **state)
{
	(void)state;
	assert_int_equal(is_valid_color("-1,0,0"), 0);
}

void    test_valid_color_boundary_zero(void **state)
{
	(void)state;
	assert_int_equal(is_valid_color("0,0,0"), 1);
}

void    test_valid_color_boundary_max(void **state)
{
	(void)state;
	assert_int_equal(is_valid_color("255,255,255"), 1);
}

void    test_valid_color_non_numeric(void **state)
{
	(void)state;
	assert_int_equal(is_valid_color("128abc,128,255"), 0);
}

void    test_valid_color_empty_string(void **state)
{
	(void)state;
	assert_int_equal(is_valid_color(""), 0);
}

/* COORDINATES VALIDATION TESTS */

void    test_valid_coordinates_valid(void **state)
{
	(void)state;
	assert_int_equal(is_valid_coordinates("0.0,128.0,255.0"), 1);
}

void    test_valid_coordinates_valid_int_values(void **state)
{
	(void)state;
	assert_int_equal(is_valid_coordinates("0,128,255"), 1);
}

void    test_valid_coordinates_null(void **state)
{
	(void)state;
	assert_int_equal(is_valid_coordinates(NULL), 0);
}

void    test_valid_coordinates_too_few(void **state)
{
	(void)state;
	assert_int_equal(is_valid_coordinates("0,128"), 0);
}

void    test_valid_coordinates_too_many(void **state)
{
	(void)state;
	assert_int_equal(is_valid_coordinates("0,128,255,64"), 0);
}

void    test_valid_coordinates_negative(void **state)
{
	(void)state;
	assert_int_equal(is_valid_coordinates("-1,0,0.0"), 1);
}

void    test_valid_coordinates_without_decimal(void **state)
{
	(void)state;
	assert_int_equal(is_valid_coordinates("-1,0,0.,1.0"), 0);
}

void    test_valid_coordinates_decimal(void **state)
{
	(void)state;
	assert_int_equal(is_valid_coordinates("1.5,0.0,3.7"), 1);
}

void    test_valid_coordinates_non_numeric(void **state)
{
	(void)state;
	assert_int_equal(is_valid_coordinates("abc,def,ghi"), 0);
}

void    test_valid_coordinates_numeric_with_non_numeric(void **state)
{
	(void)state;
	assert_int_equal(is_valid_coordinates("2.0abc,-3.0def,0ghi"), 0);
}

void    test_valid_coordinates_empty_string(void **state)
{
	(void)state;
	assert_int_equal(is_valid_coordinates(""), 0);
}

/* ---------- NORMAL VECTOR ---------- */

void    test_valid_normalized_vector_valid(void **state)
{
    (void)state;
    assert_int_equal(is_valid_normalized_vector("0.0,1.0,0.0"), 1);
}

void    test_valid_normalized_vector_null(void **state)
{
    (void)state;
    assert_int_equal(is_valid_normalized_vector(NULL), 0);
}

void    test_valid_normalized_vector_empty(void **state)
{
    (void)state;
    assert_int_equal(is_valid_normalized_vector(""), 0);
}

void    test_valid_normalized_vector_too_few(void **state)
{
    (void)state;
    assert_int_equal(is_valid_normalized_vector("0.0,1.0"), 0);
}

void    test_valid_normalized_vector_too_many(void **state)
{
    (void)state;
    assert_int_equal(is_valid_normalized_vector("0.0,1.0,0.0,0.5"), 0);
}

void    test_valid_normalized_vector_out_of_range(void **state)
{
    (void)state;
    assert_int_equal(is_valid_normalized_vector("0.0,1.5,0.0"), 0);
}

void    test_valid_normalized_vector_boundary_min(void **state)
{
    (void)state;
    assert_int_equal(is_valid_normalized_vector("-1.0,-1.0,-1.0"), 1);
}

void    test_valid_normalized_vector_boundary_max(void **state)
{
    (void)state;
    assert_int_equal(is_valid_normalized_vector("1.0,1.0,1.0"), 1);
}

void    test_valid_normalized_vector_non_numeric(void **state)
{
    (void)state;
    assert_int_equal(is_valid_normalized_vector("abc,0.0,0.0"), 0);
}

/* ---------- FOV ---------- */

void    test_valid_fov_valid(void **state)
{
    (void)state;
    assert_int_equal(is_valid_fov("90"), 1);
}

void    test_valid_fov_null(void **state)
{
    (void)state;
    assert_int_equal(is_valid_fov(NULL), 0);
}

void    test_valid_fov_empty(void **state)
{
    (void)state;
    assert_int_equal(is_valid_fov(""), 0);
}

void    test_valid_fov_boundary_zero(void **state)
{
    (void)state;
    assert_int_equal(is_valid_fov("0"), 1);
}

void    test_valid_fov_boundary_max(void **state)
{
    (void)state;
    assert_int_equal(is_valid_fov("180"), 1);
}

void    test_valid_fov_out_of_range(void **state)
{
    (void)state;
    assert_int_equal(is_valid_fov("181"), 0);
}

void    test_valid_fov_negative(void **state)
{
    (void)state;
    assert_int_equal(is_valid_fov("-1"), 0);
}

void    test_valid_fov_float(void **state)
{
    (void)state;
    assert_int_equal(is_valid_fov("90.5"), 0);
}

void    test_valid_fov_non_numeric(void **state)
{
    (void)state;
    assert_int_equal(is_valid_fov("abc"), 0);
}

/* ========================================================= */
/* OBJECT PARSING TESTS (DISPATCHER) */
/* ========================================================= */

/* ---------- AMBIENT LIGHT ---------- */

void    test_valid_ambient_valid(void **state)
{
	(void)state;
	char *arr[] = {"A", "0.5", "255,255,255", NULL};
	assert_int_equal(is_valid_ambient(arr), 1);
}

void    test_valid_ambient_null_arr(void **state)
{
	(void)state;

	assert_int_equal(is_valid_ambient(NULL), 0);
}

void    test_valid_ambient_invalid_ratio(void **state)
{
	(void)state;
	char *arr[] = {"A", "1.5", "255,255,255", NULL};
	assert_int_equal(is_valid_ambient(arr), 0);
}

void    test_valid_ambient_invalid_color(void **state)
{
	(void)state;
	char *arr[] = {"A", "0.5", "256,0,0", NULL};
	assert_int_equal(is_valid_ambient(arr), 0);
}

void    test_valid_ambient_both_invalid(void **state)
{
	(void)state;
	char *arr[] = {"A", "2.0", "300,300,300", NULL};
	assert_int_equal(is_valid_ambient(arr), 0);
}

void    test_valid_ambient_boundary_ratio_zero(void **state)
{
	(void)state;
	char *arr[] = {"A", "0.0", "0,0,0", NULL};
	assert_int_equal(is_valid_ambient(arr), 1);
}

void    test_valid_ambient_boundary_ratio_one(void **state)
{
	(void)state;
	char *arr[] = {"A", "1.0", "128,128,128", NULL};
	assert_int_equal(is_valid_ambient(arr), 1);
}

void    test_valid_ambient_boundary_color_max(void **state)
{
	(void)state;
	char *arr[] = {"A", "0.8", "255,255,255", NULL};
	assert_int_equal(is_valid_ambient(arr), 1);
}

//* ---------- CAMERA ---------- */

void    test_valid_camera_valid(void **state)
{
    (void)state;
    char *arr[] = {"C", "0,0,0", "0.0,1.0,0.0", "90", NULL};
    assert_int_equal(is_valid_camera(arr), 1);
}

void    test_valid_camera_null_arr(void **state)
{
    (void)state;
    assert_int_equal(is_valid_camera(NULL), 0);
}

void    test_valid_camera_null_first_element(void **state)
{
    (void)state;
    char *arr[] = {"C", NULL, "0.0,1.0,0.0", "90", NULL};
    assert_int_equal(is_valid_camera(arr), 0);
}

void    test_valid_camera_invalid_coordinates(void **state)
{
    (void)state;
    char *arr[] = {"C", "abc,def,ghi", "0.0,1.0,0.0", "90", NULL};
    assert_int_equal(is_valid_camera(arr), 0);
}

void    test_valid_camera_invalid_vector(void **state)
{
    (void)state;
    char *arr[] = {"C", "0,0,0", "abc,0.0,0.0", "90", NULL};
    assert_int_equal(is_valid_camera(arr), 0);
}

void    test_valid_camera_invalid_fov(void **state)
{
    (void)state;
    char *arr[] = {"C", "0,0,0", "0.0,1.0,0.0", "181", NULL};
    assert_int_equal(is_valid_camera(arr), 0);
}

void    test_valid_camera_all_invalid(void **state)
{
    (void)state;
    char *arr[] = {"C", "abc", "xyz", "999", NULL};
    assert_int_equal(is_valid_camera(arr), 0);
}

void    test_valid_camera_boundary_fov_zero(void **state)
{
    (void)state;
    char *arr[] = {"C", "0,0,0", "0.0,1.0,0.0", "0", NULL};
    assert_int_equal(is_valid_camera(arr), 1);
}

void    test_valid_camera_boundary_fov_max(void **state)
{
    (void)state;
    char *arr[] = {"C", "0,0,0", "0.0,1.0,0.0", "180", NULL};
    assert_int_equal(is_valid_camera(arr), 1);
}

void    test_valid_camera_fov_out_of_range(void **state)
{
    (void)state;
    char *arr[] = {"C", "0,0,0", "0.0,1.0,0.0", "181", NULL};
    assert_int_equal(is_valid_camera(arr), 0);
}

void    test_valid_camera_vector_boundary(void **state)
{
    (void)state;
    char *arr[] = {"C", "0,0,0", "-1.0,0.0,1.0", "90", NULL};
    assert_int_equal(is_valid_camera(arr), 1);
}

void    test_valid_camera_vector_non_numeric(void **state)
{
    (void)state;
    char *arr[] = {"C", "0,0,0", "x,y,z", "90", NULL};
    assert_int_equal(is_valid_camera(arr), 0);
}

void    test_valid_camera_fov_float(void **state)
{
    (void)state;
    char *arr[] = {"C", "0,0,0", "0.0,1.0,0.0", "90.5", NULL};
    assert_int_equal(is_valid_camera(arr), 0);
}

void    test_valid_camera_fov_negative(void **state)
{
    (void)state;
    char *arr[] = {"C", "0,0,0", "0.0,1.0,0.0", "-1", NULL};
    assert_int_equal(is_valid_camera(arr), 0);
}

/* ---------- LIGHT ---------- */

void    test_valid_light_valid(void **state)
{
    (void)state;
    char *arr[] = {"L", "0,0,0", "0.5", "255,255,255", NULL};
    assert_int_equal(is_valid_light(arr), 1);
}

void    test_valid_light_null_arr(void **state)
{
    (void)state;
    assert_int_equal(is_valid_light(NULL), 0);
}

void    test_valid_light_null_first_element(void **state)
{
    (void)state;
    char *arr[] = {"L", NULL, "0,0,0", "0.5", "255,255,255", NULL};
    assert_int_equal(is_valid_light(arr), 0);
}

void    test_valid_light_invalid_coordinates(void **state)
{
    (void)state;
    char *arr[] = {"L", "abc,def,ghi", "0.5", "255,255,255", NULL};
    assert_int_equal(is_valid_light(arr), 0);
}

void    test_valid_light_invalid_ratio(void **state)
{
    (void)state;
    char *arr[] = {"L", "0,0,0", "1.5", "255,255,255", NULL};
    assert_int_equal(is_valid_light(arr), 0);
}

void    test_valid_light_invalid_color(void **state)
{
    (void)state;
    char *arr[] = {"L", "0,0,0", "0.5", "256,0,0", NULL};
    assert_int_equal(is_valid_light(arr), 0);
}

void    test_valid_light_all_invalid(void **state)
{
    (void)state;
    char *arr[] = {"L", "abc", "2.0", "300,300,300", NULL};
    assert_int_equal(is_valid_light(arr), 0);
}

void    test_valid_light_boundary_ratio_zero(void **state)
{
    (void)state;
    char *arr[] = {"L", "0,0,0", "0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_light(arr), 1);
}

void    test_valid_light_boundary_ratio_one(void **state)
{
    (void)state;
    char *arr[] = {"L", "0,0,0", "1.0", "128,128,128", NULL};
    assert_int_equal(is_valid_light(arr), 1);
}

void    test_valid_light_boundary_color_max(void **state)
{
    (void)state;
    char *arr[] = {"L", "0,0,0", "0.8", "255,255,255", NULL};
    assert_int_equal(is_valid_light(arr), 1);
}

void    test_valid_light_ratio_above_one(void **state)
{
    (void)state;
    char *arr[] = {"L", "0,0,0", "1.1", "255,255,255", NULL};
    assert_int_equal(is_valid_light(arr), 0);
}

void    test_valid_light_color_out_of_range(void **state)
{
    (void)state;
    assert_int_equal(is_valid_light((char *[]){"L", "0,0,0", "0.5", "0,256,0", NULL}), 0);
}

void    test_valid_light_coordinates_wrong_count(void **state)
{
    (void)state;
    char *arr[] = {"L", "0,0", "0.5", "255,255,255", NULL};
    assert_int_equal(is_valid_light(arr), 0);
}

void    test_valid_light_null_coordinates(void **state)
{
    (void)state;
    char *arr[] = {"L", NULL, "0.5", "255,255,255", NULL};
    assert_int_equal(is_valid_light(arr), 0);
}

/* ---------- SPHERE ---------- */

void    test_valid_sphere_valid(void **state)
{
    (void)state;
    char *arr[] = {"sp", "0,0,0", "1.5", "255,255,255", NULL};
    assert_int_equal(is_valid_sphere(arr), 1);
}

void    test_valid_sphere_null_arr(void **state)
{
    (void)state;
    assert_int_equal(is_valid_sphere(NULL), 0);
}

void    test_valid_sphere_invalid_coordinates(void **state)
{
    (void)state;
    char *arr[] = {"sp", "abc,def,ghi", "1.5", "255,255,255", NULL};
    assert_int_equal(is_valid_sphere(arr), 0);
}

void    test_valid_sphere_invalid_diameter(void **state)
{
    (void)state;
    char *arr[] = {"sp", "0,0,0", "abc", "255,255,255", NULL};
    assert_int_equal(is_valid_sphere(arr), 0);
}

void    test_valid_sphere_invalid_color(void **state)
{
    (void)state;
    char *arr[] = {"sp", "0,0,0", "1.5", "256,0,0", NULL};
    assert_int_equal(is_valid_sphere(arr), 0);
}

void    test_valid_sphere_all_invalid(void **state)
{
    (void)state;
    char *arr[] = {"sp", "abc", "xyz", "300,300,300", NULL};
    assert_int_equal(is_valid_sphere(arr), 0);
}

void    test_valid_sphere_negative_diameter(void **state)
{
    (void)state;
    char *arr[] = {"sp", "0,0,0", "-1.5", "255,255,255", NULL};
    assert_int_equal(is_valid_sphere(arr), 0);
}

void    test_valid_sphere_zero_diameter(void **state)
{
    (void)state;
    char *arr[] = {"sp", "0,0,0", "0", "255,255,255", NULL};
    assert_int_equal(is_valid_sphere(arr), 1);
}

void    test_valid_sphere_null_coordinates(void **state)
{
    (void)state;
    char *arr[] = {"sp", NULL, "1.5", "255,255,255", NULL};
    assert_int_equal(is_valid_sphere(arr), 0);
}

void    test_valid_sphere_null_color(void **state)
{
    (void)state;
    char *arr[] = {"sp", "0,0,0", "1.5", NULL, NULL};
    assert_int_equal(is_valid_sphere(arr), 0);
}

/* ---------- PLANE ---------- */

void    test_valid_plane_valid(void **state)
{
    (void)state;
    char *arr[] = {"pl", "0,0,0", "0.0,1.0,0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 1);
}

void    test_valid_plane_null_arr(void **state)
{
    (void)state;
    assert_int_equal(is_valid_plane(NULL), 0);
}

void    test_valid_plane_null_first_element(void **state)
{
    (void)state;
    char *arr[] = {"pl", NULL, "0.0,1.0,0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_plane_null_coordinates(void **state)
{
    (void)state;
    char *arr[] = {"pl", NULL, "0.0,1.0,0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_plane_null_vector(void **state)
{
    (void)state;
    char *arr[] = {"pl", "0,0,0", NULL, "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_plane_null_color(void **state)
{
    (void)state;
    char *arr[] = {"pl", "0,0,0", "0.0,1.0,0.0", NULL, NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_plane_invalid_coordinates(void **state)
{
    (void)state;
    char *arr[] = {"pl", "abc,def,ghi", "0.0,1.0,0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_plane_invalid_vector(void **state)
{
    (void)state;
    char *arr[] = {"pl", "0,0,0", "abc,def,ghi", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_plane_invalid_color(void **state)
{
    (void)state;
    char *arr[] = {"pl", "0,0,0", "0.0,1.0,0.0", "256,0,0", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_plane_all_invalid(void **state)
{
    (void)state;
    char *arr[] = {"pl", "abc", "xyz", "300,300,300", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_plane_vector_out_of_range(void **state)
{
    (void)state;
    char *arr[] = {"pl", "0,0,0", "0.0,1.5,0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_plane_vector_boundary_min(void **state)
{
    (void)state;
    char *arr[] = {"pl", "0,0,0", "-1.0,-1.0,-1.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 1);
}

void    test_valid_plane_vector_boundary_max(void **state)
{
    (void)state;
    char *arr[] = {"pl", "0,0,0", "1.0,1.0,1.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 1);
}

void    test_valid_plane_color_boundary_zero(void **state)
{
    (void)state;
    char *arr[] = {"pl", "0,0,0", "0.0,1.0,0.0", "0,0,0", NULL};
    assert_int_equal(is_valid_plane(arr), 1);
}

void    test_valid_plane_color_boundary_max(void **state)
{
    (void)state;
    char *arr[] = {"pl", "0,0,0", "0.0,1.0,0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 1);
}

void    test_valid_plane_coordinates_wrong_count(void **state)
{
    (void)state;
    char *arr[] = {"pl", "0,0", "0.0,1.0,0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_plane_vector_wrong_count(void **state)
{
    (void)state;
    char *arr[] = {"pl", "0,0,0", "0.0,1.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

/* ---------- CYLINDER ---------- */


/* =========================================================
   is_valid_cylinder integration tests

   BUG: color is validated against arr[2] (the vector slot)
   instead of arr[5]. This means:
   - A valid vector that is also a valid color format will pass
   - The actual color at arr[5] is never validated
   - An invalid color at arr[5] will never be caught
   Fix: change `!is_valid_color(arr[2])` to `!is_valid_color(arr[5])`

   Array layout (intended):
     arr[0] = identifier ("cy")
     arr[1] = coordinates
     arr[2] = normalized vector
     arr[3] = diameter
     arr[4] = height
     arr[5] = color
   ========================================================= */

/* Fully valid cylinder — must return 1.
   NOTE: due to the bug, arr[2] ("0.0,1.0,0.0") is passed to
   is_valid_color. ft_split on ',' gives ["0.0","1.0","0.0"],
   all parse to 0 via ft_atoi, all in 0-255 range, count == 3 → passes.
   So valid input coincidentally returns 1 for the wrong reason. */
void    test_valid_cylinder_valid(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "0.0,1.0,0.0", "2.5", "5.0", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 1);
}

void    test_valid_cylinder_null_arr(void **state)
{
    (void)state;
    assert_int_equal(is_valid_cylinder(NULL), 0);
}

void    test_valid_cylinder_null_coordinates(void **state)
{
    (void)state;
    char *arr[] = {"cy", NULL, "0.0,1.0,0.0", "2.5", "5.0", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_null_vector(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", NULL, "2.5", "5.0", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_null_diameter(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "0.0,1.0,0.0", NULL, "5.0", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_null_height(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "0.0,1.0,0.0", "2.5", NULL, "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_null_color(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "0.0,1.0,0.0", "2.5", "5.0", NULL, NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_invalid_coordinates(void **state)
{
    (void)state;
    char *arr[] = {"cy", "abc,def,ghi", "0.0,1.0,0.0", "2.5", "5.0", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_invalid_vector(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "abc,def,ghi", "2.5", "5.0", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_invalid_diameter(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "0.0,1.0,0.0", "abc", "5.0", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_invalid_height(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "0.0,1.0,0.0", "2.5", "abc", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_invalid_color(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "0.0,1.0,0.0", "2.5", "5.0", "256,0,0", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_all_invalid(void **state)
{
    (void)state;
    char *arr[] = {"cy", "abc", "xyz", "???", "???", "300,300,300", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_negative_diameter(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "0.0,1.0,0.0", "-2.5", "5.0", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_zero_diameter(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "0.0,1.0,0.0", "0.0", "5.0", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_negative_height(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "0.0,1.0,0.0", "2.5", "-5.0", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_zero_height(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "0.0,1.0,0.0", "2.5", "0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_boundary_diameter(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "0.0,1.0,0.0", "9999.9", "5.0", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 1);
}

void    test_valid_cylinder_boundary_height(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "0.0,1.0,0.0", "2.5", "9999.9", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 1);
}

void    test_valid_cylinder_vector_out_of_range(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "0.0,1.5,0.0", "2.5", "5.0", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_vector_wrong_count(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "0.0,1.0", "2.5", "5.0", "255,255,255", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

void    test_valid_cylinder_color_wrong_slot(void **state)
{
    (void)state;
    char *arr[] = {"cy", "0,0,0", "255,128,0", "2.5", "5.0", "999,999,999", NULL};
    assert_int_equal(is_valid_cylinder(arr), 0);
}

/* VALIDATE INPUT */

void	test_valid_input_valid_scene(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	*path = strdup("/tmp/valid_scene.rt");
	FILE	*f = fopen(path, "w");
	fputs("A 0.5 255,255,255\n", f);
	fputs("C 0,0,0 0.0,0.0,1.0 90\n", f);
	fputs("L 0,5,0 0.8 255,255,255\n", f);
	fputs("sp 0,0,5 2.0 255,0,0\n", f);
	fclose(f);
	assert_int_equal(is_valid_input(path, scene), 1);
	free_scene(scene);
	unlink(path);
	free(path);
}

void	test_valid_input_valid_scene_with_more_newline(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	char	*path = strdup("/tmp/valid_scene.rt");
	FILE	*f = fopen(path, "w");
	fputs("A 0.5 255,255,255\n", f);
	fputs("C 0,0,0 0.0,0.0,1.0 90\n\n\n", f);
	fputs("L 0,5,0 0.8 255,255,255\n", f);
	fputs("sp 0,0,5 2.0 255,0,0\n", f);
	fclose(f);
	assert_int_equal(is_valid_input(path, scene), 1);
	free_scene(scene);
	unlink(path);
	free(path);
}

void	test_valid_input_null_file(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	assert_int_equal(is_valid_input(NULL, scene), 0);
	free_scene(scene);
}

void	test_valid_input_invalid_extension(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	assert_int_equal(is_valid_input("scene.obj", scene), 0);
	free_scene(scene);
}

void	test_valid_input_no_extension(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	assert_int_equal(is_valid_input("scene", scene), 0);
	free_scene(scene);
}

void	test_valid_input_missing_file(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	assert_int_equal(is_valid_input("/tmp/does_not_exist.rt", scene), 0);
	free_scene(scene);
}

void	test_valid_input_empty_file(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	FILE	*f = fopen("/tmp/empty.rt", "w");
	fclose(f);
	assert_int_equal(is_valid_input("/tmp/empty.rt", scene), 0);
	free_scene(scene);
	unlink("/tmp/empty.rt");
}

void	test_valid_input_missing_camera_and_light(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	FILE	*f = fopen("/tmp/missing_camera_and_light.rt", "w");
	fputs("A 0.5 255,255,255\n", f);
	fputs("sp 0,0,5 2.0 255,0,0\n", f);
	fclose(f);
	assert_int_equal(is_valid_input("/tmp/missing_camera_and_light.rt", scene), 0);
	free_scene(scene);
	unlink("/tmp/missing_camera_and_light.rt");
}

void	test_valid_input_duplicate_ambient(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	FILE	*f = fopen("/tmp/missing_camera_and_light.rt", "w");
	fputs("A 0.5 255,255,255\n", f);
	fputs("A 0.5 255,0,0\n", f);
	fputs("C 0,0,0 0.0,0.0,1.0 90\n", f);
	fputs("L 0,5,0 0.8 255,255,255\n", f);
	fputs("sp 0,0,5 2.0 255,0,0\n", f);
	fclose(f);
	assert_int_equal(is_valid_input("/tmp/missing_camera_and_light.rt", scene), 0);
	free_scene(scene);
	unlink("/tmp/missing_camera_and_light.rt");
}

void	test_valid_input_missing_ambient_and_light(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	FILE	*f = fopen("/tmp/invalid_scene.rt", "w");
	fputs("C 0,0,0 0.0,0.0,1.0 90\n", f);
	fputs("sp 0,0,5 2.0 255,0,0\n", f);
	fclose(f);
	assert_int_equal(is_valid_input("/tmp/invalid_scene.rt", scene), 0);
	free_scene(scene);
	unlink("/tmp/invalid_scene.rt");
}

void	test_valid_input_duplicate_camera(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	FILE	*f = fopen("/tmp/missing_camera_and_light.rt", "w");
	fputs("A 0.5 255,255,255\n", f);
	fputs("C 0,0,0 0.0,0.0,1.0 90\n", f);
	fputs("C 0,0,0 0.0,0.5,1.0 90\n", f);
	fputs("L 0,5,0 0.8 255,255,255\n", f);
	fputs("sp 0,0,5 2.0 255,0,0\n", f);
	fclose(f);
	assert_int_equal(is_valid_input("/tmp/missing_camera_and_light.rt", scene), 0);
	free_scene(scene);
	unlink("/tmp/missing_camera_and_light.rt");
}

void	test_valid_input_missing_ambient_and_camera(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	FILE	*f = fopen("/tmp/invalid_scene.rt", "w");
	fputs("L 0,5,0 0.8 255,255,255\n", f);
	fputs("sp 0,0,5 2.0 255,0,0\n", f);
	fclose(f);
	assert_int_equal(is_valid_input("/tmp/invalid_scene.rt", scene), 0);
	free_scene(scene);
	unlink("/tmp/invalid_scene.rt");
}

void	test_valid_input_duplicate_light(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	FILE	*f = fopen("/tmp/missing_camera_and_light.rt", "w");
	fputs("A 0.5 255,255,255\n", f);
	fputs("C 0,0,0 0.0,0.0,1.0 90\n", f);
	fputs("L 0,3,0 0.8 0,0,255\n", f);
	fputs("L 0,5,0 0.8 255,255,255\n", f);
	fputs("sp 0,0,5 2.0 255,0,0\n", f);
	fclose(f);
	assert_int_equal(is_valid_input("/tmp/missing_camera_and_light.rt", scene), 0);
	free_scene(scene);
	unlink("/tmp/missing_camera_and_light.rt");
}

void	test_valid_input_invalid_ambient(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	FILE	*f = fopen("/tmp/ambient_invalid.rt", "w");
	fputs("A 2.0 255,255,255\n", f);
	fputs("C 0,0,0 0.0,0.0,1.0 90\n", f);
	fputs("L 0,5,0 0.8 255,255,255\n", f);
	fputs("sp 0,0,5 abc 255,0,0\n", f);
	fclose(f);
	assert_int_equal(is_valid_input("/tmp/ambient_invalid.rt", scene), 0);
	free_scene(scene);
	unlink("/tmp/ambient_invalid.rt");
}

void	test_valid_input_valid_sphere(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	FILE	*f = fopen("/tmp/sphere_valid.rt", "w");
	fputs("A 1.0 255,255,255\n", f);
	fputs("C 0,0,0 0.0,0.0,1.0 90\n", f);
	fputs("L 0,5,0 0.8 255,255,255\n", f);
	fputs("sp 0,0,5 2.0 255,0,0\n", f);
	fclose(f);
	assert_int_equal(is_valid_input("/tmp/sphere_valid.rt", scene), 1);
	free_scene(scene);
	unlink("/tmp/sphere_valid.rt");
}

void	test_valid_input_invalid_sphere(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	FILE	*f = fopen("/tmp/sphere_invalid.rt", "w");
	fputs("A 1.0 255,255,255\n", f);
	fputs("C 0,0,0 0.0,0.0,1.0 90\n", f);
	fputs("L 0,5,0 0.8 255,255,255\n", f);
	fputs("sp 0,0,5 abc 255,0,0\n", f);
	fclose(f);
	assert_int_equal(is_valid_input("/tmp/sphere_invalid.rt", scene), 0);
	free_scene(scene);
	unlink("/tmp/sphere_invalid.rt");
}

void	test_valid_input_valid_plane(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	FILE	*f = fopen("/tmp/plane_valid.rt", "w");
	fputs("A 1.0 255,255,255\n", f);
	fputs("C 0,0,0 0.0,0.0,1.0 90\n", f);
	fputs("L 0,5,0 0.8 255,255,255\n", f);
	fputs("pl 0,0,0 0.0,1.0,0.0 128,128,128\n", f);
	fclose(f);
	assert_int_equal(is_valid_input("/tmp/plane_valid.rt", scene), 1);
	free_scene(scene);
	unlink("/tmp/plane_valid.rt");
}

void	test_valid_input_invalid_plane(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	FILE	*f = fopen("/tmp/plane_invalid.rt", "w");
	fputs("A 1.0 255,255,255\n", f);
	fputs("C 0,0,0 0.0,0.0,1.0 90\n", f);
	fputs("L 0,5,0 0.8 255,255,255\n", f);
	fputs("pl 0,0,0 0.0,5.0,0.0 128,128,128\n", f);
	fclose(f);
	assert_int_equal(is_valid_input("/tmp/plane_invalid.rt", scene), 0);
	free_scene(scene);
	unlink("/tmp/plane_invalid.rt");
}

void	test_valid_input_valid_cylinder(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	FILE	*f = fopen("/tmp/cylinder_valid.rt", "w");
	fputs("A 1.0 255,255,255\n", f);
	fputs("C 0,0,0 0.0,0.0,1.0 90\n", f);
	fputs("L 0,5,0 0.8 255,255,255\n", f);
	fputs("cy 0,0,0 0.0,1.0,0.0 1.0 3.0 0,255,0\n", f);
	fclose(f);
	assert_int_equal(is_valid_input("/tmp/cylinder_valid.rt", scene), 1);
	free_scene(scene);
	unlink("/tmp/cylinder_valid.rt");
}

void	test_valid_input_invalid_cylinder(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	FILE	*f = fopen("/tmp/cylinder_invalid.rt", "w");
	fputs("A 1.0 255,255,255\n", f);
	fputs("C 0,0,0 0.0,0.0,1.0 90\n", f);
	fputs("L 0,5,0 0.8 255,255,255\n", f);
	fputs("cy 0,0,0 0.0,1.0,0.0 -1.0 3.0 0,255,0\n", f);
	fclose(f);
	assert_int_equal(is_valid_input("/tmp/cylinder_invalid.rt", scene), 0);
	free_scene(scene);
	unlink("/tmp/cylinder_invalid.rt");
}

void	test_valid_input_unknown_identifier(void **state)
{
	(void)state;
	t_scene	*scene = make_scene();
	FILE	*f = fopen("/tmp/unknown_id.rt", "w");
	fputs("A 1.0 255,255,255\n", f);
	fputs("C 0,0,0 0.0,0.0,1.0 90\n", f);
	fputs("L 0,5,0 0.8 255,255,255\n", f);
	fputs("xx 0,0,0 1.0 255,255,255\n", f);
	fclose(f);
	assert_int_equal(is_valid_input("/tmp/unknown_id.rt", scene), 0);
	free_scene(scene);
	unlink("/tmp/unknown_id.rt");
}
