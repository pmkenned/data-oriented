#!/usr/bin/env python

import sys
import gzip
import random

# TODO: use argparse
# TODO: allow for non-uniform distribution of word choices
# TODO: seed numpy RNG

# TODO:
# don't have to use numpy.zipf. Instead, use words_freq.txt
# create ranges for each word proportional to the quantity
# then use binary search to find which word is chosen

# resources:
# https://en.wiktionary.org/wiki/Wiktionary:Frequency_lists
# https://en.wiktionary.org/wiki/Wiktionary:Frequency_lists/PG/2006/04/1-10000
# https://www.corpusdata.org/intro.asp
# https://www.gutenberg.org/browse/scores/top

has_numpy = False
try:
    import numpy
    has_numpy = True
except ImportError:
    pass

argc = len(sys.argv)

if argc < 2:
    sys.stderr.write('usage: %s [N]\n' % sys.argv[0])
    exit()

n = int(sys.argv[1])
m = int(sys.argv[2]) if (argc >= 3) else None

if argc >= 4:
    seed = int(sys.argv[3])
    random.seed(seed)

use_zipf = True
if has_numpy:
    zipf_sample = numpy.random.zipf(1.1, n)

#with gzip.open('words.txt.gz', 'rb') as fh:
with gzip.open('words_ordered.txt.gz', 'rb') as fh:
    # lines = fh.read().decode('utf8').split('\n')
    lines = fh.read().split('\n')
    # random.shuffle(lines)

    if m is None: m = len(lines)

    for i in range(0,n):
        if has_numpy and use_zipf:
            r = zipf_sample[i]-1
            while (r >= m):
                # sys.stderr.write('r == %d; picking another...\n' % r)
                r = numpy.random.zipf(1.001, 1)[0]-1
        else:
            r = random.randint(0,m-1)
        sys.stdout.write(lines[r] + '\n')
