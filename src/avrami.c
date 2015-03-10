#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

void compute_avrami(char* input_grow_summary, char* output_grow_summary_log, double min_volume, double max_volume, double* min_t, double* max_t, double* fit_n, double* fit_k, double* theo_n, double* theo_k)
{
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
