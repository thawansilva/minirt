#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>

#include "validation.h"
#include "libft.h"

// HELPERS FUNCTIONS

void	free_node(void *line)
{
	free(line);
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

/* VALIDATE FLOAT NUMBER  */

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

/* Empty string — ft_split on "" may return empty array,
   loop never runs, --i == -1 != 3, returns 0. */
void    test_valid_color_empty_string(void **state)
{
    (void)state;
    assert_int_equal(is_valid_color(""), 0);
}

/* ========================================================= */
/* COMPONENT VALIDATION TESTS */
/* ========================================================= */

/* ---------- VECTOR ---------- */

//void test_valid_vector(void **state)
//{
//    (void)state;
//
//    t_vec3 v;
//    assert_true(validate_vector("1.0,2.5,-3.2", &v));
//}

//void test_invalid_vector(void **state)
//{
//    (void)state;
//
//    t_vec3 v;
//    assert_false(validate_vector("1.0,abc,3.2", &v));
//    assert_false(validate_vector("1.0,2.0", &v));
//}
//
///* ---------- NORMAL ---------- */
//
//void test_valid_normal(void **state)
//{
//    (void)state;
//
//    t_vec3 n;
//    assert_true(validate_normal("0.0,1.0,0.0", &n));
//}
//
//void test_invalid_normal(void **state)
//{
//    (void)state;
//
//    t_vec3 n;
//    assert_false(validate_normal("2,0,0", &n)); // out of range
//    assert_false(validate_normal("0,0,0", &n)); // zero vector
//}
//
///* ---------- FOV ---------- */
//
//void test_fov(void **state)
//{
//    (void)state;
//
//    int fov;
//    assert_true(validate_fov("0", &fov));
//    assert_true(validate_fov("180", &fov));
//    assert_false(validate_fov("181", &fov));
//}
//
///* ---------- RATIO ---------- */
//
//void test_ratio(void **state)
//{
//    (void)state;
//
//    double r;
//    assert_true(validate_ratio("0.0", &r));
//    assert_true(validate_ratio("1.0", &r));
//    assert_false(validate_ratio("1.1", &r));
//}
//
///* ---------- RGB ---------- */
//
//void test_rgb(void **state)
//{
//    (void)state;
//
//    t_color c;
//    assert_true(validate_rgb("255,0,128", &c));
//    assert_false(validate_rgb("256,0,0", &c));
//    assert_false(validate_rgb("a,b,c", &c));
//}
//
///* ========================================================= */
///* OBJECT PARSING TESTS (DISPATCHER) */
///* ========================================================= */
//
///* ---------- AMBIENT LIGHT ---------- */
//
//void test_valid_ambient(void **state)
//{
//    (void)state;
//
//    t_scene scene = {0};
//    char *err = NULL;
//
//    assert_true(parse_line("A 0.2 255,255,255", &scene, &err));
//}
//
//void test_duplicate_ambient(void **state)
//{
//    (void)state;
//
//    t_scene scene = {0};
//    char *err = NULL;
//
//    parse_line("A 0.2 255,255,255", &scene, &err);
//    assert_false(parse_line("A 0.3 255,255,255", &scene, &err));
//}
//
///* ---------- CAMERA ---------- */
//
//void test_valid_camera(void **state)
//{
//    (void)state;
//
//    t_scene scene = {0};
//    char *err = NULL;
//
//    assert_true(parse_line("C 0,0,0 0,0,1 70", &scene, &err));
//}
//
///* ---------- LIGHT ---------- */
//
//void test_valid_light(void **state)
//{
//    (void)state;
//
//    t_scene scene = {0};
//    char *err = NULL;
//
//    assert_true(parse_line("L 0,0,0 0.5 255,255,255", &scene, &err));
//}
//
///* ---------- SPHERE ---------- */
//
//void test_valid_sphere(void **state)
//{
//    (void)state;
//
//    t_scene scene = {0};
//    char *err = NULL;
//
//    assert_true(parse_line("sp 0,0,0 10 255,0,0", &scene, &err));
//}
//
///* ---------- PLANE ---------- */
//
//void test_valid_plane(void **state)
//{
//    (void)state;
//
//    t_scene scene = {0};
//    char *err = NULL;
//
//    assert_true(parse_line("pl 0,0,0 0,1,0 255,255,255", &scene, &err));
//}
//
///* ---------- CYLINDER ---------- */
//
//void test_valid_cylinder(void **state)
//{
//    (void)state;
//
//    t_scene scene = {0};
//    char *err = NULL;
//
//    assert_true(parse_line("cy 0,0,0 0,1,0 10 20 255,255,255", &scene, &err));
//}
//
///* ========================================================= */
///* ERROR HANDLING TESTS */
///* ========================================================= */
//
///* ---------- INVALID IDENTIFIER ---------- */
//
//void test_invalid_identifier(void **state)
//{
//    (void)state;
//
//    t_scene scene = {0};
//    char *err = NULL;
//
//    assert_false(parse_line("xx 0,0,0", &scene, &err));
//}
//
///* ---------- WRONG ARGUMENT COUNT ---------- */
//
//void test_wrong_arg_count(void **state)
//{
//    (void)state;
//
//    t_scene scene = {0};
//    char *err = NULL;
//
//    assert_false(parse_line("sp 0,0,0 10", &scene, &err));
//}
//
///* ========================================================= */
///* FILE / GLOBAL PARSER TESTS */
///* ========================================================= */
//
//void test_valid_scene(void **state)
//{
//    (void)state;
//
//    t_scene scene;
//    char *err = NULL;
//
//    assert_true(read_file("valid.rt", &scene, &err));
//}
//
//void test_missing_camera(void **state)
//{
//    (void)state;
//
//    t_scene scene;
//    char *err = NULL;
//
//    assert_false(read_file("no_camera.rt", &scene, &err));
//}
