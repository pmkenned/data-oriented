import matplotlib.pyplot as plt
import scipy.special as sps
import numpy as np

# NOTES:
# start -> anaconda prompt
# activate sandbox2020
# cd C:\cygwin\...
# python zipf_example.py

a = 2.0
s = np.random.zipf(a, 10000)

count, bins, ignored = plt.hist(s[s<50], 50, normed=True)
x = np.arange(1., 50.)
y = x**(-a)/sps.zetac(a)
#plt.plot(x, y/max(y), linewidth=2, color='r')
plt.loglog(x, y/max(y), linewidth=2, color='r')
plt.show()
