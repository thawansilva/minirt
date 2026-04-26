/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_validation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:40:48 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/26 13:58:38 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "test_validation_bonus.h"
#include "validation_bonus.h"
#include "libft.h"
#include "parser_bonus.h"
#include "scene_bonus.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* =========================================================
   HELPERS — reuse the same pattern as test_valid_input.c
   ========================================================= */

static t_scene  *make_scene(void)
{
    return (calloc(1, sizeof(t_scene)));
}

static void free_scene(t_scene *scene)
{
    t_list  *node;
    t_list  *next;

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

static void write_rt(const char *path, const char *content)
{
    FILE    *f;

    f = fopen(path, "w");
    fputs(content, f);
    fclose(f);
}

#define MANDATORY \
    "A 0.5 255,255,255\n" \
    "C 0,0,0 0.0,0.0,1.0 90\n" \
    "L 0,5,0 0.8 255,255,255\n"

/* =========================================================
   CONE unit tests (uses is_valid_sphere: coords, float, color)
   arr[0] = identifier "co"
   arr[1] = coordinates
   arr[2] = diameter (float)
   arr[3] = color
   ========================================================= */

void    test_valid_cone_valid(void **state)
{
    (void)state;
    char *arr[] = {"co", "0,0,0", "2.0", "255,0,0", NULL};
    assert_int_equal(is_valid_sphere(arr), 1);
}

void    test_valid_cone_invalid_coordinates(void **state)
{
    (void)state;
    char *arr[] = {"co", "abc,def,ghi", "2.0", "255,0,0", NULL};
    assert_int_equal(is_valid_sphere(arr), 0);
}

void    test_valid_cone_invalid_diameter(void **state)
{
    (void)state;
    char *arr[] = {"co", "0,0,0", "abc", "255,0,0", NULL};
    assert_int_equal(is_valid_sphere(arr), 0);
}

void    test_valid_cone_invalid_color(void **state)
{
    (void)state;
    char *arr[] = {"co", "0,0,0", "2.0", "256,0,0", NULL};
    assert_int_equal(is_valid_sphere(arr), 0);
}

void    test_valid_cone_negative_diameter(void **state)
{
    (void)state;
    char *arr[] = {"co", "0,0,0", "-2.0", "255,0,0", NULL};
    assert_int_equal(is_valid_sphere(arr), 0);
}

void    test_valid_cone_zero_diameter(void **state)
{
    (void)state;
    char *arr[] = {"co", "0,0,0", "0.0", "255,0,0", NULL};
    assert_int_equal(is_valid_sphere(arr), 1);
}

void    test_valid_cone_null_coordinates(void **state)
{
    (void)state;
    char *arr[] = {"co", NULL, "2.0", "255,0,0", NULL};
    assert_int_equal(is_valid_sphere(arr), 0);
}

void    test_valid_cone_null_diameter(void **state)
{
    (void)state;
    char *arr[] = {"co", "0,0,0", NULL, "255,0,0", NULL};
    assert_int_equal(is_valid_sphere(arr), 0);
}

void    test_valid_cone_null_color(void **state)
{
    (void)state;
    char *arr[] = {"co", "0,0,0", "2.0", NULL, NULL};
    assert_int_equal(is_valid_sphere(arr), 0);
}

/* =========================================================
   HYPERBOLOID unit tests (uses is_valid_plane: coords, vector, color)
   arr[0] = "hy"
   arr[1] = coordinates
   arr[2] = normalized vector
   arr[3] = color
   ========================================================= */

void    test_valid_hyperboloid_valid(void **state)
{
    (void)state;
    char *arr[] = {"hy", "0,0,0", "0.0,1.0,0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 1);
}

void    test_valid_hyperboloid_invalid_coordinates(void **state)
{
    (void)state;
    char *arr[] = {"hy", "abc,def,ghi", "0.0,1.0,0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_hyperboloid_invalid_vector(void **state)
{
    (void)state;
    char *arr[] = {"hy", "0,0,0", "abc,def,ghi", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_hyperboloid_invalid_color(void **state)
{
    (void)state;
    char *arr[] = {"hy", "0,0,0", "0.0,1.0,0.0", "256,0,0", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_hyperboloid_null_coordinates(void **state)
{
    (void)state;
    char *arr[] = {"hy", NULL, "0.0,1.0,0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_hyperboloid_null_vector(void **state)
{
    (void)state;
    char *arr[] = {"hy", "0,0,0", NULL, "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_hyperboloid_null_color(void **state)
{
    (void)state;
    char *arr[] = {"hy", "0,0,0", "0.0,1.0,0.0", NULL, NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_hyperboloid_vector_out_of_range(void **state)
{
    (void)state;
    char *arr[] = {"hy", "0,0,0", "0.0,1.5,0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_hyperboloid_vector_wrong_count(void **state)
{
    (void)state;
    char *arr[] = {"hy", "0,0,0", "0.0,1.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

/* =========================================================
   PARABOLOID unit tests (uses is_valid_plane: coords, vector, color)
   Identical structure to hyperboloid — validates the same wiring.
   ========================================================= */

void    test_valid_paraboloid_valid(void **state)
{
    (void)state;
    char *arr[] = {"pa", "0,0,0", "0.0,1.0,0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 1);
}

void    test_valid_paraboloid_invalid_coordinates(void **state)
{
    (void)state;
    char *arr[] = {"pa", "abc,def,ghi", "0.0,1.0,0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_paraboloid_invalid_vector(void **state)
{
    (void)state;
    char *arr[] = {"pa", "0,0,0", "abc,def,ghi", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_paraboloid_invalid_color(void **state)
{
    (void)state;
    char *arr[] = {"pa", "0,0,0", "0.0,1.0,0.0", "256,0,0", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_paraboloid_null_coordinates(void **state)
{
    (void)state;
    char *arr[] = {"pa", NULL, "0.0,1.0,0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_paraboloid_null_vector(void **state)
{
    (void)state;
    char *arr[] = {"pa", "0,0,0", NULL, "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_paraboloid_null_color(void **state)
{
    (void)state;
    char *arr[] = {"pa", "0,0,0", "0.0,1.0,0.0", NULL, NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_paraboloid_vector_out_of_range(void **state)
{
    (void)state;
    char *arr[] = {"pa", "0,0,0", "0.0,1.5,0.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

void    test_valid_paraboloid_vector_wrong_count(void **state)
{
    (void)state;
    char *arr[] = {"pa", "0,0,0", "0.0,1.0", "255,255,255", NULL};
    assert_int_equal(is_valid_plane(arr), 0);
}

/* =========================================================
   is_valid_input BONUS integration tests
   These verify that "co", "hy", "pa" are correctly wired
   in func_objs and that the full pipeline accepts/rejects them.
   ========================================================= */

void    test_valid_input_bonus_valid_full_scene(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/bonus_full.rt",
        MANDATORY
        "sp 0,0,5 2.0 255,0,0\n"
        "pl 0,0,0 0.0,1.0,0.0 128,128,128\n"
        "cy 0,0,0 0.0,1.0,0.0 1.0 3.0 0,255,0\n"
        "co 1,0,0 1.5 255,128,0\n"
        "hy 2,0,0 0.0,1.0,0.0 0,128,255\n"
        "pa 3,0,0 1.0,0.0,0.0 128,0,255\n");
    assert_int_equal(is_valid_input("/tmp/bonus_full.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/bonus_full.rt");
}

void    test_valid_input_bonus_valid_cone(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/bonus_co.rt",
        MANDATORY
        "co 0,0,0 2.0 255,0,0\n");
    assert_int_equal(is_valid_input("/tmp/bonus_co.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/bonus_co.rt");
}

void    test_valid_input_bonus_valid_hyperboloid(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/bonus_hy.rt",
        MANDATORY
        "hy 0,0,0 0.0,1.0,0.0 255,255,0\n");
    assert_int_equal(is_valid_input("/tmp/bonus_hy.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/bonus_hy.rt");
}

void    test_valid_input_bonus_valid_paraboloid(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/bonus_pa.rt",
        MANDATORY
        "pa 0,0,0 0.0,1.0,0.0 0,255,255\n");
    assert_int_equal(is_valid_input("/tmp/bonus_pa.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/bonus_pa.rt");
}

void    test_valid_input_bonus_invalid_cone(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/bonus_inv_co.rt",
        MANDATORY
        "co 0,0,0 abc 255,0,0\n");
    assert_int_equal(is_valid_input("/tmp/bonus_inv_co.rt", scene), 0);
    free_scene(scene);
    unlink("/tmp/bonus_inv_co.rt");
}

void    test_valid_input_bonus_invalid_hyperboloid(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/bonus_inv_hy.rt",
        MANDATORY
        "hy 0,0,0 0.0,5.0,0.0 255,255,0\n");
    assert_int_equal(is_valid_input("/tmp/bonus_inv_hy.rt", scene), 0);
    free_scene(scene);
    unlink("/tmp/bonus_inv_hy.rt");
}

void    test_valid_input_bonus_invalid_paraboloid(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/bonus_inv_pa.rt",
        MANDATORY
        "pa 0,0,0 0.0,1.0,0.0 256,0,0\n");
    assert_int_equal(is_valid_input("/tmp/bonus_inv_pa.rt", scene), 0);
    free_scene(scene);
    unlink("/tmp/bonus_inv_pa.rt");
}

void    test_valid_input_bonus_multiple_cones(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/bonus_multi_co.rt",
        MANDATORY
        "co 0,0,0 2.0 255,0,0\n"
        "co 3,0,0 1.0 0,255,0\n"
        "co -3,0,0 3.0 0,0,255\n");
    assert_int_equal(is_valid_input("/tmp/bonus_multi_co.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/bonus_multi_co.rt");
}

void    test_valid_input_bonus_multiple_hyperboloids(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/bonus_multi_hy.rt",
        MANDATORY
        "hy 0,0,0 0.0,1.0,0.0 255,255,0\n"
        "hy 0,5,0 1.0,0.0,0.0 0,255,255\n");
    assert_int_equal(is_valid_input("/tmp/bonus_multi_hy.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/bonus_multi_hy.rt");
}

void    test_valid_input_bonus_multiple_paraboloids(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/bonus_multi_pa.rt",
        MANDATORY
        "pa 0,0,0 0.0,1.0,0.0 128,0,255\n"
        "pa 5,0,0 1.0,0.0,0.0 255,128,0\n");
    assert_int_equal(is_valid_input("/tmp/bonus_multi_pa.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/bonus_multi_pa.rt");
}

void    test_valid_input_bonus_any_order(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/bonus_any_order.rt",
        "co 1,0,0 1.5 255,128,0\n"
        "A 0.5 255,255,255\n"
        "hy 2,0,0 0.0,1.0,0.0 0,128,255\n"
        "L 0,5,0 0.8 255,255,255\n"
        "pa 3,0,0 1.0,0.0,0.0 128,0,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n");
    assert_int_equal(is_valid_input("/tmp/bonus_any_order.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/bonus_any_order.rt");
}

/* =========================================================
   LIGHT VALIDATION TESTS
   Tests for: minimum 1 light required, multiple lights allowed,
   absence of light is invalid
   ========================================================= */

void    test_valid_input_light_exactly_one(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_exactly_one.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "L 0,5,0 0.8 255,255,255\n"
        "sp 0,0,5 2.0 128,128,128\n");
    assert_int_equal(is_valid_input("/tmp/light_exactly_one.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/light_exactly_one.rt");
}

void    test_valid_input_light_multiple_lights(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_multiple.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "L 0,5,0 0.8 255,255,255\n"
        "L 10,10,10 0.5 200,200,200\n"
        "L -5,3,8 0.6 100,150,200\n"
        "sp 0,0,5 2.0 128,128,128\n");
    assert_int_equal(is_valid_input("/tmp/light_multiple.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/light_multiple.rt");
}

void    test_valid_input_light_many_lights(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_many.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "L 0,5,0 0.8 255,0,0\n"
        "L 5,5,5 0.6 0,255,0\n"
        "L 10,0,0 0.7 0,0,255\n"
        "L -5,-5,-5 0.5 255,255,0\n"
        "sp 0,0,5 2.0 128,128,128\n");
    assert_int_equal(is_valid_input("/tmp/light_many.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/light_many.rt");
}

void    test_invalid_input_light_missing(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_missing.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "sp 0,0,5 2.0 255,0,0\n"
        "pl 0,0,0 0.0,1.0,0.0 0,255,0\n");
    assert_int_equal(is_valid_input("/tmp/light_missing.rt", scene), 0);
    free_scene(scene);
    unlink("/tmp/light_missing.rt");
}

void    test_invalid_input_light_completely_absent(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_absent.rt",
        "A 0.5 255,255,255\n"
        "sp 0,0,5 2.0 255,0,0\n"
        "C 0,0,0 0.0,0.0,1.0 90\n");
    assert_int_equal(is_valid_input("/tmp/light_absent.rt", scene), 0);
    free_scene(scene);
    unlink("/tmp/light_absent.rt");
}

void    test_valid_input_light_with_all_objects(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_all_objects.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "L 0,5,0 0.8 255,255,255\n"
        "sp 0,0,5 2.0 255,0,0\n"
        "pl 0,0,0 0.0,1.0,0.0 0,255,0\n"
        "cy 5,0,0 0.0,1.0,0.0 1.0 3.0 0,0,255\n"
        "co 10,0,0 1.5 255,128,0\n"
        "hy 15,0,0 1.0,0.0,0.0 128,255,0\n"
        "pa 20,0,0 0.0,1.0,0.0 0,128,255\n");
    assert_int_equal(is_valid_input("/tmp/light_all_objects.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/light_all_objects.rt");
}

void    test_valid_input_light_multiple_with_all_objects(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_multi_all_objects.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "L 0,5,0 0.8 255,255,255\n"
        "L 10,10,10 0.5 200,200,200\n"
        "L -5,-5,-5 0.6 100,100,100\n"
        "sp 0,0,5 2.0 255,0,0\n"
        "pl 0,0,0 0.0,1.0,0.0 0,255,0\n"
        "cy 5,0,0 0.0,1.0,0.0 1.0 3.0 0,0,255\n"
        "co 10,0,0 1.5 255,128,0\n"
        "hy 15,0,0 1.0,0.0,0.0 128,255,0\n"
        "pa 20,0,0 0.0,1.0,0.0 0,128,255\n");
    assert_int_equal(is_valid_input("/tmp/light_multi_all_objects.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/light_multi_all_objects.rt");
}

void    test_valid_input_light_different_positions(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_diff_pos.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "L 0,0,0 0.8 255,255,255\n"
        "L 100,100,100 0.5 200,200,200\n"
        "L -100,-100,-100 0.6 100,100,100\n"
        "L 0.5,0.5,0.5 0.7 50,50,50\n"
        "sp 0,0,5 2.0 255,0,0\n");
    assert_int_equal(is_valid_input("/tmp/light_diff_pos.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/light_diff_pos.rt");
}

void    test_valid_input_light_different_brightnesses(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_diff_bright.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "L 0,5,0 0.0 255,255,255\n"
        "L 0,6,0 0.5 255,255,255\n"
        "L 0,7,0 1.0 255,255,255\n"
        "sp 0,0,5 2.0 255,0,0\n");
    assert_int_equal(is_valid_input("/tmp/light_diff_bright.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/light_diff_bright.rt");
}

void    test_valid_input_light_different_colors(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_diff_color.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "L 0,5,0 0.8 255,0,0\n"
        "L 0,6,0 0.8 0,255,0\n"
        "L 0,7,0 0.8 0,0,255\n"
        "L 0,8,0 0.8 255,255,0\n"
        "L 0,9,0 0.8 0,255,255\n"
        "sp 0,0,5 2.0 255,0,0\n");
    assert_int_equal(is_valid_input("/tmp/light_diff_color.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/light_diff_color.rt");
}

void    test_valid_input_light_minimum_brightness(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_min_bright.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "L 0,5,0 0.0 128,128,128\n"
        "sp 0,0,5 2.0 255,0,0\n");
    assert_int_equal(is_valid_input("/tmp/light_min_bright.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/light_min_bright.rt");
}

void    test_valid_input_light_maximum_brightness(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_max_bright.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "L 0,5,0 1.0 255,255,255\n"
        "sp 0,0,5 2.0 255,0,0\n");
    assert_int_equal(is_valid_input("/tmp/light_max_bright.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/light_max_bright.rt");
}

void    test_valid_input_light_light_first(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_first.rt",
        "L 0,5,0 0.8 255,255,255\n"
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "sp 0,0,5 2.0 255,0,0\n"
        "sp 0,0,5 2.0 255,0,0\n");
    assert_int_equal(is_valid_input("/tmp/light_first.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/light_first.rt");
}

void    test_valid_input_light_light_middle(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_middle.rt",
        "A 0.5 255,255,255\n"
        "L 0,5,0 0.8 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "sp 0,0,5 2.0 255,0,0\n");
    assert_int_equal(is_valid_input("/tmp/light_middle.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/light_middle.rt");
}

void    test_valid_input_light_light_last(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_last.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "sp 0,0,5 2.0 255,0,0\n"
        "L 0,5,0 0.8 255,255,255\n");
    assert_int_equal(is_valid_input("/tmp/light_last.rt", scene), 1);
    free_scene(scene);
    unlink("/tmp/light_last.rt");
}

void    test_invalid_input_light_negative_brightness(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_neg_bright.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "L 0,5,0 -0.5 255,255,255\n"
        "sp 0,0,5 2.0 255,0,0\n");
    assert_int_equal(is_valid_input("/tmp/light_neg_bright.rt", scene), 0);
    free_scene(scene);
    unlink("/tmp/light_neg_bright.rt");
}

void    test_invalid_input_light_over_max_brightness(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_over_bright.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "L 0,5,0 1.5 255,255,255\n"
        "sp 0,0,5 2.0 255,0,0\n");
    assert_int_equal(is_valid_input("/tmp/light_over_bright.rt", scene), 0);
    free_scene(scene);
    unlink("/tmp/light_over_bright.rt");
}

void    test_invalid_input_light_invalid_coordinates(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_inv_coord.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "L abc,def,ghi 0.8 255,255,255\n"
        "sp 0,0,5 2.0 255,0,0\n");
    assert_int_equal(is_valid_input("/tmp/light_inv_coord.rt", scene), 0);
    free_scene(scene);
    unlink("/tmp/light_inv_coord.rt");
}

void    test_invalid_input_light_invalid_color(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_inv_color.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "L 0,5,0 0.8 256,0,0\n"
        "sp 0,0,5 2.0 255,0,0\n");
    assert_int_equal(is_valid_input("/tmp/light_inv_color.rt", scene), 0);
    free_scene(scene);
    unlink("/tmp/light_inv_color.rt");
}

void    test_invalid_input_light_missing_among_objects(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    write_rt("/tmp/light_missing_objects.rt",
        "A 0.5 255,255,255\n"
        "C 0,0,0 0.0,0.0,1.0 90\n"
        "sp 0,0,5 2.0 255,0,0\n"
        "pl 0,0,0 0.0,1.0,0.0 0,255,0\n"
        "cy 5,0,0 0.0,1.0,0.0 1.0 3.0 0,0,255\n");
    assert_int_equal(is_valid_input("/tmp/light_missing_objects.rt", scene), 0);
    free_scene(scene);
    unlink("/tmp/light_missing_objects.rt");
}
