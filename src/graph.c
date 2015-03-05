#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void run_ctioga2(char* cmd)
{
	printf("Running ctioga2: %s\n", cmd);
	
	int status = system(cmd);
	
	//printf("CMD: %s\n", cmd);
	if (status != 0)
	{
		
		printf("------------------------------------------------------------\n");
		printf("WARNING:\n");
		printf("Plot command returned status %d. Executed command: %s\n", status, cmd);
		printf("------------------------------------------------------------\n");
		
		exit(-6);
	}
}

void create_log_grow_summary(char* input_file, char* output_file)
{
			
}

void created_graphs(char* output_dir, char* input_dir, char* exe_path, double min_t, double max_t, double min_fit_volume, double max_fit_volume, double fit_n, double fit_k, double theo_n, double theo_k)
{
	char buffer[2048];
	
	
	// Plotting grow linear
	sprintf(buffer, "ctioga2 --csv --load '%s/grow_summary.csv' -f '%s/util/plot/graph-grow-linear.ct2' --output-directory '%s' --name 'graph-grow-linear'", input_dir, exe_path, output_dir);
	run_ctioga2(buffer);
	
	// Plotting grow log
	sprintf(buffer, "ctioga2 --csv --load '%s/grow_summary_log.csv' -f '%s/util/plot/graph-grow-log.ct2'    --output-directory '%s' --name 'graph-grow-log'",    input_dir, exe_path, output_dir);
	run_ctioga2(buffer);
	
	// Plotting grow log with fit
	sprintf(buffer, "ctioga2 --csv --load '%s/grow_summary_log.csv' --set min_ln_t %.10E --set max_ln_t %.10E --set min_fit_volume %.2f --set max_fit_volume %.2f --set fit_n %.10E --set fit_k %.10E -f '%s/util/plot/graph-grow-log-fit.ct2'    --output-directory '%s' --name 'graph-grow-log-fit'", input_dir, log(min_t), log(max_t), min_fit_volume, max_fit_volume, fit_n, fit_k, exe_path, output_dir);
	run_ctioga2(buffer);
}

