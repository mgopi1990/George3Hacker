#!/usr/bin/env python3

## Converts ur name to japanese_name
def japanese_name(name):
 j_letter = {
  'A':'ka', 'B':'tu', 'C':'mi', 'D':'te',
  'E':'ku', 'F':'lu', 'G':'ji', 'H':'ri',
  'I':'ki', 'J':'zu', 'K':'me', 'L':'ta',
  'M':'rin','N':'to', 'O':'mo', 'P':'no',
  'Q':'ke', 'R':'shi','S':'ari','T':'chi',
  'U':'do', 'V':'ru', 'W':'mei','X':'na',
  'Y':'fu', 'Z':'zi',
  }

 j_name = [j_letter.get(x,x) for x in name.upper()]
 return (''.join(j_name).title())

if __name__ == "__main__":
 eng_name = input ('Enter name: ')
 print (japanese_name(eng_name))
