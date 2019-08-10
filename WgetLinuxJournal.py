#!/usr/bin/env python3

# Seem like linux Journals site is going down
# Need to download all the study resources
# wget -c https://secure2.linuxjournal.com/ljarchive/LJArchive2018.zip
# rest of their .pdf documents can be downloaded
# by this script
# USAGE: just redirect the output of this script to shell script and run
# this generates wget to download files

from urllib.request import urlopen
from bs4 import BeautifulSoup
import re
import sys
import inspect

debug_wanted = False

def print_debug(message):
	if not debug_wanted:
		return

	callerframerecord = inspect.stack()[1]
	frame = callerframerecord[0]
	info = inspect.getframeinfo(frame)
	
	#print(info.filename, 'func=%s' % info.function, 'line=%s:' % info.lineno, message)
	#print(info.filename, 'func=%s' % info.function, 'line=%s:' % info.lineno, message)
	print ('# DEBUG: [{},{}] {}'.format(info.function, info.lineno, message), 
				file=sys.stderr)

def print_error (message):
	print ('# ERROR: ' + message, file=sys.stderr) 

def print_warning (message):
	print ('# WARN: ' + message, file=sys.stderr)

def generate_wgets():
	## The constants
	journal_name = 'LinuxJournal'
	link = 'https://secure2.linuxjournal.com/pdf/dljdownload.php'
	action = '&action=spit'

	## Lets be kind with the server
	wget_cmd = 'wget -m -c --wait=9 --limit-rate=10K -O '

	months = { 
		  'January':1, 
		 'February':2, 
		    'March':3, 
		    'April':4, 
		      'May':5, 
		     'June':6, 
		     'July':7, 
		   'August':8, 
		'September':9, 
		  'October':10, 
		 'November':11, 
		 'December':12
		 }

	## Strip the Focus or Feature
	regex1 = re.compile(r'Focus: *|Feature: *')
	regex1_sub = ''

	## these special chars turn to ' '
	regex2 = re.compile(r'[-/)(\']')
	regex2_sub = ' '

	## these spaces turn to _
	regex3 = re.compile(r'  *')
	regex3_sub = '_'

	page = urlopen(link)
	soup = BeautifulSoup(page, 'html.parser')
	#print(soup.prettify())

	for row in soup.findAll('tr'):
		## we know that, its Date, pdf link, epub link, mobi link, Feature
		i = 0
		for col in row.findAll('td'):
			print_debug (str(col))
			if (i == 0):
				## parse Date 
				date = col.find(text=True)
				if (date == None):
					print_error ('DateParse: NoneType')
					break
				date = date.strip().split(' ')
				print_debug (str(date))
				if (len(date) != 2):
					print_error ('Bad Month Year: ' + str(date))
					break;
				yr = date[1]
				mon = months.get(date[0])
				if (mon == 'None'):
					print_error ('Bad Month: ' + date[0])
					break
			elif (i == 1):
				## parse Pdf Link
				## https://download.linuxjournal.com/pdf/get-doc.php?code=64bf38057270d9c6101ccbb69e17ba9a&tcode=pdf-301-&action=spit
				## their php needs action to initiate download
				print_debug (str(col))
				download_url = col.find('a', href=True) 
				if (download_url == None):
					print_error ('Bad Download URL for {} {}'.format(mon,yr))
					break
				download_url = download_url['href'].strip() + action
				print_debug (download_url)
				if (not download_url.startswith('http://')):
					print_error ('Doesnt start with https: ' + download_url)
					break
			elif (i == 2):
				## parse Epub link
				## Todo: Need to have code here to parse, mostly like in pdf link
				pass
			elif (i == 3):
				## parse Mobi link
				## Todo: Need to have code here to parse, mostly like in pdf link
				pass
			elif (i == 4):
				## parse the feature text
				string = col.find(text=True).strip()
				print_debug (string)
				if (not (string.startswith('Focus:') or string.startswith('Feature:'))):
					print_warning ('Doesnt start with Focus or Feature: ' + string)
					break

				string = regex1.sub (regex1_sub, string)
				string = regex2.sub (regex2_sub, string)
				string = regex3.sub (regex3_sub, string)

			else:
				## we dont want anything more
				break
			i += 1
		else:
			print_debug ('No. of fields parsed: ' + str(i))

		if (i >= 4):
			out_file = '{}_{}_{:02d}_{}.pdf'.format(journal_name, yr, mon, string)
			cmd = '{} {} "{}"'.format(wget_cmd, out_file, download_url)
			print (cmd)

if __name__ == "__main__":
	generate_wgets()
