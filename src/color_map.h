#ifndef COLOR_MAP_H_INCLUDED
#define COLOR_MAP_H_INCLUDED

void init_color_map();
unsigned int get_color_acid(unsigned int i, unsigned int n);
unsigned int get_color_grad_rgb(unsigned int i, unsigned int n, unsigned int start_rgb, unsigned int end_rgb);

#endif // COLOR_MAP_H_INCLUDED
