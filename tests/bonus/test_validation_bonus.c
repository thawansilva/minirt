/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_validation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaperei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:40:48 by thaperei          #+#    #+#             */
/*   Updated: 2026/04/26 13:40:48 by thaperei         ###   ########.fr       */
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
