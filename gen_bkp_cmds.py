#!/usr/bin/env python3

## Someone gave this activity
## Some sort of backup utility
## backup file in dest to tgz 
## Copies files from src to dest.

## ./gen_bkp_cmds.py a.csv
## sample << a.csv >>
## "/home/pi/Desktop/temp/src/t1","/home/pi/Desktop/temp/dest/t1","/home/pi/Desktop/temp/bkp/t1"
## "/home/pi/Desktop/temp/src/t2","/home/pi/Desktop/temp/dest/t2","/home/pi/Desktop/temp/bkp/t2"

import csv
import os
import sys
import datetime

if len(sys.argv) <= 1:
    print (' Usage: {} <file1.csv> <file2.csv> ... <filen.csv>'
                        .format(sys.argv[0]))
    sys.exit()

## add to bkp
bkp_postfix = datetime.datetime.now().strftime('_%Y%m%d%H%M%S.tgz')

for csv_file in sys.argv[1:]:
    try:
        fp = open(csv_file,'r')
    except:
        print ('ERROR: Unable to open {}'.format(csv_file), 
                                    file=sys.stderr)
        continue
    else:
        csv_reader = csv.reader(fp)
        line_count = 0
        for row in csv_reader:
            ## print (row)
            line_count += 1
            if len(row) != 3:
                print ('ERROR: [{}:{}] Parse failed'
                                .format(csv_file, line_count),
                                    file=sys.stderr)
                continue

            print ('\n## [{}:{}]'.format(csv_file, line_count))
            ## Copy tar
            cmd = ('tar -zcvf "{}{}" "{}"'
                    .format(row[2],bkp_postfix,row[1]))
            print (cmd)
            #os.system(cmd)

            ## Copy file
            cmd = 'cp -rf "{}" "{}"'.format(row[0], row[1])
            print (cmd)
            #os.system(cmd)

