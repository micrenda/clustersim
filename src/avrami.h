#include "common.h"

void compute_avrami(char* input_grow_summary, char* output_grow_summary_log, double min_volume, double max_volume, double* min_t, double* max_t, double* fit_n, double* fit_k, double* theo_n, double* theo_k, AvramiModel* model, CommonStatus* status);

void register_cluster_creation(AvramiModel* model, unsigned int creation);
void register_cluster_grow(AvramiModel* model, unsigned int grow);
