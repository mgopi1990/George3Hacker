#!/usr/bin/env python

## This program find the number of days required to upgrade all buildings in castle siege
## install bs4 and prettytable for this to run
## pip install bs4
## pip install prettytable

from bs4 import BeautifulSoup
from urllib.request import urlopen	
from pprint import pprint
from prettytable import PrettyTable
from termcolor import colored

####### GLOBAL DATA: Dont disturb #######

## Upgrade cost; Fetched from internet using DownloadUpgradeCost()
## Curtesy: http://age-of-empires-castle-siege.wikia.com/wiki/
DictUpgradeCost = {
 'Archer Tower': ['15s', '30m', '2h', '6h', '16h', '1d', '1d 16h', '2d 8h', '4d', '6d', '8d'],
 'Archery Range': ['1h', '3h', '12h', '1d 6h', '2d 18h', '4d 12h', '6d 12h', '8d', '10d'],
 'Army Camp': ['10s', '1h 30m', '3h', '15h', '1d 12h', '3d', '5d 6h', '7d 12h', '10d'],
 'Ballista Tower': ['1d 12h', '2d 12h', '3d 12h', '5d 6h', '7d 12h', '10d', '12d'],
 'Barracks': ['30m', '1h 15m', '3h', '12h', '1d 6h', '2d 18h', '4d 12h', '6d 12h', '8d', '10d'],
 'Caltrops': ['15m', '45m', '2h', '3h', '4h', '6h', '9h', '12h'],
 'Catapult Emplacement': ['4h 30m', '16h', '3d', '5d 6h', '7d 12h', '8d', '10d'],
 'Cathedral': ['3h', '10h', '1d', '2d', '3d 12h', '5d'],
 'Crossbow Tower': ['10h', '1d', '2d', '3d 12h', '5d', '6d'],
 'Cultural Barracks': ['1d 12h', '3d', '5d 6h', '7d 12h', '10d'],
 'Embassy': ['2d', '5d'],
 'Engineer Trap': ['10h', '14h', '18h', '1d', '1d 6h', '2d'],
 'Farm': ['1m', '2m', '1h', '3h', '10h', '16h', '1d', '1d 18h', '2d 12h', '3d 12h', '4d 22h'],
 'Fire Trap': ['10h', '14h', '18h', '24h', '1d 6h', '1d 12h', '2d'],
 'Flame Tower': ['3d', '4d 12h', '6d', '7d 12h', '9d'],
 'Guard House': ['2h', '6h', '16h', '1d 8h', '2d 8h', '5d', '12d'],
 'Hall of Heroes': ['3h', '1d', '2d', '7d 12h'],
 'Keep': ['0s', '45s', '2h', '6h', '20h', '2d', '4d', '7d', '10d', '14d'],
 'Lumberyard': ['10s', '15s', '45m', '2h', '6h', '12h', '1d', '2d', '3d', '4d'],
 'Mill': ['1m', '2m', '1h', '3h', '10h', '16h', '1d', '1d 18h', '2d 12h', '3d 12h', '4d 22h'],
 'Musket Tower': ['10d', '12d'],
 'Patrol Point': ['30m', '1h 15m'],
 'Quarry': ['12h', '16h', '1d', '2d', '3d 12h', '5d', '5d 12h', '6d 2h'],
 'Road': [], 
 'Siege Workshop': ['1h', '12h', '1d 6h', '2d 18h', '4d 12h', '6d 12h', '8d', '10d'],
 'Silo': ['10s', '15s', '45m', '2h', '6h', '12h', '1d', '2d', '3d', '4d'],
 'Stable': ['1d 6h', '2d 18h', '4d 12h', '6d 12h', '8d', '10d'],
 'Storehouse': ['1h 30m', '6h', '12h', '1d', '2d', '3d', '4d'],
 'Trebuchet Emplacement': ['3d', '5d 6h', '7d 12h', '10d'],
 'University': ['3h', '10h', '1d', '2d', '3d 12h', '5d'],
 'Wall': [],
 'Watch Signal': ['15h', '15h', '1d', '2d', '2d', '3d 12h', '5d', '7d']
}

######## List of buildings. Too lazy to use ordered dict #############
ListBuilding = [ 'Keep', 'Archer Tower', 'Ballista Tower', 'Crossbow Tower', 
					  'Flame Tower', 'Musket Tower', 'Catapult Emplacement', 
					  'Trebuchet Emplacement', 'Barracks', 'Archery Range', 'Stable', 
					  'Siege Workshop', 'Cultural Barracks', 'Hall of Heroes', 'Army Camp', 
					  'Caltrops', 'Engineer Trap', 'Fire Trap', 'Guard House', 'Patrol Point', 
					  'Cathedral', 'University', 'Embassy', 'Farm', 'Lumberyard', 'Quarry', 
					  'Mill', 'Silo', 'Storehouse', 'Watch Signal', 'Wall', 'Road' 
					]


#################################################################################

####### My Buildings Current level #######
DictMyBuildingsUpgrade = {
 'Keep': 		[ 9 ],
 'Archer Tower': 	[ 8, 7, 7, 7, 7, 7, 5, 0 ],
 'Ballista Tower': 	[ 3, 3, 3, 3, 0 ],
 'Crossbow Tower': 	[ 4, 3, 3 ],
 'Flame Tower':		[ 3, 3 ],
 'Musket Tower': 	[ 0, 0 ],
 'Catapult Emplacement': [ 4, 4, 4 ],
 'Trebuchet Emplacement':[ 2, 2 ],
 'Barracks': 		[ 8 ],
 'Archery Range': 	[ 7 ],
 'Stable': 		[ 4 ],
 'Siege Workshop': 	[ 6 ],
 'Cultural Barracks': 	[ 4 ],
 'Hall of Heroes': 	[ 4 ],
 'Army Camp': 		[ 8, 8, 8, 8 ],
 'Caltrops': 		[ 3, 3, 7, 7, 7, 2, 4, 3, 3, 7, 7, 3, 3, 3 ],
 'Engineer Trap': 	[ 5, 3, 3, 3 ],
 'Fire Trap': 		[ 5, 6 ],
 'Guard House':		[ 6, 5 ],
 'Patrol Point': 	[ 2, 2, 2 ],
 'Cathedral': 		[ 6 ],
 'University': 		[ 6 ],
 'Embassy': 		[ 2 ],
 'Farm': 		[ 9, 9, 9, 9 ],
 'Lumberyard': 		[ 9, 9, 9, 9 ],
 'Quarry': 		[ 6, 6, 6 ],
 'Mill': 		[ 10, 10, 9, 9 ],
 'Silo': 		[ 9, 9, 9, 9 ],
 'Storehouse': 		[ 6, 6 ],
 'Watch Signal': 	[ 6 ],
 'Wall': 		[ ],
 'Road': 		[ ]
 }

## Class to Handle CSTime format 0d 10h 15m 10s
class CSTime:
	def __init__(self, days=0, hours=0, min=0, sec=0):
		self.days, self.hours, self.min, self.sec = days, hours, min, sec
		self.convert_date ()
		
	def __init__(self, other):
		if (isinstance(other, CSTime)):
			self.days, self.hours, self.min, self.sec = other.days, other.hours, other.min, other.sec
		elif (isinstance (other, str)):
			days, hours, min, sec = 0, 0, 0, 0
			CSTimeStr = other
	
			for t in CSTimeStr.split(' '):
				if t == '' or t == ' ':
					continue
				
				if t[-1] == 'd':
					days += int(t[0:-1])
				elif t[-1] == 'h':
					hours += int(t[0:-1])
				elif t[-1] == 'm':
					min += int(t[0:-1])
				elif t[-1] == 's':
					sec += int(t[0:-1])
				else:
					continue
	
			self.days, self.hours, self.min, self.sec = days, hours, min, sec
			self.convert_date ()

	def __add__(self, other):
		return (CSTime(self.days + other.days,
							self.hours + other.hours,
							self.min + other.min,
							self.sec + other.sec))

	def __iadd__(self, other):
		self.days, self.hours, self.min, self.sec = self.days+other.days, self.hours + other.hours, self.min + other.min, self.sec + other.sec 
		self.convert_date ()
		return (self)

	def __str__(self):
		ret_str = ''
		if self.days:
			ret_str += str(self.days) +'d '
		if self.hours:		
			ret_str += str(self.hours) +'h '
		if self.min:		
			ret_str += str(self.min) +'m '
		if self.sec:		
			ret_str += str(self.sec) +'s '
		
		if ret_str == '':
			return('0s')

		return(ret_str.rstrip())

	def convert_date(self):
		self.min += self.sec // 60
		self.sec %= 60
		self.hours += self.min // 60
		self.min %= 60
		self.days += self.hours // 24
		self.hours %= 24
## End of CSTime


## Downloads building cost from age-of-empires-castle-siege.wika.com
def DownloadUpgradeCost():
	HomeUrl = 'http://age-of-empires-castle-siege.wikia.com/wiki/'
	StrFind = 'Upgrade Time'
	DictBuildings = {}
	for building in ListBuilding():
		#print (building.replace(' ','_'))
		Url = HomeUrl + building.replace(' ','_')
		page = urlopen(Url)
		soup = BeautifulSoup(page, 'html.parser')
		table = soup.find('table', class_='article-table')
		i = 0
		for tr in table.findAll('tr'):
			if i == 0:
				j = 0;
				for th in tr.findAll('th'):
					#print ('[' + th.find(text=True).rstrip() + ']')
					if th.find(text=True).rstrip() == StrFind:
						break
					j += 1
			else:
				k = 0
				for td in tr.findAll('td'):
					k += 1
					if (k == j):
						#print (td.find(text=True).rstrip())
						DictBuildings[building].append(td.find(text=True).rstrip())
						break
			i += 1
			#print (tr.find(text = True))
			#print (tr)
	#pprint(DictBuildings)
	return (DictBuildings)

## Finds Hours required and pretty prints the table
def FindHours(DictUpgradeCost, DictMyBuildingsUpgrade):
	x = PrettyTable(['Sno', 'Building', 'Cur/Max', 'HoursForMe', 'WholeHours'])
	x.align['Building'] = 'l'
	x.align['HoursForMe'] = 'l'
	x.align['WholeHours'] = 'l'

	TotalHoursNeededForAll = CSTime('0s')
	TotalHoursNeededForMe  = CSTime('0s')
	sno = 1
	for building in ListBuilding:
		x.add_row(['', building + ':', '', '', ''])
		building_no = 1
		for current_level in DictMyBuildingsUpgrade[building]:

			BuildingHoursNeededForMe = CSTime('0s')
			BuildingHoursNeededForAll = CSTime('0s')	
			for cost in DictUpgradeCost[building][current_level:]:
				BuildingHoursNeededForMe += CSTime(cost)

			BuildingHoursNeededForAll = CSTime(BuildingHoursNeededForMe)
			for cost in DictUpgradeCost[building][0:current_level]:
				BuildingHoursNeededForAll += CSTime(cost)

			TotalHoursNeededForMe += BuildingHoursNeededForMe
			TotalHoursNeededForAll += BuildingHoursNeededForAll

			x.add_row([str(sno), 
						  '   '+building+str(building_no), 
						  	str(current_level) + '/' + str(len(DictUpgradeCost[building])),
							str(BuildingHoursNeededForMe),
							str(BuildingHoursNeededForAll)])

			building_no += 1
			sno += 1

	#x.add_row(['', '        TOTAL ', '', str(TotalHoursNeededForMe), str(TotalHoursNeededForAll)])
	x.add_row(['', colored('        TOTAL ','red'), '', str(TotalHoursNeededForMe), str(TotalHoursNeededForAll)])
	print(x)

################# Our Program starts here ####################
## Only two lines :-P

#DictUpgradeCost = DownloadUpgradeCost()
FindHours(DictUpgradeCost, DictMyBuildingsUpgrade)

