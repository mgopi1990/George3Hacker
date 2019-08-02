#!/usr/bin/env python

## This is used to extract .tgz recursively
## Just copy the parent .tgz into a folder and run it.
## WARNING: it could delete the .tgz after extraction. So backup

import os
import sys

## How to extract these files ???
archive_detail = { '.tgz': {'cmd': 'tar -zxf {} -C {}'},
                '.tar.gz': {'cmd': 'tar -zxf {} -C {}'},
                   '.tar': {'cmd': 'tar -xf {} -C {}' },
                   '.gz' : {'cmd': 'gunzip {}'}
                 }

## This function will be invoked recursively to extract the files
## takes current path and new path to be tried as arguments
def recursive_archive(cwd_path, new_path):
  ## Ignore normal files and soft links
  if (os.path.isfile(new_path) or os.path.islink(new_path)):
    return

  ## Lets get to this folder
  os.chdir(new_path)
  print ('cd ' + new_path)

  ## walk through all the child directories.
  ## Cant we use os.path.walk() ???
  for filename in os.listdir('.'):

    ## again, ignore softlinks
    if (os.path.islink(filename)):
      continue

    ## just confirm if its normal file
    if (os.path.isfile(filename)):

      for extn in archive_detail.keys():
        if (filename.endswith(extn)):
          folder_name = filename[0:(-1 * len(extn))]

          if (extn == '.gz'):
            ## we handle both .gz and .tar.gz
            if (filename.endswith('.tar.gz')):
              continue

            ## To handle 0size file. Just delete them
            if (os.path.getsize(filename) == 0):
              os.unlink(filename)
              print ('# del 0 byte file ' + filename)
              continue

            os.system(archive_detail[extn]['cmd'].format(filename))
            print (archive_detail[extn]['cmd'].format(filename))

            recursive_archive (new_path, os.path.join(new_path, folder_name))

          else:
            ## Handles other types, like, tar.gz, tgz etc..
            ## Just create a new folder with tgz name and extract there
            ## Finally del the filename
            os.mkdir(folder_name)
            print ('mkdir ' + folder_name)
            os.system(archive_detail[extn]['cmd'].format(filename, folder_name))
            print (archive_detail[extn]['cmd'].format(filename, folder_name))
            os.unlink(filename)
            print ('rm ' + filename)

            recursive_archive (new_path, os.path.join(new_path, folder_name))
      continue

    ## Handle directory
    ## Just initiate a recursion for each folder we come across
    if (os.path.isdir(filename)):
      temp_path = os.path.join(new_path, filename)
      #print('HERE' + temp_path)
      
      recursive_archive (new_path, temp_path)

      os.chdir(cwd_path)
      print ('cd ' + cwd_path)

## start of main()
if __name__ == "__main__":
  cwd = os.getcwd()
  if (len(sys.argv) <= 1):
    recursive_archive(cwd, os.path.join(cwd, '.'))
  else:
    for paths in sys.argv[1:]:
      os.chdir(paths)
      recursive_archive(cwd, os.path.join(cwd, paths))
      os.chdir(cwd)
