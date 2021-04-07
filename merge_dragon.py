#!/usr/bin/env python3

## Lets check how much merge is needed for different levels
## in dragon merge.
## lets check 3 merge line and 5 merge line,
## and see like, how long it takes to reach greater levels

## Sample run output.
## Fuck merge dragon. I need to merge whole life to create wonders.
'''
$ python3 merge_dragon.py
 Choose max level as 18
 Type: MERGE_BY_3
  max_level: 18
  tot_merges: 64570081
  tot_wanted: 129140163
  max_squares: 35
  Units Left:
   Level 18: 1


 Type: MERGE_BY_5
  max_level: 18
  tot_merges: 4979685
  tot_wanted: 14939065
  max_squares: 62
  Units Left:
   Level 18: 2
   Level 17: 1
   Level 16: 1
   Level 12: 1
   Level 11: 1
   Level 10: 1
   Level  8: 1
   Level  6: 1
   Level  2: 1


 Type: HYBRID_MERGE
  max_level: 18
  tot_merges: 2489847 (merge_by_3-9, merge_by_5-2489838)
  tot_wanted: 7469533
  max_squares: 0
  Units Left:
   Level 18: 1
'''


import sys

# Max level we could calculate by default
MAX_LEVEL = 18 

MERGE_BY_3 = 3
MERGE_BY_5 = 5

def calc_merge_3(max_level):
	return calc_merge (max_level, MERGE_BY_3)

def calc_merge_5(max_level):
	return calc_merge (max_level, MERGE_BY_5)

## Handles MERGE_BY_3 and MERGE_BY_5
def calc_merge (max_level, min_merge):
	merge_dict = {}
	merge_dict['type'] = 'MERGE_BY_{}'.format(min_merge)
	merge_dict['merge'] = {}
	for i in range(1, max_level+1):
		merge_dict['merge'][i] = 0

	current_high_level = 0
	tot_merges = 0
	squares = 0
	max_squares = 0
	tot_wanted = 0
	merge_tree = merge_dict['merge']
	while (merge_tree[max_level] == 0):
		merge_tree[1] += min_merge
		tot_wanted += min_merge
		squares += min_merge

		if (squares > max_squares):
			max_squares = squares

		for i in range (1, max_level):
			new = (merge_tree[i] // min_merge)
			if new == 0:
				break

			if (min_merge == MERGE_BY_3):
				## incase of merge by 3, we get one new units
				merge_tree[i+1] += new

				## when we merge 3 units, the new object takes 1 unit space.
				## so -3 + 1 = -2 
				squares -= (2*new)

			elif (min_merge == MERGE_BY_5):
				## incase of merge by 5, we get two new units
				merge_tree[i+1] += new*2
			
				## when we merge 5 units, the new object takes 2 unit space.
				## so -5 + 2 = -3
				squares -= (3*new)

			merge_tree[i] = merge_tree[i] % min_merge
			tot_merges += 1

	merge_dict['max_level'] = max_level
	merge_dict['tot_merges'] = tot_merges
	merge_dict['tot_wanted'] = tot_wanted
	merge_dict['max_squares'] = max_squares

	return merge_dict

## Calculates merge by 5 or 3, 
## we dont want 2 units of final level
def calc_merge_hybrid(max_level):
	merge_dict = {}
	merge_dict['type'] = 'HYBRID_MERGE'
	merge_dict['max_level'] = max_level

	merge_dict['merge'] = {}
	for i in range(1, max_level+1):
		merge_dict['merge'][i] = 0

	merge_tree = merge_dict['merge']
	merge_tree[max_level] = 1
	tot_merge_by_5 = 0
	tot_merge_by_3 = 0
	for level in range(max_level, 1, -1):
		merge_by_5 = merge_tree[level] // 2 
		merge_by_3 = merge_tree[level] % 2
		merge_tree[level] = 0
		merge_tree[level-1] = (merge_by_5 * 5) + (merge_by_3 * 3)
		tot_merge_by_5 += merge_by_5
		tot_merge_by_3 += merge_by_3

	merge_dict['tot_merges'] = tot_merge_by_5 + tot_merge_by_3
	merge_dict['tot_merges_by_3'] = tot_merge_by_3
	merge_dict['tot_merges_by_5'] = tot_merge_by_5
	merge_dict['tot_wanted'] = merge_tree[1]
	
	## ToDo: To be handled later 
	merge_dict['max_squares'] = 0
	
	## reset the tree
	merge_tree[1] = 0
	merge_tree[max_level] = 1

	return merge_dict


def print_merge (merge_dict):
	if (merge_dict['type'] == 'HYBRID_MERGE'):
		print ((' Type: {}\n  max_level: {}\n' +
				'  tot_merges: {} (merge_by_3-{}, merge_by_5-{})\n' +
			    '  tot_wanted: {}\n  max_squares: {}').
					format(merge_dict['type'], merge_dict['max_level'], 
							merge_dict['tot_merges'], 
							merge_dict['tot_merges_by_3'], 
							merge_dict['tot_merges_by_5'], 
							merge_dict['tot_wanted'], 
							merge_dict['max_squares']))
	else: 
		print ((' Type: {}\n  max_level: {}\n  tot_merges: {}\n' +
				'  tot_wanted: {}\n  max_squares: {}').
					format(merge_dict['type'], merge_dict['max_level'], 
							merge_dict['tot_merges'], merge_dict['tot_wanted'], 
							merge_dict['max_squares']))

	print ('  Units Left:')
	for i in range(merge_dict['max_level'], 0, -1): 
		if (merge_dict['merge'][i] == 0):
			continue
		print ('   Level {:2}: {}'.format(i, merge_dict['merge'][i]))

	print ('\n')


if __name__ == "__main__":
	if (len(sys.argv) <= 1) or (int(sys.argv[1]) < 2):
		max_level = MAX_LEVEL 
		print (' Choose max level as {}'.format(MAX_LEVEL))
	else:
		max_level = int(sys.argv[1])

	for merge_handle in [calc_merge_3, calc_merge_5, calc_merge_hybrid]:
		print_merge (merge_handle(max_level))

