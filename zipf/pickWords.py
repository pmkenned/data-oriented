#!/usr/bin/env python

import sys
import gzip
import random

has_numpy = False
try:
    import numpy
    has_numpy = True
except ImportError:
    pass

if has_numpy:

    x_cnt = dict()
    x = numpy.random.zipf(1.05, 100000)

    for i in x:
        i -= 1
        if i in x_cnt:
            x_cnt[i] += 1
        else:
            x_cnt[i] = 1

    keys_sorted = sorted(x_cnt.keys())
    for xi in keys_sorted:
        val = x_cnt[xi]
        print (xi+1, val)
    exit()

# TODO: use argparse
# TODO: allow for non-uniform distribution of word choices

argc = len(sys.argv)

if argc < 2:
    sys.stderr.write('usage: %s [N]\n' % sys.argv[0])
    exit()

n = int(sys.argv[1])
m = int(sys.argv[2]) if (argc >= 3) else None

if argc >= 4:
    seed = int(sys.argv[3])
    random.seed(seed)

with gzip.open('words.txt.gz', 'rb') as fh:
    lines = fh.read().decode('utf8').split('\n')

    if m is None: m = len(lines)

    for i in range(0,n):
        r = random.randint(0,m-1)
        sys.stdout.write(lines[r] + '\n')
