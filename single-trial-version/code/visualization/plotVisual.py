# plotVisual.py
#
# Plot output data files of visual delay-match-to-sample simulation
#
# by Antonio Ulloa, PhD
#
# Last modified on January 15 2015

import numpy as np
import pylab as pl

# Load data files
efd1 = np.loadtxt('../../output/efd1.out')
efd2 = np.loadtxt('../../output/efd2.out')
ev1h = np.loadtxt('../../output/ev1h.out')
ev1v = np.loadtxt('../../output/ev1v.out')
ev4c = np.loadtxt('../../output/ev4c.out')
ev4h = np.loadtxt('../../output/ev4h.out')
ev4v = np.loadtxt('../../output/ev4v.out')
exfr = np.loadtxt('../../output/exfr.out')
exfs = np.loadtxt('../../output/exfs.out')
exss = np.loadtxt('../../output/exss.out')

# Plot values
fig1 = pl.figure()
fig1.suptitle('EFD1')
pl.plot(efd1) 

fig2 = pl.figure()
fig2.suptitle('EFD2')
pl.plot(efd2)

fig3 = pl.figure()
fig3.suptitle('EV1H')
pl.plot(ev1h)

fig4 = pl.figure()
fig4.suptitle('EV1V')
pl.plot(ev1v)

print ev1v.shape

grid = ev1v[1].reshape(9,9)

print grid.shape

fig5 = pl.figure()
fig5.suptitle('EV4C')
pl.plot(ev4c)

fig6 = pl.figure()
fig6.suptitle('EV4H')
pl.plot(ev4h)

fig7 = pl.figure()
fig7.suptitle('EV4V')
pl.plot(ev4v)

fig8 = pl.figure()
fig8.suptitle('EXFR')
pl.plot(exfr)

fig9 = pl.figure()
fig9.suptitle('EXFS')
pl.plot(exfs)

fig0 = pl.figure()
fig0.suptitle('EXSS')
pl.plot(exss)

# Show the plot on the screen
pl.show() 
