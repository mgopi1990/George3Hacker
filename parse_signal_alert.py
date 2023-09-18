#!/usr/bin/env python3

'''
Used to parse signal alert.

sample msg:

Today's free signal is

SIGNAL ALERT

SELL NZDJPY 84.517

🤑 TP1 84.250
🤑 TP2 83.900
🤑 TP3 83.000
🛑 SL 84.920

Upgrade now for up to 15 signals per day including updates on www.fxpremiere.com and Www.cryptocurrencysignal.com for Crypto days to get the best deals on the Internet

#forex #forexsignals #forextemplate #forexindicators #forextrader #forexlifestyle #forexmoney #forexlife #forexmarket #forextraining #forextrade #forexaccount #forextradingsignals #forexpartners #telegramforexsignals #telegramcopier the first thing is take the offer

'''

import re

def parse_for_signal_alert (forex_string):
 signal_alerts = []
 alert = {}
 currency = ''
 started = False
 for line in forex_string.split('\n'):
  line = line.strip()

  ## ignore empty line
  if line == '':
   continue

  ## skip till we reach 'SIGNAL ALERT'
  if not started:
   if (line.startswith ('SIGNAL ALERT')):
    started = True
   continue

  ## collect tokens
  tokens = line.split(' ')

  ## assume we reached the end  
  if (len(tokens) != 3):
   if (currency != ''):
    signal_alerts.append(alert)
    #print (f'Parsed till {line}')
   break

  ## assume beginning of the alert
  if ((tokens[0] == 'SELL') or \
      (tokens[0] == 'BUY')):
   ## some alert data is parsed.
   ## add and reinit
   if (currency != ''):
    signal_alerts.append (alert)
    alert = {}
   currency = tokens[1]
   alert[currency] = {}
   alert[currency][tokens[0]] = float (tokens[2])
  else: 
   alert[currency][tokens[1]] = float (tokens[2])
 else:
  signal_alerts.append(alert)
 return signal_alerts


### begin of main pgm

fp = open ('/tmp/tt1', 'r')
forex_string = fp.read()
alert_signals = parse_for_signal_alert (forex_string)
print (alert_signals)


