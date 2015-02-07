#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

void render(CommonStatus* common_status, Render* render, unsigned int space[], unsigned int space_sizes[], Cluster* clusters, unsigned int clusters_count, unsigned int t, unsigned int duration, char* output_directory);
void parse_render(CommonStatus* common_status, Render* render, config_setting_t* config_render);
void free_render(Render* render);
#endif // RENDER_H_INCLUDED
