#!/usr/bin/env python3

'''
find . -type f -print0 | xargs -0 -I "{}" sh -c 'md5sum "{}" |  cut -f1 -d " " | tr "\n" " "; du -h "{}"' | sort -h -k2 -r | uniq -w32 --all-repeated=separate
'''

## high priority to low
FOLDERS = ["TRY7", "TRY6", "TRY5", "TRY4", "TRY3", "TRY2", "TRY1"]
MD5SUM_FILE = "files.txt"



def load_checksums():
 filelist_summary_dict = {}

 for folders in FOLDERS:
  lineno = 0
  md5file = folders + '/' + MD5SUM_FILE
  with open (md5file) as fp:
   for line in fp:
    words = line.strip().split('  ', 1)
    lineno += 1
    if (len(words) == 2):
     md5sum = words[0]
     fname = folders + '/' + words[1]
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
 fp = open (outfile, 'w')
 if fp:
  for k,v in filelist_summary_dict.items():
   if len(v) > 1:
    fp.write ('\n')
    for delfile in v[1:]:
     if not delfile.startswith('TRY7'): 
      ''' dont del anything from TRY7 '''
      fp.write (' rm -rf \'{}\'\n'.format(delfile))
 fp.close()

def print_filelist_summary (filelist_summary_dict, outfile):
 fp = open (outfile, 'w')
 if fp:
  for k,v in filelist_summary_dict.items():
   fp.write ('\n[{}] {}\n'.format (k, v[0]))
   for dupfile in v[1:]:
    fp.write(' {}\n'.format(dupfile))
 fp.close()



filelist_summary_dict = load_checksums()
print_filelist_summary (filelist_summary_dict, 'summary.txt')
print_filelist_delete (filelist_summary_dict, 'del.txt')


