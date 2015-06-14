#!/usr/bin/python
import csv, sys, getopt, math

def main(argv):

	try:
		opts, args = getopt.getopt(argv,"h",[])
	except getopt.GetoptError:
		print 'make_avg_csv <file1> <file2> ...'
		sys.exit(2)
	for opt, arg in opts:
		if opt == '-h':
			print 'make_avg_csv <file1> <file2> ...'
			sys.exit()
	
	data = {}
	
	print "# basename, dimensions, count, avg_n, stdev_n, avg_k, stdev_k"
	
	for file_input in argv:
		
		count   = 0
		avg_n 	= 0.0	
		avg_k 	= 0.0
		
		dimensions = None
			
		with open(file_input, 'r') as csv_input:
			reader = csv.reader(csv_input, delimiter=',', quotechar='|')
			next(reader, None)
			
			sum_n	= 0.0 
			sum_k	= 0.0
		
			for row in reader:
				
				if float(row[5]) != 0.0 and float(row[6]) != 0.0:
					sum_n += float(row[5])
					sum_k += float(row[6])
					count += 1
					dimensions = int(row[1])
			
			avg_n = sum_n / count	
			avg_k = sum_k / count
				
			
		with open(file_input, 'r') as csv_input:
			reader = csv.reader(csv_input, delimiter=',', quotechar='|')
			next(reader, None)
			
			sum_pow2_n	= 0.0;
			sum_pow2_k	= 0.0;
			
			for row in reader:
				if float(row[5]) != 0.0 and float(row[6]) != 0.0:
					sum_pow2_n += math.pow(float(row[5]) - avg_n, 2)
					sum_pow2_k += math.pow(float(row[6]) - avg_k, 2)
				
			stdev_n = math.sqrt(sum_pow2_n / count);
			stdev_k = math.sqrt(sum_pow2_k / count);
			

			print "%s,\t%d,\t%d,\t%.8E,\t%.8E,\t%.8E,\t%.8E" % (row[0], dimensions, count, avg_n, stdev_n, avg_k, stdev_k)
		
		
if __name__ == "__main__":
   main(sys.argv[1:])
   

	
