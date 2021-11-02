#!/usr/bin/env python3

## i/p: aaabcdce 
## o/p: 3a2c1b1d1e

from collections import OrderedDict

def convert_string(inp):
    tempOrderedDict = {}
    for e in inp:
        tempOrderedDict.setdefault(e, 0)
        tempOrderedDict[e] += 1
    
    tempList = []
    for k,v in tempOrderedDict.items():
        index = 0
        for k1,v1 in tempList:
            if v<=v1:
                index += 1
            else:
                break
        tempList.insert(index, (k,v))
    
    return ''.join(['{}{}'.format(k,v) for v,k in tempList])

print (convert_string('aaabcdce'))
