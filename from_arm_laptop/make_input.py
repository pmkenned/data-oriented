#!/usr/bin/env python

import sys
import random
import gzip

if len(sys.argv) < 2:
    sys.stderr.write('usage: %s [N]\n' % sys.argv[0])
    exit()

n = int(sys.argv[1])

#with open('words.txt', 'r') as fh:
with gzip.open('words.txt.gz', 'rb') as fh:
    data = fh.read()
    lines = data.split('\n')
    n_words = len(lines)

    for i in range(0,n):
        r = random.randint(0,n_words-1)
        sys.stdout.write(lines[r])
        r = random.randint(1,10)
        if r == 1:
            sys.stdout.write('\n')
        else:
            sys.stdout.write(' ')
sys.stdout.write('\n')
