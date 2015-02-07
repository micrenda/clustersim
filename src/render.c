/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#include <png.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <libconfig.h>
#include <limits.h>
#include "common.h"
#include "color_map.h"

/* A pixel. */
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel_t;

/* A picture. */
typedef struct  {
    pixel_t *pixels;
    size_t width;
    size_t height;
} bitmap_t;

pixel_t* pixel_at (bitmap_t* bitmap, int x, int y);
unsigned int get_pixel_color(CommonStatus* common_status, Render* render, Cluster* cluster, unsigned int clusters_count, unsigned short t, unsigned short duration);
void save_png_to_file (bitmap_t *bitmap, const char *path);
void render2d(CommonStatus* common_status, Render* render, unsigned int space[], unsigned int space_sizes[], Cluster* clusters, unsigned int clusters_count, unsigned int t, unsigned int duration, char* output_directory);
void render3d(CommonStatus* common_status, Render* render, unsigned int space[], unsigned int space_sizes[], Cluster* clusters, unsigned int clusters_count, unsigned int t, unsigned int duration, char* output_directory);
short  should_be_rendered(CommonStatus* common_status,  Render* render, unsigned int current[common_status->dimensions], unsigned int space[common_status->space_volume]);

void render(CommonStatus* common_status, Render* render, unsigned int space[], unsigned int space_sizes[], Cluster* clusters, unsigned int clusters_count, unsigned int t, unsigned int duration, char* output_directory)
{
    switch(render->type)
    {
        case R_2D:
            return render2d(common_status, render, space, space_sizes, clusters, clusters_count, t, duration, output_directory);
        case R_3D:
            return render3d(common_status, render, space, space_sizes, clusters, clusters_count, t, duration, output_directory);
    }
}

void render3d(CommonStatus* common_status, Render* render, unsigned int space[], unsigned int space_sizes[], Cluster* clusters, unsigned int clusters_count, unsigned int t, unsigned int duration, char* output_directory)
{
    if (render->axis_1 == USHRT_MAX)
    {
        printf("Unable to detect render axis %d\n", 1);
        exit(-1);
    }

    if (render->axis_2 == USHRT_MAX)
    {
        printf("Unable to detect render axis %d\n", 2);
        exit(-1);
    }

    if (render->axis_3 == USHRT_MAX)
    {
        printf("Unable to detect render axis %d\n", 3);
        exit(-1);
    }









    // Creating a simplied version of space: we keep only surfaces and we remove the internal points
    unsigned int*  simplified_space = malloc(common_status->space_volume * sizeof(unsigned int));
    unsigned long  simplified_grow_total = common_status->stat_pixel_grow_total;

    for (unsigned long p = 0; p < common_status->space_volume; p++)
    {
        if (space[p] != UINT_MAX)
        {
            unsigned int current[common_status->dimensions];
            decode_position_cartesian(common_status, current, p);

            short surrounded_by_same_cluster = 1;

            unsigned int adjacent_points[common_status->adjacents_count][common_status->dimensions];
            get_adjacents_points(common_status, current, adjacent_points);

            for (unsigned int a = 0; a < common_status->adjacents_count; a++)
            {

                if (is_inside(common_status, adjacent_points[a], space_sizes))
                {
                    unsigned long adjacent_encoded = encode_position_cartesian(common_status, adjacent_points[a]);

                    if (space[adjacent_encoded] != space[p])
                    {
                         surrounded_by_same_cluster = 0;
                        break;
                    }
                }
                else
                {
                    surrounded_by_same_cluster = 0;
                    break;
                }
            }


            if (!surrounded_by_same_cluster)
            {
                simplified_space[p] = space[p];
            }
            else
            {
                simplified_space[p] = UINT_MAX; // It is an internal point. Removing to reduce the ply file size
                simplified_grow_total--;
            }

        }
        else
            simplified_space[p] = space[p];


    }



    char filename[256];

	sprintf(filename, "%s/frame_%06u.ply", output_directory, t);
    FILE* f = fopen(filename, "w");


    fprintf(f, "ply\n");
    fprintf(f, "format ascii 1.0\n");
    fprintf(f, "comment made by custersim\n");

    if (render->name != NULL)
        fprintf(f, "comment render: %s\n", render->name);
    fprintf(f, "element vertex %lu\n", simplified_grow_total);

    if (common_status->dimensions == 3)
    {
        char axis_1_label[8];
        char axis_2_label[8];
        char axis_3_label[8];

        dimension_to_label(axis_1_label, common_status, render->axis_1);
        dimension_to_label(axis_2_label, common_status, render->axis_2);
        dimension_to_label(axis_3_label, common_status, render->axis_3);

        fprintf(f, "property float %s\n", axis_1_label);
        fprintf(f, "property float %s\n", axis_2_label);
        fprintf(f, "property float %s\n", axis_3_label);
    }
    else
    {
        fprintf(f, "property float x\n");
        fprintf(f, "property float y\n");
        fprintf(f, "property float z\n");
    }

    // fprintf(f, "property int material_index\n");

   // fprintf(f, "element material %u\n", clusters_count);

    fprintf(f, "property uchar red\n");
    fprintf(f, "property uchar green\n");
    fprintf(f, "property uchar blue\n");

    fprintf(f, "end_header\n");




    for (unsigned long p = 0; p < common_status->space_volume; p++)
    {

        if (simplified_space[p] != UINT_MAX)
        {
            unsigned int current[common_status->dimensions];
            decode_position_cartesian(common_status, current, p);

            if (should_be_rendered(common_status, render, current, simplified_space))
            {
                Cluster* cluster = &clusters[simplified_space[p]];

                unsigned int pos_i = current[render->axis_1];
                unsigned int pos_j = current[render->axis_2];
                unsigned int pos_k = current[render->axis_3];

                unsigned int color = get_pixel_color(common_status, render, cluster, clusters_count, t, duration);
                unsigned short red 	    = (color & 0xff0000) >> 16;
                unsigned short green 	= (color & 0x00ff00) >>  8;
                unsigned short blue 	= (color & 0x0000ff) >>  0;

                fprintf(f, "%u %u %u %u %u %u\n", pos_i, pos_j, pos_k, red, green, blue);
            }
        }
    }

    fclose(f);



    free(simplified_space);
}

void render2d(CommonStatus* common_status, Render* render, unsigned int space[], unsigned int space_sizes[], Cluster* clusters, unsigned int clusters_count, unsigned int t, unsigned int duration, char* output_directory)
{

    if (render->axis_1 == USHRT_MAX)
    {
        printf("Unable to detect render axis %d\n", 1);
        exit(-1);
    }

    if (render->axis_2 == USHRT_MAX)
    {
        printf("Unable to detect render axis %d\n", 2);
        exit(-1);
    }


    unsigned width  = space_sizes[render->axis_1];
    unsigned height = space_sizes[render->axis_2];


    bitmap_t bmp;
    /* Create an image. */
    bmp.width 	= width;
    bmp.height 	= height;
    bmp.pixels  = calloc(bmp.width * bmp.height, sizeof(pixel_t));

    // Drawing background
    for (unsigned int i = 0; i < width; i++)
    {
        for (unsigned int j = 0; j < height; j++)
        {
            pixel_t* pixel = pixel_at (&bmp, i, j);

            pixel->red 	    = 0xff;
            pixel->blue 	= 0xff;
            pixel->green 	= 0xff;
        }
    }



    for (unsigned long p = 0; p < common_status->space_volume; p++)
    {
        if (space[p] != UINT_MAX)
        {

            unsigned int current[common_status->dimensions];
            decode_position_cartesian(common_status, current, p);



            if (should_be_rendered(common_status, render, current, space))
            {
                unsigned int pos_i = current[render->axis_1];
                unsigned int pos_j = current[render->axis_2];

                Cluster* cluster = &clusters[space[p]];
                pixel_t * pixel = pixel_at (&bmp, pos_i, pos_j);

                unsigned int color = get_pixel_color(common_status, render, cluster, clusters_count, t, duration);

                pixel->red 	    = (color & 0xff0000) >> 16;
                pixel->green 	= (color & 0x00ff00) >>  8;
                pixel->blue 	= (color & 0x0000ff) >>  0;
            }
        }
    }

    char filename[256];

	sprintf(filename, "%s/frame_%06u.png", output_directory, t);
	save_png_to_file(&bmp, filename);

	free(bmp.pixels);

}

short  should_be_rendered(CommonStatus* common_status,  Render* render, unsigned int current[common_status->dimensions], unsigned int space[common_status->space_volume])
{
    short to_be_rendered = 1;
    for (unsigned short d = 0; d < common_status->dimensions; d++)
    {
        if (d == render->axis_1 || d == render->axis_2 || (render->type == R_3D && d == render->axis_3) )
            continue; // we jump the axis of our render

        unsigned int cursor[common_status->dimensions];
        // copy the value of current into probe array
        for (unsigned short e = 0; e < common_status->dimensions; e++)
            cursor[e] = current[e];

        unsigned short trasparent = 1;

        switch(render->cut_directions[d])
        {
        case 0:

            for (cursor[d] = render->cut_levels[d]; cursor[d] > current[d]; cursor[d]--)
            {
                trasparent &= space[encode_position_cartesian(common_status, cursor)] == UINT_MAX;
            }

            to_be_rendered &= trasparent;

        break;

        case 1:

            for (cursor[d] = render->cut_levels[d]; cursor[d] < current[d]; cursor[d]++)
            {
                trasparent &= space[encode_position_cartesian(common_status, cursor)] == UINT_MAX;
            }

            to_be_rendered &= trasparent;

        break;

        default:
            assert(0); // We should never enter here
        break;
        }

    }

    return to_be_rendered;
}

unsigned int get_pixel_color(CommonStatus* common_status, Render* render, Cluster* cluster, unsigned int clusters_count, unsigned short t, unsigned short duration)
{
    switch (render->color_scheme)
    {
        case RANDOM_ACID:
            return get_color_acid(cluster->id, clusters_count);
        case GRADIENT_RADIUS:
            return get_color_grad_rgb(cluster->radius, common_status->max_radius, render->color_1, render->color_2);
        case GRADIENT_VOLUME:
            return get_color_grad_rgb(cluster->volume, common_status->space_volume, render->color_1, render->color_2);
        case GRADIENT_AGE:
            return get_color_grad_rgb(t - cluster->creation_time, duration, render->color_1, render->color_2);
        case GRADIENT_BIRTH:
            return get_color_grad_rgb(cluster->creation_time, duration, render->color_1, render->color_2);
        default:
            return 0x000000;
    }

}



pixel_t* pixel_at (bitmap_t* bitmap, int x, int y)
{
    return &bitmap->pixels[bitmap->width * y + x];
}

void save_png_to_file (bitmap_t *bitmap, const char *path)
{
    FILE * fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    size_t x, y;
    png_byte ** row_pointers = NULL;

    /* The following number is set by trial and error only. I cannot
       see where it it is documented in the libpng manual.
    */
    int pixel_size = 3;
    int depth = 8;

    fp = fopen (path, "wb");
    if (! fp) {
        goto fopen_failed;
    }

    png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        goto png_create_write_struct_failed;
    }

    info_ptr = png_create_info_struct (png_ptr);
    if (info_ptr == NULL) {
        goto png_create_info_struct_failed;
    }

    /* Set up error handling. */

    if (setjmp (png_jmpbuf (png_ptr))) {
        goto png_failure;
    }

    /* Set image attributes. */

    png_set_IHDR (png_ptr,
                  info_ptr,
                  bitmap->width,
                  bitmap->height,
                  depth,
                  PNG_COLOR_TYPE_RGB,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);

    /* Initialize rows of PNG. */

    row_pointers = png_malloc (png_ptr, bitmap->height * sizeof (png_byte *));
    for (y = 0; y < bitmap->height; ++y) {
        png_byte *row = png_malloc (png_ptr, sizeof (uint8_t) * bitmap->width * pixel_size);
        row_pointers[y] = row;
        for (x = 0; x < bitmap->width; ++x) {
            pixel_t * pixel = pixel_at (bitmap, x, y);
            *row++ = pixel->red;
            *row++ = pixel->green;
            *row++ = pixel->blue;
        }
    }

    /* Write the image data to "fp". */

    png_init_io 	(png_ptr, fp);
    png_set_rows 	(png_ptr, info_ptr, row_pointers);
    png_write_png 	(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);


    for (y = 0; y < bitmap->height; y++) {
        png_free (png_ptr, row_pointers[y]);
    }

    png_free (png_ptr, row_pointers);

 png_failure:
 png_create_info_struct_failed:
    png_destroy_write_struct (&png_ptr, &info_ptr);

 png_create_write_struct_failed:
    fclose (fp);

 fopen_failed:
	return;

}


void parse_render(CommonStatus* common_status, Render* render, config_setting_t* config_render)
{
        render->name[0] = '\0';

        const char *render_name;
        if (config_setting_lookup_string(config_render, "name", &render_name) == CONFIG_TRUE)
        {
            strcat(render->name, render_name);
        }

        const char* axis_1          = NULL;
        const char* axis_2          = NULL;
        const char* axis_3          = NULL;
        const char* cuts            = NULL;
        const char* color_scheme    = NULL;


        if (config_setting_lookup_string(config_render, "axis_1", &axis_1) != CONFIG_TRUE)
        {
            printf("Unble read attribute axis_1 in render element.\n");
            exit(-1);
        }

        if (config_setting_lookup_string(config_render, "axis_2", &axis_2) != CONFIG_TRUE)
        {
            printf("Unble read attribute axis_2 in render element.\n");
            exit(-1);
        }

        if (config_setting_lookup_string(config_render, "axis_3", &axis_3) == CONFIG_TRUE)
            render->type = R_3D;
        else
            render->type = R_2D;

        // Parsing axes
        render->axis_1 = label_to_dimension(common_status, (char*) axis_1);
        render->axis_2 = label_to_dimension(common_status, (char*) axis_2);
        if (axis_3 != NULL) render->axis_3 = label_to_dimension(common_status, (char*) axis_3);


        config_setting_lookup_string(config_render, "cuts", (const char **) &cuts);

        // Parsing cuts
        render->cut_levels = calloc(common_status->dimensions, sizeof(unsigned int));
        render->cut_directions = calloc(common_status->dimensions, sizeof(unsigned short));

        for (unsigned short d = 0; d < common_status->dimensions; d++)
        {
            render->cut_levels[d] = common_status->space_sizes[d] - 1;
            render->cut_directions[d] = 0;
        }

        char* cut = strtok((char*) cuts, ",");

        while(cut)
        {
            char cut_label[255];
            unsigned int cut_value;
            char cut_direction[255];

            if (sscanf(cut, "%[A-Za-z0-9]=%u%s", cut_label, &cut_value, cut_direction) != 3)
            {
                printf("Error at cuts element in render element\n");
                exit(-1);
            }

            unsigned short dimension = label_to_dimension(common_status, cut_label);

            render->cut_levels[dimension] = cut_value;
            render->cut_directions[dimension] = strcmp(cut_direction, "up") == 0;

            // Validating the cut levels, just in case
            if (render->cut_levels[dimension] >= common_status->space_sizes[dimension])
            {
                printf("Error at cuts element in render element: cut level %u is bigger than space size %u\n", render->cut_levels[dimension], common_status->space_sizes[dimension]);
                exit(-1);
            }


            cut = strtok(NULL, ",");
        }


        if (config_setting_lookup_string(config_render, "color_scheme", (const char**) &color_scheme) != CONFIG_TRUE)
        {
            printf("Unble read attribute color_scheme in render element.\n");
            exit(-1);
        }



        if (!strcmp(color_scheme, "RANDOM_ACID"))
            render->color_scheme = RANDOM_ACID;
        else if (!strcmp(color_scheme, "GRADIENT_RADIUS"))
            render->color_scheme = GRADIENT_RADIUS;
        else if (!strcmp(color_scheme, "GRADIENT_VOLUME"))
            render->color_scheme = GRADIENT_VOLUME;
        else if (!strcmp(color_scheme, "GRADIENT_AGE"))
            render->color_scheme = GRADIENT_AGE;
        else if (!strcmp(color_scheme, "GRADIENT_BIRTH"))
            render->color_scheme = GRADIENT_BIRTH;
        else
        {
            printf("Unable to decode color_scheme: %s\n", color_scheme);
            exit(-1);
        }


        if (config_setting_lookup_int(config_render, "color_1", (int *) &render->color_1) != CONFIG_TRUE)
        {
            render->color_1 = 0xeeeeee;
        }

        if (config_setting_lookup_int(config_render, "color_2", (int *) &render->color_2) != CONFIG_TRUE)
        {
            render->color_1 = 0x111111;
        }
}

void free_render(Render* render)
{
    free(render->cut_directions);
    free(render->cut_levels);
}
