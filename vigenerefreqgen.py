#!/usr/bin/env python3.3
# vigenerefreq2 -- compute word frequencies from standard input and KEYWORD LENGTH

import sys
import re
import operator
from string import ascii_lowercase


keylength = 7 # CHANGE FOR OTHER KEYLENGTHS BASED ON GCD WITHIN REPETITIONS
c = []

# process input

for line in sys.stdin:
	line = line.rstrip('\n')				# strip lines; make lowercase; 
	line = line.lower()

# create frequency list (list of dictionaries)

f = [{} for i in range(keylength)]
for i in range(keylength):	
	c.append(line[i::keylength])   # a list of all chars for keyword shift_i
	for char in ascii_lowercase:
		f[i].update({char:0}) 
	for ch in c[i]:
		f[i][ch] += 1
#		print (" i = %d;  ch = %s; f[i][ch] = %d \n" % (i, ch, f[i][ch])) # )

length = len(line)/float(keylength)			# total number of chars for each val in keylength

# print ("The keyword is repeated %d times \n" %length)


# produce output

for i in range(keylength):	
	print ("\n %d \n" % (i+1))
	for c in ascii_lowercase:
		print ("%s : %04f" % (c, (f[i][c])/(float(length))))
