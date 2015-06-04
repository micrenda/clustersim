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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <libconfig.h>
#include <ctype.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <omp.h>
#include "common.h"
#include "le.h"
#include "render.h"
#include "test.h"
#include "color_map.h"
#include "graph.h"
#include "avrami.h"

void err_config(config_t* config);
void lower_string(char* s);
void print_help(char* exe_name);
void check_lua_error(char** lua_msg);
void mark_space(SpacePixel* space, unsigned int current_time, unsigned long position_encoded, Cluster* cluster, CommonStatus* common_status);

ssize_t readlink(const char * restrict path, char * restrict buf, size_t bufsiz);
char *dirname(char *path);
char *basename(char *path);
char *getcwd(char *buf, size_t size);

int recursive_mkdir(const char *dir);

int main(int argc, char *argv[])
{
//Disabling for now
//pragma pomp inst init pragma
	char exe_fullpath[PATH_MAX] = "";
	char exe_path[PATH_MAX] = "";
	char exe_name[PATH_MAX] = "";
	readlink("/proc/self/exe", exe_fullpath, sizeof(exe_fullpath)-1);
	strcpy(exe_path, dirname(exe_fullpath));
	strcpy(exe_name, basename(exe_fullpath));
	
    short test_flag = 0;
    short debug_flag = 0;
    short help_flag = 0;
    short keep_png_flag = 0;
    
    unsigned int num_threads = 1;
    unsigned int repeats = 1;
    
    char video_config_encoder[256] = "libx264";		
    char video_config_ext[256]     = "mp4";

    char base_directory[PATH_MAX];
    getcwd(base_directory, PATH_MAX);
    


    int flag;
    static struct option long_options[] = {
        {"test",     0, 0, 't'},
        {"debug",    0, 0, 'd'},
        {"threads",  1, 0, 'j'},
        {"repeat",   1, 0, 'r'},
        {"ffmpeg-encoder",   1, 0, '1'},
        {"keep-png", 0, 0, '2'},
        {"help",     0, 0, 'h'},
        {"output_dir", 1, 0, 'o'},
        {NULL,       0, NULL, 0}
    };
    int option_index = 0;
    while ((flag = getopt_long(argc, argv, "htdg:o:1:2j:r:", long_options, &option_index)) != -1)
    {
        switch (flag)
        {
        case 't':
            test_flag = 1;
            break;
        case 'd':
            debug_flag = 1;
            break;
        case '1':
            printf("encoder: %s\n", optarg);
            strcpy(video_config_encoder, optarg);
            break;
        case '2':
            keep_png_flag = 1;
            break;
        case 'o':
            strcpy(base_directory, optarg);
            break;
        case 'h':
            print_help(exe_name);
            exit(0);
            break;
        case 'j':
			num_threads = atoi(optarg);
			break;
        case 'r':
			repeats = atoi(optarg);
			break;
        case '?':
            print_help(exe_name);
            exit(-1);
            break;
        default:
            printf ("?? getopt returned character code 0%o ??\n", flag);
            exit(-1);
            break;
        }
    }

    if (help_flag)
    {
        print_help(exe_name);
        exit(0);
    }

    if (test_flag)
    {
        exit(test_everything());
    }
    
    if (num_threads >= 1)
	{
		omp_set_num_threads(num_threads);
		printf("Max number of threads: %u.\n", num_threads);
	}
	else
	{
		printf("The <num_threads> parameters specified with option -j must be not smaller than 1.\n");
		exit(-1);
	}
	
	if (repeats > 1)
	{
		printf("Simulations repeated %u times.\n", repeats);
	}

	if (strcmp(base_directory, exe_path) == 0)
	{
		sprintf(base_directory, "%s/output", exe_path);
	}


	if (debug_flag)
	{
	printf("Exe path: %s\n", exe_path);	
	printf("Exe name: %s\n", exe_name);	
	}

    unsigned int config_files_count = argc - optind;
    if (config_files_count == 0)
    {
        printf("No config file was provided.\n\n");
        print_help(exe_name);
        exit(-1);
    }

    char* config_files[config_files_count];

    for (int opt_i = optind; opt_i < argc; opt_i++)
    {
        config_files[opt_i-optind] = argv[opt_i];
    }


    char config_full_path[256] = {};

    char* cwd = NULL;
    cwd = getcwd(cwd, 0);

	#pragma omp parallel for if (repeats == 1 && config_files_count >= num_threads)
    for (unsigned int cf = 0; cf < config_files_count; cf++)
    {
		#pragma omp parallel for if (repeats >= num_threads)
		for (unsigned int r = 0; r < repeats; r++)
		{
			printf("========================================\n");

			char* config_file_name = config_files[cf];
			strcpy (config_full_path, "");

			if (config_file_name[0] != '/')
			{
				strcat (config_full_path, cwd);
				strcat (config_full_path, "/");
			}

			strcat (config_full_path, config_file_name);



			printf("Reading file: %s\n", config_full_path);


			// reading config filed_ratio_length
			config_t *config = malloc(sizeof(config_t));
			config_init(config);

			// Read the file. If there is an error, report it and exit.
			if (config_read_file(config, config_full_path) != CONFIG_TRUE)
			{
				const char *error_file = config_error_file(config);
				int  error_line = config_error_line(config);
				const char *error_text = config_error_text(config);

				printf("ERROR - Error parsing cfg file: %s\n", config_full_path);
				printf("%s:%d - %s\n", error_file, error_line, error_text);

				err_config(config);
			}

			config_setting_t  *config_sim 	= config_lookup(config, "simulation");

			if (config_sim == NULL)
			{
				printf("ERROR - Unable to read the 'simulation' section in config file.\n");
				err_config(config);
			}


			const char *basename = NULL;


			if (config_setting_lookup_string(config_sim, "basename",  &basename) != CONFIG_TRUE)
			{
				printf("ERROR - No 'basename' setting in configuration file.\n");
				err_config(config);
			}

			// It contains how many dimension the space has.
			// 1   means we are working in 1D space (a segment)
			// 2   means we are working in 2D space (a rectangle)
			// 3   means we are working in 3D space (a box)
			// > 3 means we are working in nD space
			unsigned short cfg_dimensions;

			const char* dimensions_string;

			if (config_setting_lookup_string(config_sim, "dimensions",  &dimensions_string) != CONFIG_TRUE)
			{
				printf("ERROR - No 'dimensions' setting in configuration file.\n");
				err_config(config);
			}


			sscanf(dimensions_string, "%hu", &cfg_dimensions);

			if (cfg_dimensions < 1)
			{
				printf("ERROR - 'dimensions' must be bigger than 0\n");
				err_config(config);
			}


			// Time frames to simulate
			unsigned int duration;

			if (config_setting_lookup_int(config_sim, "duration", (int*) &duration) != CONFIG_TRUE)
			{
				printf("ERROR - No 'duration' setting in configuration file.\n");
				err_config(config);
			}

			// Stop when the volume is filled up to 100%
			short  stop_enabled = 0;
			double stop_when_volume_is = 1.d;

			if (config_setting_lookup_float(config_sim, "stop_when_volume_is", &stop_when_volume_is) == CONFIG_TRUE)
			{
				stop_enabled = 1;
			}


			// Get the volume limits to calculated avrami coefficients (NB: this values is a percentual)
			double avrami_fit_min_volume = 0.0;
			double avrami_fit_max_volume = 1.0;
			
			config_setting_lookup_float(config_sim, "avrami_fit_min_volume", &avrami_fit_min_volume);
			config_setting_lookup_float(config_sim, "avrami_fit_max_volume", &avrami_fit_max_volume);


			// Define the size of the space.
			unsigned int space_sizes[cfg_dimensions];


			config_setting_t* space_sizes_config = config_setting_get_member(config_sim, "container_size");

			if (space_sizes_config != NULL)
			{
				if (config_setting_length(space_sizes_config)  == cfg_dimensions)
				{
					for (unsigned short d = 0; d < cfg_dimensions; d++)
					{
						space_sizes[d] = config_setting_get_int_elem(space_sizes_config, d);
					}
				}
				else
				{
					printf("ERROR - 'container_size' must have %d elements.\n", cfg_dimensions);
					err_config(config);
				}
			}
			else
			{
				printf("ERROR - No 'container_size' setting in configuration file.\n");
				err_config(config);
			}

			// Initialize the common module, to be able t encode/decode positions
			CommonStatus* common_status = init_common(cfg_dimensions, space_sizes, duration);

			// This big array contains the n-dimensional space. Every element of the array represent
			// a pixel. Every pixed (32bit) is the id of the group it belong to.
			// A function will take care to translate a x,y,z coordinates to the element of the space
			SpacePixel* space = malloc(common_status->space_volume * sizeof(SpacePixel));

			printf("Memory allocation: %.3f MBytes (%lu bytes/px x %lu)\n", 1.0 * common_status->space_volume * sizeof(SpacePixel) / (1024 * 1024), sizeof(SpacePixel), common_status->space_volume);

			// all location are free at the beginning
			for (unsigned int p = 0; p < common_status->space_volume; p++)
			{
				SpacePixel* pixel = &space[p];
				pixel->cluster = NULL;
				pixel->fill_time       = UINT_MAX;
				pixel->fill_neighbours = 0;
			}


			// Formula to be used to calculate the cluster to be created at any time frame
			//
			// The variable t is replaced with the current time frame.
			// The variable s is replaced with the duration.
			// The variable d is replaced with dimensions of the system (1 => 1D, 2 => 2D, etc.).
			//
			// EXAMPLE:
			//  To create 10 new points only at beginning:
			//  "if t = 0 then return 10 else return 0 end;"
			//
			//  To create 5 points at every time frame:
			//  "return 5;"
			const char* cluster_creation_func;

			if (config_setting_lookup_string(config_sim, "cluster_creation_func", &cluster_creation_func)  != CONFIG_TRUE)
			{
				printf("ERROR - No 'cluster_creation_func' setting in configuration file.\n");
				err_config(config);
			}

			// Formula to be used to calculate how much how much to grow every cluster at a give time
			// The variable i is replaced with the current cluster id.
			// The variable t is replaced with the current time frame.
			// The variable s is replaced with the total duration.
			// The variable r is replaced with the current cluster radius.
			// The variable v is replaced with the current cluster volume.
			// The variable c is replaced with the current cluster creation time frame (0,1,...).
			// The variable d is replaced with dimensions of the system (1 => 1D, 2 => 2D, etc.).
			//
			// EXAMPLE:
			//  To grow linear with 5 pixels:
			//  return 5;
			//
			//  To grow only up to a given radius 50:
			//  "if r <= 50 then return 2 else return 0 end;"
			//
			//  To grow half of the clusters with a speed and another half with another speed
			//  "if i % 2 == 0 then return 2 else return 3 end;"
			const char* cluster_grow_func;

			if (config_setting_lookup_string(config_sim, "cluster_grow_func", &cluster_grow_func)  != CONFIG_TRUE)
			{
				printf("ERROR - No 'cluster_grow_func' setting in configuration file.\n");
				err_config(config);
			}

			// Formula to be used to calculate where to positionate the cluster created at every iteration
			// In our case we have two possibity.
			// 1. To use a generic formula for all axes
			// 2. To specify the formula for every axis
			//
			// It is possible to specify only one of the formula. It no formula is provided then
			// we positionate the new clusters randomly in the space
			//
			// Whatever we choose, these replacing will be done:
			// The variable i is replaced with the current cluster id.
			// The variable j is replaced with the a counter that indicate the inserting order (start from 0 and is resetted at every timeframe).
			// The variable t is replaced with the current time frame.
			// The variable s is replaced with the total duration.
			// The variable w is replaced with the container size in the current dimension.
			// The variable d is replaced with the dimensions of the system (1 => 1D, 2 => 2D, etc.).

			const char* cluster_position_gene_func = NULL;
			
			const char* cluster_position_axis_func[common_status->dimensions];
			for(unsigned short d = 0; d < common_status->dimensions; d++)
				cluster_position_axis_func[d] = NULL;

			if (config_setting_lookup_string(config_sim, "cluster_position_func", &cluster_position_gene_func)  != CONFIG_TRUE)
			{
				for (unsigned short d = 0; d < common_status->dimensions; d++)
				{
					char func_name[256];
					char axis_label[8];
					dimension_to_label(axis_label, common_status, d);
					sprintf(func_name, "cluster_position_func_%s", axis_label);
					cluster_position_axis_func[d] = NULL;
					config_setting_lookup_string(config_sim, func_name, &cluster_position_axis_func[d]);
				}
			}


			typedef enum {GENERAL, AXIS, RANDOM} position_strategry_type;
			position_strategry_type position_strategry;


			if (cluster_position_gene_func != NULL && cluster_position_gene_func[0] != '\0')
				position_strategry = GENERAL;
			else
			{
				short all = 1;
				short some = 0;

				for (int d = 0; d < common_status->dimensions; d++)
				{
					all  &= cluster_position_axis_func[d] != NULL && cluster_position_axis_func[d][0] != '\0';
					some |= cluster_position_axis_func[d] != NULL && cluster_position_axis_func[d][0] != '\0';
				}

				if (some == 1 && all == 1)
					position_strategry = AXIS;
				else if (some == 1 && all == 0)
				{
					for (int e = 0; e < common_status->dimensions; e++)
					{
						char axis_label[8];
						dimension_to_label(axis_label, common_status, e);
						printf("Unble to find the cluster_position_func_%s config element.\n", axis_label);
					}
					exit(-1);
				}
				else
					position_strategry = RANDOM;
			}


			// Reading render settings
			char render_id[256] = {};

			unsigned int render_count = 0;
			sprintf(render_id, "render_%u", render_count+1);
			while(config_lookup(config, render_id) != NULL)
			{
				render_count++;
				sprintf(render_id, "render_%u", render_count+1);
			}

			// Parsing render settings
			Render renders[render_count];
			for (unsigned int i = 0; i < render_count; ++i)
			{
				sprintf(render_id, "render_%u", i+1);

				config_setting_t* config_render = config_lookup(config, render_id);
				if (config_render != NULL)
				{
					parse_render(common_status, &renders[i], config_render);
				}
			}

			// Loading LUA common functions
			char common_func_id[256];
			const char* buffer_common_func = NULL;
			int common_funcs_count = 0;
			sprintf(common_func_id, "common_func_%u", common_funcs_count+1);
			while(config_setting_lookup_string(config_sim, common_func_id, &buffer_common_func) == CONFIG_TRUE)
			{
				common_funcs_count++;
				sprintf(common_func_id, "common_func_%u", common_funcs_count+1);
			}

			const char *common_funcs[common_funcs_count];

			// Parsing render settings
			for (unsigned int f = 0; f < common_funcs_count; ++f)
			{
				sprintf(common_func_id, "common_func_%u", f+1);
				config_setting_lookup_string(config_sim, common_func_id, &common_funcs[f]);
			}


			// ATTENTION
			// When we are here we are sure that the config file was correctly parsed

			// Creating output directory

			char output_directory[256] = {};
			unsigned int u = 1;

			int status_mkdir = 0;
			do
			{
				sprintf(output_directory, "%s/%s_run%u", base_directory, basename, u);
				status_mkdir = recursive_mkdir(output_directory);

				if (status_mkdir == 0)
				{
					printf("Created directory: %s\n", output_directory);
					break; // directory created;
				}
				else
				{
					if (errno != EEXIST)
					{
						printf("ERROR - Unable to create the directory '%s'. Command mkdir returned: %s\n", output_directory, strerror(errno));
						err_config(config);
						exit(-2);
					}
				}
				u++;

			} while(status_mkdir != 0);


			// Copying out config file to params.cfg so we have a copy of the parameters used
			FILE *config_file_src, *config_file_dest;

			config_file_src = fopen(config_full_path, "r");
			if (config_file_src == NULL)
			{
			  printf("ERROR - Can not to open config file: %s", config_full_path);
			  exit(1);
			}

			char config_file_dest_filename[256];
			sprintf(config_file_dest_filename, "%s/%s", output_directory, "parameters.cfg");

			config_file_dest = fopen(config_file_dest_filename, "w");
			if (config_file_dest == NULL)
			{
			  printf("ERROR - Can not to open config file: %s", config_full_path);
			  fclose(config_file_src);
			  exit(1);
			}

			char a;
			do
			{
				a = fgetc(config_file_src);
				if (a != EOF) fputc(a, config_file_dest);
			} while (a != EOF);


			fclose(config_file_src);
			fclose(config_file_dest);



			// Setting the render output directory
			for (unsigned int i = 0; i < render_count; ++i)
			{
				Render* render = &renders[i];

				if (render->name[0] == '\0')
					sprintf(render->output_directory, "%s/render_%d", output_directory, i+1);
				else
					sprintf(render->output_directory, "%s/render_%s", output_directory, render->name);

				int status_mkdir = recursive_mkdir(render->output_directory);

				if (status_mkdir != 0)
				{
					printf("ERROR - Unable to create the directory '%s'. Command mkdir returned: %s\n", output_directory, strerror(errno));
					err_config(config);
					exit(-2);
				}
			}

			// Opening CSV file for output of growing summary
			char csv_filename_grow[256];
			sprintf(csv_filename_grow, "%s/grow_summary.csv", output_directory);

			FILE *csv_grow_file = fopen(csv_filename_grow, "w");
			if (csv_filename_grow == NULL)
			{
				printf("ERROR - Error opening file '%s'\n", csv_filename_grow);
				err_config(config);
			}

			fprintf(csv_grow_file, "#time,new_clusters_asked,new_clusters_created,clusters_total,volume_grow,volume_total,volume_totale_perc\n");


			le_init();
			init_color_map();
			
			AvramiModel model;
			
			model.last_cluster_creation 	= 0;
			model.last_cluster_grow 		= 0;
			
			model.stat_creation_zero 		= 0;
			model.stat_creation_equal 		= 0;
			model.stat_creation_not_equal	= 0;
			
			model.stat_grow_zero 		= 0;
			model.stat_grow_equal 		= 0;
			model.stat_grow_not_equal	= 0;


			// Initialize the values of the cluster to create at every iteration;
			unsigned int clusters_to_create[duration];
			unsigned int max_clusters_count = 0;


			char *lua_msg = NULL; // This variable contains all lua error messages

			for (unsigned int f = 0; f < common_funcs_count; f++)
			{
				int cookie_common_func = le_loadexpr((char*)common_funcs[f], &lua_msg);
				check_lua_error(&lua_msg);
				le_eval(cookie_common_func, &lua_msg);
				check_lua_error(&lua_msg);
			}


			int cookie_creation = le_loadexpr((char*)cluster_creation_func, &lua_msg);
			check_lua_error(&lua_msg);
			int cookie_grow     = le_loadexpr((char*)cluster_grow_func,     &lua_msg);
			check_lua_error(&lua_msg);


			int cookie_position_gene = 0;

			if (position_strategry == GENERAL)
			{
				cookie_position_gene = le_loadexpr((char*)cluster_position_gene_func,     &lua_msg);
				check_lua_error(&lua_msg);
			}


			int cookie_position_axis[common_status->dimensions];
			if (position_strategry == AXIS)
			{
				for (int d = 0; d < common_status->dimensions; d++)
				{
					cookie_position_axis[d] = le_loadexpr((char*)cluster_position_axis_func[d], &lua_msg);
					check_lua_error(&lua_msg);
				}
			}

			for (unsigned int t = 0; t < duration; ++t)
			{
				le_setvar("d",common_status->dimensions);
				le_setvar("t",t);
				le_setvar("s",duration);

				int cnt =  le_eval_integer(cookie_creation, &lua_msg);
				check_lua_error(&lua_msg);

				if (cnt < 0)
				{
					printf("ERROR - LUA script '%s' at t=%u returned a value lower than %u. Returned value: %d", "cluster_creation_func", t, 0, cnt);
					exit(-3);
				}

				clusters_to_create[t] = cnt;
				max_clusters_count += cnt;
				
				register_cluster_creation(&model, cnt);
			}
			
			// Contain the list of clusters we created
			// The id of every cluster must be the same of the position in the array.
			unsigned int clusters_count = 0;
			Cluster clusters[max_clusters_count];

			// This keep trace of the cluster really created at every time iteration (if we create a cluster where one was existing, then we jump it)
			unsigned int clusters_created[duration];
			
			// Initialize random seed
			time_t tt;
			srand((unsigned) time(&tt));

			printf("\n");
			// Now we start to dance, starting simulation
			for (unsigned int t = 0; t < duration; ++t)
			{
				clusters_created[t] = 0;
				common_status->stat_pixel_grow[t] = 0;

				for (unsigned int c = 0; c < clusters_to_create[t]; ++c)
				{
					// position in space
					unsigned int coordinates[common_status->dimensions];

					for (unsigned int d = 0; d < common_status->dimensions; ++d)
					{
						if (position_strategry == GENERAL || position_strategry == AXIS)
						{
							int cookie_position = position_strategry == AXIS ? cookie_position_axis[d] : cookie_position_gene;

							le_setvar("i",clusters_count);
							le_setvar("j",clusters_created[t]);
							le_setvar("t",t);
							le_setvar("s",duration);
							le_setvar("w",common_status->space_sizes[d]);
							le_setvar("d",common_status->dimensions);

							coordinates[d] = le_eval_integer(cookie_position, &lua_msg);
							check_lua_error(&lua_msg);

							if (coordinates[d] >= common_status->space_sizes[d])
							{
								printf("ERROR - LUA script '%s' at t=%u returned a value not between %u and %u. Returned value: %u", "cluster_position_func", t, 0, common_status->space_sizes[d], coordinates[d]);
								exit(-3);
							}
						}
						else
							coordinates[d] = rand() % common_status->space_sizes[d];
					}

					// Critical moment: is the space position already occupied by another cluster (if we are in Avrami mode we don't take care)
					unsigned long position_encoded = encode_position_cartesian(common_status, coordinates);

					if (space[position_encoded].cluster == NULL)
					{
						// Location is free, creating a new cluster
						unsigned int id = clusters_count++;
						Cluster* cluster = &clusters[id];
						// Initializing all the fields
						cluster->id = id;
						cluster->creation_time = t;
						cluster->radius = 1;
						cluster->center = position_encoded;
						cluster->volume  = 1;
						cluster->growing = 1;

						

						clusters_created[t]++;
						
						
						mark_space(space, t, position_encoded, cluster, common_status);
					}
				}

				// growing the clusters
				unsigned int clusters_grows[clusters_count];
				for (unsigned int c = 0; c < clusters_count; c++) clusters_grows[c] = 0;
				
				unsigned int max_grow = 0;

				for (unsigned int c = 0; c < clusters_count; ++c)
				{
					Cluster* cluster = &clusters[c];
					if (cluster->growing && cluster->creation_time < t)
					{
						le_setvar("d",common_status->dimensions);
						le_setvar("t",t);
						le_setvar("s",duration);
						le_setvar("c",cluster->creation_time);
						le_setvar("i",cluster->id);
						le_setvar("r",cluster->radius);
						le_setvar("v",cluster->volume);
						
						int grw = le_eval_integer(cookie_grow, &lua_msg);

						if (grw < 0)
						{
							printf("ERROR - LUA script '%s' at t=%u returned a value lower than %u. Returned value: %d", "cluster_grow_func", t, 0, grw);
							exit(-3);
						}

						clusters_grows[c] =  grw;
						check_lua_error(&lua_msg);

						if (clusters_grows[c] > max_grow)
							max_grow = clusters_grows[c];
							
						register_cluster_grow(&model, grw);
					}
				}
				
				for (unsigned int g = 1; g <= max_grow; g++)
				{
					#pragma omp parallel for shared(space,common_status)
					for (unsigned long p = 0; p < common_status->space_volume; p++)
					{
						SpacePixel* space_pixel = &space[p];
						if (space_pixel->fill_neighbours > 0 && space_pixel->cluster == NULL)
						{
							unsigned int p_decoded[common_status->dimensions];
							decode_position_cartesian(common_status, p_decoded, p);

							for (unsigned int c = 0; c < clusters_count; ++c)
							{
								Cluster* cluster = &clusters[c];
								
								unsigned int center_decoded[common_status->dimensions];
								decode_position_cartesian(common_status, center_decoded, cluster->center);
								
								if (g <= clusters_grows[c] && calculate_distance(common_status, center_decoded, p_decoded) < cluster->radius + g && space_pixel->cluster == NULL)
								{
									// Checking if there is a near point of the same cluster
									short found = 0;

									unsigned int adjacent_points[common_status->adjacents_count][common_status->dimensions];
									get_adjacents_points(common_status, p_decoded, adjacent_points);

									for (unsigned int a = 0; a < common_status->adjacents_count; a++)
									{
										if (is_inside(common_status, adjacent_points[a]))
										{
											unsigned long adjacent_encoded = encode_position_cartesian(common_status, adjacent_points[a]);
											SpacePixel* adjacent_pixel = &space[adjacent_encoded]; 
											if (adjacent_pixel->cluster != NULL && adjacent_pixel->cluster == cluster)
											{
												found = 1;
												break;
											}
										}
									}
									
									
									if (found)
									{
										#pragma omp critical
										{
											mark_space(space, t, p, cluster, common_status);
										}
									}
								}
							}
						}
					}
				}
				
				for (unsigned int c = 0; c < clusters_count; ++c)
				{
					Cluster* cluster = &clusters[c];
					cluster->radius += clusters_grows[c];
				}


				//// We grow all the cluster one by one. So there is no cluster who get a avantage
				//for (unsigned int g = 1; g <= max_grow; g++)
				//{
					
					//#pragma omp parallel for shared(space,common_status)
					//for (unsigned int c = 0; c < clusters_count; ++c)
					//{
						//Cluster* cluster = &clusters[c];
						//if (cluster->growing && cluster->creation_time < t && g <= clusters_grows[c])
						//{
							//// searching all the point that are between radius and radius + grow and
							//// if they are free, associating to the current cluster

							//unsigned int cluster_center[common_status->dimensions];
							//decode_position_cartesian(common_status, cluster_center, cluster->center);

							//unsigned int r = cluster->radius + 1;

							//unsigned int surface_point_count = get_surface_points_count(common_status, r);
							//short found_growing_points = 0;

							//for (unsigned int s = 0; s < surface_point_count; s++)
							//{
								//unsigned int new_point_radius = r;
								//double new_point_angles[common_status->dimensions - 1];
								//decode_position_polar(common_status, new_point_angles, new_point_radius, s);

								//int new_point_relative_coordinates[common_status->dimensions];
								//convert_polar_angles_to_cartesian(common_status, new_point_angles, new_point_radius/* - 1*/, new_point_relative_coordinates);

								//unsigned int new_point_coordinates[common_status->dimensions];
								//add_relative_vector(common_status, new_point_coordinates, cluster_center, new_point_relative_coordinates);
								//// We ignore the points outside the space
								//if (is_inside(common_status, new_point_coordinates))
								//{
									//unsigned long new_point_coordinates_encoded = encode_position_cartesian(common_status, new_point_coordinates);

									//// Checking if the point is occupied by another cluster or not
									//if (space[new_point_coordinates_encoded] == UINT_MAX)
									//{
										//// The point is free.
										//// Checking if there is an adiacent pixel of the same cluster
										//short found = 0;

										//unsigned int adjacent_points[common_status->adjacents_count][common_status->dimensions];
										//get_adjacents_points(common_status, new_point_coordinates, adjacent_points);

										//for (unsigned int a = 0; a < common_status->adjacents_count; a++)
										//{

											//if (is_inside(common_status, adjacent_points[a]))
											//{
												//unsigned long adjacent_encoded = encode_position_cartesian(common_status, adjacent_points[a]);

												//if (space[adjacent_encoded] == cluster->id)
												//{
													//found = 1;
													//break;
												//}
											//}
										//}

										
										//if (found)
										//{
											//#pragma omp critical
											//{
												////Ok, we can grow on this pixel
												//cluster->volume++;
												//found_growing_points = 1;
												
												//if (space[new_point_coordinates_encoded] == UINT_MAX)
												//{
													//common_status->stat_pixel_grow[t]++;
													//common_status->stat_pixel_grow_total++;
												//}
												//space[new_point_coordinates_encoded] = cluster->id;
											//}
										//}
									//}
								//}
							//}

							
							//if (found_growing_points)
							//{
								//cluster->radius = r;
							//}
							//else
							//{
								//// There was no point available in the surface of the cluster
								//// Setting as not growing so we will not grow anymore this cluster
								//cluster->growing = 0;
							//}
							
						//}
					//}
				//}



				// rendering
				#pragma omp parallel for
				for (unsigned r = 0; r < render_count; r++)
				{
					render(common_status, &renders[r], space, clusters, clusters_count, t, duration, renders[r].output_directory);
				}
				
				double volume_perc = 100.d * common_status->stat_pixel_grow_total / common_status->space_volume;
				printf("\033[FCalculated time frame %u of %u (volume: % 3.2f%%)\n", t+1, duration, volume_perc);

				if (stop_enabled && common_status->stat_pixel_grow_total >= stop_when_volume_is * common_status->space_volume)
				{
					printf("\nCluster volume is %f%% of total volume. Stopping.\n", volume_perc);
					break;
				}

				// writing CSV
				fprintf(csv_grow_file, "%u,%u,%u,%u,%u,%lu,%f\n",
						t,
						clusters_to_create[t],
						clusters_created[t],
						clusters_count,
						common_status->stat_pixel_grow[t],
						common_status->stat_pixel_grow_total,
						1.d * common_status->stat_pixel_grow_total / common_status->space_volume);
						
				fflush(csv_grow_file);
			}


			/* 
			 * Executing sanity checks
			 * Now we check for every pixel in space that there is no point where these conditions are not meet:
			 * 
			 * 1) It is not assigned to any cluster
			 * 2) The distance between them and the cluster center is less than cluster radius
			 * 3) There is a 1st order neighbor assigned to the same cluster
			 * 
			 * It all these condition are met then it means that the growing algoritm has a problem and the results are unreliable
			 * 
			 */
			 
			printf("Executing pixel sanity checks ...\n");
			unsigned long unhealth_pixels = 0;
			unsigned long check_grow_pixels = 0;
			 
			#pragma omp parallel for shared(unhealth_pixels, check_grow_pixels)
			for (unsigned long p = 0; p < common_status->space_volume; p++)
			{
				if (space[p].cluster == NULL)
				{
					// The pixed is free
					unsigned int p_decoded[common_status->dimensions];
					decode_position_cartesian(common_status, p_decoded, p);
					
					for (unsigned int c = 0; c < clusters_count; c++)
					{
						Cluster* cluster = &clusters[c];
						unsigned int center_decoded[common_status->dimensions];
						decode_position_cartesian(common_status, center_decoded, cluster->center);
						
						if (calculate_distance(common_status, p_decoded, center_decoded) < (cluster->radius - 3))
						{
							// The pixel is in the range of the cluster
							
							// Checking if there is an adiacent pixel of the same cluster
							short found = 0;

							unsigned int adjacent_points[common_status->adjacents_count][common_status->dimensions];
							get_adjacents_points(common_status, p_decoded, adjacent_points);

							for (unsigned int a = 0; a < common_status->adjacents_count; a++)
							{
								if (is_inside(common_status, adjacent_points[a]))
								{
									unsigned long adjacent_encoded = encode_position_cartesian(common_status, adjacent_points[a]);
									if (space[adjacent_encoded].cluster == cluster)
									{
										found = 1;
										break;
									}
								}
							}

							
							if (found)
							{
								#pragma omp atomic
								unhealth_pixels++;
								
								if (debug_flag)
								{
									#pragma omp critical
									{
										printf("Found unassigned pixel: ");
										printf("(");
										
										for (unsigned short d = 0; d < common_status->dimensions; d++)
										{
											if (d!=0) printf(", ");
											printf("%u", p_decoded[d]);
										}
										printf(")\n");
									}
								}
								break; // No need to check for other clusters
							}
						}
					}
				}
				else
				{
					#pragma omp atomic
					check_grow_pixels++;
				}
			}
			
			if (check_grow_pixels != common_status->stat_pixel_grow_total)
				printf("WARNING 1/2: in variable 'common_status->stat_pixel_grow_total' we have %lu filled pixels but a final check resulted that we have %lu filled pixels. Please check the code.\n", common_status->stat_pixel_grow_total, check_grow_pixels);
			else
				printf("PASSED 1/2: filled pixel count check passed.\n");
			
			if (unhealth_pixels > 0)
			{
				printf("WARNING 2/2: %lu unassigned pixels was found inside the radius of a cluster with a neighbor of the same cluster. This means the algorithm used to grows the clusters is not 100%% correct. The unhealth pixes are %lu of %lu (%.2f%%)\n",
					unhealth_pixels,
					unhealth_pixels,
					common_status->stat_pixel_grow_total,
					100.d * unhealth_pixels / common_status->stat_pixel_grow_total);
			}
			else
				printf("PASSED 2/2: unassigned pixel check passed.\n");
			


			char csv_filename_clusters[256];
			sprintf(csv_filename_clusters, "%s/clusters_details.csv", output_directory);

			FILE *csv_clusters_file = fopen(csv_filename_clusters, "w");
			if (csv_clusters_file == NULL)
			{
				printf("ERROR - Error opening file '%s'\n", csv_filename_clusters);
				err_config(config);
			}


			fprintf(csv_clusters_file, "#id,creation_time,radius,volume,volume_perc");
			for (unsigned short d = 0; d < common_status->dimensions; d++)
			{
				char axis_label[8];
				dimension_to_label(axis_label, common_status, d);
				fprintf(csv_clusters_file, ",center_%s", axis_label);
			}

			fprintf(csv_clusters_file, "\n");

			for (unsigned int c = 0; c < clusters_count; c++)
			{
				Cluster* cluster = &clusters[c];

				fprintf(csv_clusters_file, "%u,", cluster->id);
				fprintf(csv_clusters_file, "%u,", cluster->creation_time);
				fprintf(csv_clusters_file, "%u,", cluster->radius);
				fprintf(csv_clusters_file, "%lu,", cluster->volume);
				fprintf(csv_clusters_file, "%f,", 1.d * cluster->volume / common_status->space_volume);
				
				unsigned int center[common_status->dimensions];
				decode_position_cartesian(common_status, center, cluster->center);
				for (unsigned short d = 0; d < common_status->dimensions; d++)
					fprintf(csv_clusters_file, "%u,", center[d]);
				
				fprintf(csv_clusters_file,"\n");
			}

			fclose(csv_clusters_file);
			fclose(csv_grow_file);


			const char* video_config_executable;  // ffmpeg
			
			// Checking which ffmpeg command is available (Debian uses avconv while other distros use ffmpeg)
			if (system("avconv -h > /dev/null 2> /dev/null") == 0)
			{
				video_config_executable = "avconv";
			}
			else if (system("ffmpeg -h > /dev/null 2> /dev/null") == 0)
			{
				video_config_executable = "ffmpeg";
			}
			else
			{
				video_config_executable = "ffmpeg";
				printf("WARNING: Unable to find 'ffmpeg' command. The video creation will be disabled.\n");	
			}


			for (unsigned r = 0; r < render_count; r++)
			{
				Render* render = &renders[r];

				if (render->type == R_2D)
				{
					if (duration < 5)
						printf("WARNING - The duration is %d time units but the video require %d frame per seconds: ffmpeg could not run properly.\n", duration, 5);

					// We ensure the max size does not exceed full hd videos
					unsigned int w,h;
					unsigned int orig_w = common_status->space_sizes[render->axis_1];
					unsigned int orig_h = common_status->space_sizes[render->axis_2];
					
					if (1.d * orig_w / orig_h >= 16.d/9.d)
					{
						if (orig_w > 1920)
						{
							w = 1920;
							h = (orig_h * w / orig_w / 2) * 2; // Ensure we have an even number
						}
						else
						{
							w = (orig_w / 2) * 2;
							h = (orig_h / 2) * 2;
						}
					}
					else
					{
						if (orig_h > 1080)
						{
							h = 1080;
							w = (orig_w * h / orig_h / 2) * 2; // Ensure we have an even number
						}
						else
						{
							h = (orig_h / 2) * 2;
							w = (orig_w / 2) * 2;
						}
					}
					 
					
					char ffmpeg_cmd[256];
					sprintf(ffmpeg_cmd, "%s -loglevel error -framerate 5 -i %s/frame_%%06d.png -vf scale=\"%u:%u\" -c:v %s -r 30 %s/%s.%s",
						video_config_executable,
						render->output_directory,
						w,
						h,
						video_config_encoder,
						output_directory,
						render->name,
						video_config_ext);

					
					printf("Running ffmpeg for 'render_%d':\t", r + 1);
					if (debug_flag)
						printf("%s\n", ffmpeg_cmd);
					
					int status = system(ffmpeg_cmd);
					if (status == 0)
					{
						if (!debug_flag)
							printf("DONE\n");
						
						if (!keep_png_flag)
						{
							// Deleting PNG files
							char del_cmd[256];
							sprintf(del_cmd, "rm -r '%s'", render->output_directory);
							system(del_cmd);
						}
					}
					else
					{
						printf("ERROR (%d)\n", status);
						printf("________________________________________\n");
						printf("Failed command:\n%s\n", ffmpeg_cmd);
						printf("________________________________________\n");
					}
				}
			}


			char csv_filename_grow_log[256];
			sprintf(csv_filename_grow_log, "%s/grow_summary_log.csv", output_directory);

			double  min_t, max_t, fit_n, fit_k, theo_n, theo_k;
			compute_avrami(csv_filename_grow, csv_filename_grow_log, avrami_fit_min_volume, avrami_fit_max_volume, &min_t, &max_t, &fit_n, &fit_k, &theo_n, &theo_k, &model, common_status);
			
			char csv_filename_stats[256];
			sprintf(csv_filename_stats, "%s/stats.csv", output_directory);
			
			FILE* file_stats = fopen(csv_filename_stats, "w");
			fprintf(file_stats, "# basename, dimensions, volume_space, volume_fill, clusters, fit_n, fit_k, theo_n, theo_k\n");
			fprintf(file_stats, "%s,",  basename);
			fprintf(file_stats, "%u,",  common_status->dimensions);
			fprintf(file_stats, "%lu,", common_status->space_volume);
			fprintf(file_stats, "%lu,", common_status->stat_pixel_grow_total);
			fprintf(file_stats, "%u,",  clusters_count);
			fprintf(file_stats, "%.10f,",   fit_n);
			fprintf(file_stats, "%.10E,",   fit_k);
			fprintf(file_stats, "%.10f,",   theo_n);
			fprintf(file_stats, "%.10E\n",  theo_k);
			fclose(file_stats);
			
			
			
			created_graphs(output_directory, output_directory, exe_path, min_t, max_t, avrami_fit_min_volume, avrami_fit_max_volume, fit_n, fit_k, theo_n, theo_k, debug_flag);
			
			// Freeing the memory
			for (unsigned int r = 0; r < render_count; r++)
				free_render(&renders[r]);

			free(space);
			
			free_common(common_status);
			config_destroy(config);
			free(config);
		}

    }

    free(cwd);

    return 0;
}

void err_config(config_t* config)
{
    config_destroy(config);
    free(config);
    exit(-1);
}

void check_lua_error(char** lua_msg)
{
    if (*lua_msg != NULL)
    {
        printf("Error while parsing/executing LUA script at:\n%s\n", *lua_msg);
        exit(-1);
    }
}

void lower_string(char* s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        s[i] = tolower(s[i]);
        i++;
    }
}

int recursive_mkdir(const char *dir)
{
	char tmp[PATH_MAX];
	char *p = NULL;
	size_t len;

	snprintf(tmp, sizeof(tmp),"%s",dir);
	len = strlen(tmp);
	if(tmp[len - 1] == '/')
		tmp[len - 1] = 0;
	for(p = tmp + 1; *p; p++)
	{
		if(*p == '/')
		{
			*p = 0;
			mkdir(tmp, S_IRWXU);
			*p = '/';
		}
	}
	return mkdir(tmp, S_IRWXU);
}


void mark_space(SpacePixel* space, unsigned int current_time, unsigned long position_encoded, Cluster* cluster, CommonStatus* common_status)
{
	if (space[position_encoded].cluster == NULL)
	{
		common_status->stat_pixel_grow[current_time]++;
		common_status->stat_pixel_grow_total++;
		
		SpacePixel* space_pixel = &space[position_encoded];
		space_pixel->cluster = cluster;
		space_pixel->fill_time = current_time;
		
		unsigned int position_decoded[common_status->dimensions];
		decode_position_cartesian(common_status, position_decoded, position_encoded);
		
		unsigned int adjacent_points[common_status->adjacents_count][common_status->dimensions];
		get_adjacents_points(common_status, position_decoded, adjacent_points);

		for (unsigned int a = 0; a < common_status->adjacents_count; a++)
		{
			if (is_inside(common_status, adjacent_points[a]))
			{
				unsigned long encoded_adj = encode_position_cartesian(common_status, adjacent_points[a]);
				
				if (position_encoded != encoded_adj)
				{
					SpacePixel* adj_space_pixel = &space[encoded_adj];
					adj_space_pixel->fill_neighbours++;
				}
			}
		}
	}
	else
	{
		printf("INTERNAL ERROR - Tried to mark a space position already marked. Contact developer.\n");
		exit(5);
	}
}



void print_help(char* exe_name)
{
    printf("Usage:\n\n");
    printf("  %s [-o <output_dir>] [--ffmpeg-encoder <encoder>] <file1.cfg> <file2.cfg> <file3.cfg> ...\n", exe_name);
    printf("  %s -t\n", exe_name);
    printf("  %s -h\n", exe_name);
    printf("\n");
    printf("      --ffmpeg-encoder <output_dir>            Set encoder used by ffmpeg (default libx264)\n");
    printf("      --keep-png            				   Does not delete generated png files\n");
    printf("  -r  --repeat         <n>                 	   Repeat the simulation n times\n");
    printf("  -o  --output_dir     <output_dir>            Set output directory (default current working dir)\n");
    printf("  -t  --test                                   Execute internal tests\n");
    printf("  -h  --help                                   Print this help menu\n");
    printf("\n");
}

