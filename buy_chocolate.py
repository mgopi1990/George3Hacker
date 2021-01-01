#!/usr/bin/env python3

## Ravi went to buy chocolate. One chocolate costs Rs.1.
## He also have offer that he can get one chocolate for 3 wrappers he return.
## Ravi ate all the chocolates. How many chocolates did Ravi ate?


WRAPPER_OFFER=3
COST_OF_CHOCOLATE=1

def chocolates_for_wrappers(n_chocolates):
    return(n_chocolates//WRAPPER_OFFER)

def buy_chocolates(cash):
    tot_chocolates = cash//COST_OF_CHOCOLATE
    temp_chocolates = tot_chocolates
    while (temp_chocolates):
        temp_chocolates = chocolates_for_wrappers(temp_chocolates)
        tot_chocolates += temp_chocolates
    return tot_chocolates


if __name__ == "__main__":
    cash = 15
    print (' Cash: {} Chocolates: {}'.format(cash, buy_chocolates(cash)))


