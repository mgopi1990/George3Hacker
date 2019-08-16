#!/usr/bin/env python3

## Simply reads csv file and generates sed for translation
## the cvs files will be in the below format,
## char 1,char 2,char 3
## Scaffold1,Scaffold2,Scaffold3
## Scaffold4,Scaffold8,Scaffold1
## Scaffold6,Scaffold9,Scaffold11
## ,Scaffold9,
##
## eg.
##  ./a.py aa.csv
## 

import sys
import csv

def gen_sed_list (files):
	translations_dict = {}
	translations_list = []
	line_no = 1
	for file in files:
		with open(file, 'r') as f:
			data = csv.reader(f)

			## just read the row0, heading
			for heading in data:
				heading = tuple(heading)
				break

			for row in data:
				line_no += 1
				for index,word in enumerate(row):
					word = word.strip()
					if (word == ''):
						print ('# WARN  [{},{}]: word empty while parsing {}'.format(file, line_no, row))
						continue

					if (word in translations_dict.keys()):
						print ('# ERROR [{},{}]: ({}:{}) already present while parsing {}'.format(file, line_no, word, translations_dict[word], row))
						continue

					if (index < len(heading)):
						translations_dict[word] = heading[index]
					else:
						print ('# ERROR [{},{}]: no heading for {}'.format(file, line_no, word))

	for orig in sorted(translations_dict.keys(), reverse=True):
		#translations_list.append(tuple(orig, translations_dict[orig], 's/{}/{}/g'.format(orig,translations_dict[orig])))
		translations_list.append('s/{}/{}/g;'.format(orig,translations_dict[orig]))

	return translations_list

if __name__ == "__main__":
	if len(sys.argv) <= 1:
		print (' Usage: {} <csv filename>'.format(sys.argv[0]))
		exit()
	
	sed_list = gen_sed_list(sys.argv[1:])

	print ('\n\n## paste this below translations into a file; say aa.sed')
	print ('## then issue, sed -f aa.sed inFile > outFile \n')
	for i in sed_list:
		print (i);
