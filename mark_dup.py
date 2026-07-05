#!/usr/bin/env python3

'''
Used to detect duplicates between various revisions.
Like the below script,
find . -type f -print0 | xargs -0 -I "{}" sh -c 'md5sum "{}" |  cut -f1 -d " " | tr "\n" " "; du -h "{}"' | sort -h -k2 -r | uniq -w32 --all-repeated=separate

Consider we have several folders, say TRY7, TRY6 ... TRY1.
Each of which is taken backup several times with TRY7 being the latest.
Then all the duplicates in TRY6 ... TRY1 would be fetched and removed.
This would not touch any dups in TRY7 to be safe.

This also wont delete any files. But would generate SUMMARY and DEL files,
which could be run to take appropriate action.

run,
python3 mark_dup.py "TRY7;TRY6;TRY5;TRY4;TRY3;TRY2;TRY1"

TRY7 is the FINAL_FOLDER
TRY6..TRY1 are the old drafts.
All these folders need to have MD5SUM_FILE to work properly

'''

import os
import sys

''' globals '''
MD5SUM_FILE = "files.txt"
SUMMARY_FILE = 'summary.txt'
DEL_FILE = 'del.txt'
LOST_FILE = 'lost.txt'

''' folder list would be populated '''
FOLDERS = []
FINAL_FOLDER = ''


def load_folder_list_from_args(argv):
 global FOLDERS, FINAL_FOLDER

 if len (argv) != 2: ''' need exactly 1 argument '''
  print (' Usage: {} "FOLDER_FINAL;FOLDER_N;...;FOLDER_1"'.format (argv[0]))
  return -1

 FOLDERS = [x.strip() for x in argv[1].split(';')]
 FINAL_FOLDER = FOLDERS[0]

 if len (FOLDERS) < 2:
  print ('ERROR: Need atleast 2 folders')
  return -1

 ''' check if MD5SUM_FILE exist '''
 for folders in FOLDERS:
  md5file = os.path.join (folders, MD5SUM_FILE)
  if (not os.path.isfile(md5file)):
   print ('ERROR: file not found {}'.format (md5file))
   return -1

 return 0


def load_checksums():
 filelist_summary_dict = {}

 for folders in FOLDERS:
  lineno = 0
  md5file = os.path.join (folders, MD5SUM_FILE)
  with open (md5file) as fp:
   for line in fp:
    words = line.strip().split('  ', 1)
    lineno += 1
    if (len(words) == 2):
     md5sum = words[0]
     fname = os.path.join (folders, words[1])
     if words[0] in filelist_summary_dict:
      ''' dup files follows the first '''
      filelist_summary_dict[md5sum].append(fname)
     else:
      ''' add original to first of the list '''
      filelist_summary_dict[md5sum] = [fname]
    else:
     print ('ERROR:parser failed {}:{}:{}'.format(md5file, lineno, line))

 #print (filelist_summary_dict)
 return filelist_summary_dict


def print_filelist_delete (filelist_summary_dict, outfile):
 with open (outfile, 'w') as fp:
  for k,v in filelist_summary_dict.items():
   if len(v) > 1:
    fp.write ('\n')
    for delfile in v[1:]:
     if not delfile.startswith(FINAL_FOLDER):
      ''' don't del anything from FINAL_FOLDER '''
      fp.write (' rm -f \'{}\'\n'.format(delfile))


def print_filelist_summary (filelist_summary_dict, outfile):
 with open (outfile, 'w') as fp:
  for k,v in filelist_summary_dict.items():
   fp.write ('\n[{}] {}\n'.format (k, v[0]))
   for dupfile in v[1:]:
    fp.write(' {}\n'.format(dupfile))


### start of main ###
if __name__ == '__main__':
 if (load_folder_list_from_args(sys.argv) != 0):
  print ('ERROR: Parse failed')
  sys.exit()

 filelist_summary_dict = load_checksums()
 print_filelist_summary (filelist_summary_dict, SUMMARY_FILE)
 print_filelist_delete (filelist_summary_dict, DEL_FILE)
