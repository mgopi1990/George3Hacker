#!/usr/bin/env python3

# In 5 min, 5 crane, can catch 5 fishes
# How much can, 50 cranes catch in 50 min ??

# In 5 min, 5 crane, can catch 5 fishes
# So in 50 min, 5 crane can catch 50 fishes
# So in 50 min, 50 crane can catch 500 fishes ???
# lets confirm with code snippet

from math import ceil

if __name__ == "__main__":
    FISH_CAUGHT_BY_5CRANE_IN_5MIN = 5
    i = 0
    for cranes in [ 5, 50]:
        for max_minutes in [ 5, 50 ]:
            fishes = 0
            i += 1
            print (' Test{}: crane: {} max_min: {}:'.format(i, cranes, max_minutes))
            for minutes in range(5, max_minutes+1, 5):
                fishes += FISH_CAUGHT_BY_5CRANE_IN_5MIN * ceil (cranes / 5)
                print ('  Min:{:3} Fishes: {}'.format(minutes, fishes))
            print (' Result Test{}: crane: {} max_min: {} fishes: {}\n'.format(i, cranes, max_minutes, fishes))


