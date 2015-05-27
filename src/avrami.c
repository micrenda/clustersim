#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common.h"
#include <gsl/gsl_multifit.h>



// Skip headers and lines with not finite values
unsigned int count_file_lines(char* filename)
{
	FILE* f = fopen(filename, "r");
	unsigned int lines = 0;
	
	int ch;
	while (EOF != (ch=getc(f)))
	{
		if (ch=='\n')
			++lines;	
	}
	
	fclose(f);
	
	return lines;
}


int polynomialfit(int obs, int degree, double *dx, double *dy, double *store) /* n, p */
{
	gsl_multifit_linear_workspace *ws;
	gsl_matrix *cov, *X;
	gsl_vector *y, *c;
	
	double chisq;
	int i, j;

	X = gsl_matrix_alloc(obs, degree);
	y = gsl_vector_alloc(obs);
	c = gsl_vector_alloc(degree);
	cov = gsl_matrix_alloc(degree, degree);

	for(i=0; i < obs; i++)
	{
		gsl_matrix_set(X, i, 0, 1.0);
		for(j=0; j < degree; j++)
			gsl_matrix_set(X, i, j, pow(dx[i], j));
		
		gsl_vector_set(y, i, dy[i]);
	}

	ws = gsl_multifit_linear_alloc(obs, degree);
	gsl_multifit_linear(X, y, c, cov, &chisq, ws);

	/* store result ... */
	for(i=0; i < degree; i++)
		store[i] = gsl_vector_get(c, i);
	

	gsl_multifit_linear_free(ws);
	gsl_matrix_free(X);
	gsl_matrix_free(cov);
	gsl_vector_free(y);
	gsl_vector_free(c);
	return 1;
	/* we do not "analyse" the result (cov matrix mainly) to know if the fit is "good" */
}

void compute_avrami(char* input_grow_summary, char* output_grow_summary_log, double min_volume, double max_volume, double* min_t, double* max_t, double* fit_n, double* fit_k, double* theo_n, double* theo_k, AvramiModel* model, CommonStatus* status)
{
	// Computing avrami theoretical models
	AvramiType type = AVRAMI_TYPE_OTHER;
	unsigned int creation = model->last_cluster_creation;
	unsigned int grow     = model->last_cluster_grow;
	
	if (model->stat_creation_not_equal == 0)
	{
		if (model->stat_creation_equal == 0)
			type = AVRAMI_TYPE_INSTANT;
		else
			type = AVRAMI_TYPE_CONSTANT;
	}
	
	// This is the volume shape factor and it is used to calculate the volume of a cristal (in this case with spherical shape) starting from one of its 
	// caracteristic dimension:
	// V = g r³
	double g_value;
	//char*  g_formula;
	
	switch (status->dimensions)
	{
		case 2:
			g_value = M_PI;
		break;
		
		case 3:
			g_value = 4 * M_PI / 3;
		break;
		
		default:
			g_value =  pow(M_PI, status->dimensions / 2.d) / exp(lgamma(1.0 + status->dimensions / 2.d));
		break;
	}
	
	switch (type)
	{
		case AVRAMI_TYPE_INSTANT:
			*theo_n = status->dimensions;
			*theo_k = g_value * creation * pow(grow, status->dimensions) / status->space_volume;
		break;
		
		case AVRAMI_TYPE_CONSTANT:
			*theo_n = status->dimensions + 1;
			*theo_k = g_value / (status->dimensions + 1) * creation * pow(grow, status->dimensions) / status->space_volume;
		break;
		
		default:
			*theo_n = 0;
			*theo_k = 1;
		break;
	}
	
	
	// Read csv line by line
	char buffer[1024];
	
	char *record,*line;
	
	
	unsigned int input_length = count_file_lines(input_grow_summary) - 1; // First line is a comment
	

	FILE *in = fopen(input_grow_summary,"r");
	
	if(in == NULL)
	{
	  printf("ERROR: Failed opening file: %s\n", input_grow_summary);
	  exit(-8);
	}
	
	FILE *out = fopen(output_grow_summary_log,"w");
	fprintf(out, "# log(t);log(-log(1-X))\n");
	
	
	double fit_log_time  [input_length];
	double fit_log_volume[input_length];
	
	// we skip the first line because it just contains a comment
	fgets(buffer,sizeof(buffer),in);
	
	*min_t =  INFINITY;
	*max_t = -INFINITY;
	
	unsigned int fit_length = 0;
	while((line=fgets(buffer,sizeof(buffer),in)) != NULL)
	{
		unsigned int i = 0;
		
		unsigned int time = 0;
		double       volume = 0;
			
		record = strtok(line, ",;");
		while(record != NULL)
		{
			
			
			switch (i)
			{
				case 0:
					time   = atoi(record);
				break;
				
				case 6:
					volume = atof(record);
				break;
			}
			
			record = strtok(NULL, ",;");
			++i;
		}
		
		if (time != 0) // We skip the first point because log(0)=-inf
		{
			double log_time   = log(time);
			double log_volume = log(-log(1-volume));
			
			fprintf(out, "%0.10f,%0.10f\n", log_time, log_volume);
			if (time > *max_t) *max_t = time;
			if (time < *min_t) *min_t = time;
			
			if (volume >= min_volume && volume <= max_volume)
			{
				// We have time and volume, calculating log values
				fit_log_time  [fit_length] 	= log_time;
				fit_log_volume[fit_length]	= log_volume;
				
				fit_length++;
			}
		}
	}
	
	
	// Calculating n and k
	if (fit_length > 0)
	{
		double coeff[2];
		polynomialfit(fit_length, 2, fit_log_time, fit_log_volume, coeff);
		
		*fit_k = exp(coeff[0]);
		*fit_n = coeff[1];	
	}
	else
	{
		*fit_k = 1;
		*fit_n = 0;	
	}
	
	fclose(out);
	fclose(in);
}



void register_cluster_creation(AvramiModel* model, unsigned int creation)
{
	if (creation == 0)
		model->stat_creation_zero++;
	else
	{
		if (model->last_cluster_creation != 0)
		{
			if (model->last_cluster_creation == creation)
				model->stat_creation_equal++;
			else
				model->stat_creation_not_equal++;
		}
		
		model->last_cluster_creation = creation;
	}
	
	
}

void register_cluster_grow(AvramiModel* model, unsigned int grow)
{
	if (grow == 0)
		model->stat_grow_zero++;
	else
	{
		if (model->last_cluster_grow != 0)
		{
			if (model->last_cluster_grow == grow)
				model->stat_grow_equal++;
			else
				model->stat_grow_not_equal++;
		}
		
		model->last_cluster_grow = grow;
	}
	
	
}
