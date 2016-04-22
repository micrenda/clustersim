#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void run_ctioga2(char* cmd, char* name, int debug_flag)
{
	printf("Running ctioga2 for '%s':\t", name);
	
	if (debug_flag)
		printf("%s\n", cmd);
	
	int status = system(cmd);
	
	if (!debug_flag)
		printf("DONE\n");
	
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

void created_graphs(char* output_dir, char* input_dir, char* exe_path, double min_t, double max_t, double min_fit_volume, double max_fit_volume, double fit_n, double fit_k, double theo_n, double theo_k, int debug_flag)
{
	char buffer[2048];
	
	
	// Plotting grow linear
	sprintf(buffer, "ctioga2 --csv --load '%s/grow_summary.csv' -f '%s/plot/graph-grow-linear.ct2' --output-directory '%s' --name 'graph-grow-linear'", input_dir, exe_path, output_dir);
	run_ctioga2(buffer, "graph-grow-linear", debug_flag);
	
	// Plotting grow linear with fit
	sprintf(buffer, "ctioga2 --csv --load '%s/grow_summary.csv' --set min_t %.10E --set max_t %.10E --set min_fit_volume %.2f --set max_fit_volume %.2f --set fit_n %.10f --set fit_k %.10E  --set theo_n %.10f --set theo_k %.10E -f '%s/plot/graph-grow-linear-fit.ct2' --output-directory '%s' --name 'graph-grow-linear-fit'", input_dir, min_t, max_t, min_fit_volume, max_fit_volume, fit_n, fit_k, theo_n, theo_k, exe_path, output_dir);
	run_ctioga2(buffer, "graph-grow-linear-fit", debug_flag);
	
	// Plotting grow log
	sprintf(buffer, "ctioga2 --csv --load '%s/grow_summary_log.csv' -f '%s/plot/graph-grow-log.ct2'    --output-directory '%s' --name 'graph-grow-log'",    input_dir, exe_path, output_dir);
	run_ctioga2(buffer, "graph-grow-log", debug_flag);
	
	// Plotting grow log with fit
	sprintf(buffer, "ctioga2 --csv --load '%s/grow_summary_log.csv' --set min_ln_t %.10E --set max_ln_t %.10E --set min_fit_volume %.2f --set max_fit_volume %.2f --set fit_n %.10f --set fit_k %.10E --set theo_n %.10f --set theo_k %.10E -f '%s/plot/graph-grow-log-fit.ct2'    --output-directory '%s' --name 'graph-grow-log-fit'", input_dir, log(min_t), log(max_t), min_fit_volume, max_fit_volume, fit_n, fit_k, theo_n, theo_k, exe_path, output_dir);
	run_ctioga2(buffer, "graph-grow-log-fit", debug_flag);
	
	//// Plotting histograms
	//sprintf(buffer, "ctioga2 --csv --load '%s/clusters_details.csv' -f '%s/plot/hist-volume.ct2'    --output-directory '%s' --name 'hist-volume'", input_dir, exe_path, output_dir);
	//run_ctioga2(buffer, "hist-volume", debug_flag);
}

