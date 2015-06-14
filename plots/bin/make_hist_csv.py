#!/usr/bin/python
import csv, sys, getopt

def main(argv):

	file_input  = ''
	file_output = ''
	column = None
	size   = None
	bars   = None
   
	try:
		opts, args = getopt.getopt(argv,"hi:c:s:o:b:",["input=","column=","size=", "output=", "bars="])
	except getopt.GetoptError:
		print 'make_hist_csv -i <input_file> -c <column> -s <size> -o <output_file>'
		sys.exit(2)
	for opt, arg in opts:
		if opt == '-h':
			print 'make_hist_csv -i <input_file> -c <column> -s <size> -o <output_file>'
			sys.exit()
		elif opt in ("-i", "--input"):
			file_input = arg
		elif opt in ("-o", "--output"):
			file_output = arg
		elif opt in ("-c", "--column"):
			column = int(arg) - 1
		elif opt in ("-s", "--size"):
			size = float(arg)
		elif opt in ("-b", "--bars"):
			bars = int(arg)

	if file_input  == '':
		print 'Input file was not provided'
		sys.exit(1)
	if file_output == '':
		print 'Output file was not provided'
		sys.exit(1)

	if column == None:
		print '--column must be provided'
		sys.exit(1)
		
	if bars == None and size == None:
		print 'One or --size of --bars must be provided'
		sys.exit(1)
		

		
		
	
	data = {}
	with open(file_input, 'r') as csv_input:
		reader = csv.reader(csv_input, delimiter=',', quotechar='|')
		next(reader, None)
		
		
		if bars != None:	
			value_min = None
			value_max = None
			
			for row in reader:
				value = float(row[column])
				
				if value_min == None or value_min > value:
					value_min = value
				if value_max == None or value_max < value:
					value_max = value
				
			size = (value_max - value_min) / bars
				
	with open(file_input, 'r') as csv_input:
		reader = csv.reader(csv_input, delimiter=',', quotechar='|')
		next(reader, None)	
		
		for row in reader:
			r = round(float(row[column]) / size)
			
			if not r in data:
				data[r] = 0
			data[r] += 1
			
			
	with open(file_output, 'w') as csv_output:
		writer = csv.writer(csv_output, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
		
		for r, c in data.iteritems():
			writer.writerow([r * size, c])
		
if __name__ == "__main__":
   main(sys.argv[1:])
   

	
