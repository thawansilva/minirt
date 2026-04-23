/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_elements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@ai>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/04/22 20:23:08 by thaperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "libft.h"
#include "parser.h"
#include "scene.h"

static t_scene *make_scene(void)
{
    t_scene *scene;

    scene = (t_scene *)calloc(1, sizeof(t_scene));
    scene->objs = NULL;
    scene->num_objs = 0;
    scene->num_lights = 0;
    return (scene);
}

static void free_scene(t_scene *scene)
{
    if (!scene)
        return;
    if (scene->objs)
        ft_lstclear(&scene->objs, free);
    if (scene->light)
        free(scene->light);
    if (scene->surfaces)
        free(scene->surfaces);
    free(scene);
}

void test_parse_elements_integration(void **state)
{
    (void)state;
    t_scene *scene = make_scene();
    t_list *n;

    /* Prepare a small scene: A, C, L, sp */
    ft_lstadd_back(&scene->objs, ft_lstnew(ft_strdup("A 0.2 100,101,102")));
    ft_lstadd_back(&scene->objs, ft_lstnew(ft_strdup("C 0,0,0 0.0,1.0,0.0 90")));
    ft_lstadd_back(&scene->objs, ft_lstnew(ft_strdup("L 1,2,3 0.8 200,201,202")));
    ft_lstadd_back(&scene->objs, ft_lstnew(ft_strdup("sp 5,5,5 2.5 10,20,30")));

    /* set counts so allocations inside parse_elements succeed */
    scene->num_lights = 1;
    scene->num_objs = 1;

    parse_elements(scene);

    /* Ambient */
    assert_true(fabs(scene->ambient.lightness - 0.2) < 0.0001);
    assert_int_equal(scene->ambient.color.r, 100);
    assert_int_equal(scene->ambient.color.g, 101);
    assert_int_equal(scene->ambient.color.b, 102);

    /* Camera */
    assert_true(fabs(scene->camera.coordinate.x) < 0.0001);
    assert_true(fabs(scene->camera.coordinate.y) < 0.0001);
    assert_true(fabs(scene->camera.coordinate.z) < 0.0001);
    assert_true(fabs(scene->camera.norm_vector.y - 1.0) < 0.0001);
    assert_int_equal(scene->camera.fov, 90);

    /* Light */
    assert_true(fabs(scene->light->coordinate.x - 1.0) < 0.0001);
    assert_true(fabs(scene->light->coordinate.y - 2.0) < 0.0001);
    assert_true(fabs(scene->light->coordinate.z - 3.0) < 0.0001);
    assert_true(fabs(scene->light->brightness - 0.8) < 0.0001);
    assert_int_equal(scene->light->color.r, 200);
    assert_int_equal(scene->light->color.g, 201);
    assert_int_equal(scene->light->color.b, 202);

    /* Sphere */
    assert_int_equal(scene->surfaces[0].type, SPHERE);
    assert_true(fabs(scene->surfaces[0].obj.coordinate.x - 5.0) < 0.0001);
    assert_true(fabs(scene->surfaces[0].obj.coordinate.y - 5.0) < 0.0001);
    assert_true(fabs(scene->surfaces[0].obj.coordinate.z - 5.0) < 0.0001);
    assert_int_equal(scene->surfaces[0].obj.color.r, 10);
    assert_int_equal(scene->surfaces[0].obj.color.g, 20);
    assert_int_equal(scene->surfaces[0].obj.color.b, 30);

    free_scene(scene);
}

void test_parse_elements_multiple_objects(void **state)
{
    (void)state;
    t_scene *scene = make_scene();

    /* Put ambient, camera, light and three objects: sp, pl, cy */
    ft_lstadd_back(&scene->objs, ft_lstnew(ft_strdup("A 0.3 1,2,3")));
    ft_lstadd_back(&scene->objs, ft_lstnew(ft_strdup("C 0,0,1 0,1,0 45")));
    ft_lstadd_back(&scene->objs, ft_lstnew(ft_strdup("L 2,2,2 0.7 10,20,30")));
    ft_lstadd_back(&scene->objs, ft_lstnew(ft_strdup("sp 1,1,1 2.0 5,5,5")));
    ft_lstadd_back(&scene->objs, ft_lstnew(ft_strdup("pl 0,1,0 0,1,0 6,6,6")));
    ft_lstadd_back(&scene->objs, ft_lstnew(ft_strdup("cy 3,3,3 0,0,1 1.0 4.0 7,7,7")));

    scene->num_lights = 1;
    scene->num_objs = 3;

    parse_elements(scene);

    /* Check surfaces populated in insertion order */
    assert_int_equal(scene->surfaces[0].type, SPHERE);
    assert_true(fabs(scene->surfaces[0].obj.coordinate.x - 1.0) < 0.0001);
    assert_int_equal(scene->surfaces[0].obj.color.r, 5);

    assert_int_equal(scene->surfaces[1].type, PLANE);
    assert_true(fabs(scene->surfaces[1].obj.orientation.y - 1.0) < 0.0001);
    assert_int_equal(scene->surfaces[1].obj.color.g, 6);

    assert_int_equal(scene->surfaces[2].type, CYLINDER);
    assert_true(fabs(scene->surfaces[2].obj.coordinate.z - 3.0) < 0.0001);
    assert_int_equal(scene->surfaces[2].obj.color.b, 7);

    free_scene(scene);
}
