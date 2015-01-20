# ============================================================================
#
#                            PUBLIC DOMAIN NOTICE
#
#       National Institute on Deafness and Other Communication Disorders
#
# This software/database is a "United States Government Work" under the 
# terms of the United States Copyright Act. It was written as part of 
# the author's official duties as a United States Government employee and 
# thus cannot be copyrighted. This software/database is freely available 
# to the public for use. The NIDCD and the U.S. Government have not placed 
# any restriction on its use or reproduction. 
#
# Although all reasonable efforts have been taken to ensure the accuracy 
# and reliability of the software and data, the NIDCD and the U.S. Government 
# do not and cannot warrant the performance or results that may be obtained 
# by using this software or data. The NIDCD and the U.S. Government disclaim 
# all warranties, express or implied, including warranties of performance, 
# merchantability or fitness for any particular purpose.
#
# Please cite the author in any work or product based on this material.
# 
# ==========================================================================



# ***************************************************************************
#
#   Large-Scale Neural Modeling software (LSNM)
#
#   Section on Brain Imaging and Modeling
#   Voice, Speech and Language Branch
#   National Institute on Deafness and Other Communication Disorders
#   National Institutes of Health
#
#   This file (plotVisual.py) was created on December 1, 2014.
#
#
#   Author: Antonio Ulloa. Last updated by Antonio Ulloa on January 18 2015  
# **************************************************************************/

# plotVisual.py
#
# Plot output data files of visual delay-match-to-sample simulation

import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
import matplotlib.animation as animation

# Load data files
lgns = np.loadtxt('../../output/lgns.out')
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

# Set up plot
plt.figure(1)

# Plot LGN module
ax = plt.subplot(11,2,1)
ax.plot(lgns)
ax.set_xticks([])
ax.set_yticks([])
plt.ylabel('LGN', rotation='horizontal', horizontalalignment='right')

# Plot V1 module
ax = plt.subplot(11,2,3)
ax.plot(ev1h)
ax.set_xticks([])
ax.set_yticks([])
plt.ylabel('V1h', rotation='horizontal', horizontalalignment='right')

ax = plt.subplot(11,2,5)
ax.plot(ev1v)
ax.set_xticks([])
ax.set_yticks([])
plt.ylabel('V1v', rotation='horizontal', horizontalalignment='right')

# Plot V4 module
ax = plt.subplot(11,2,7)
ax.plot(ev4h)
ax.set_xticks([])
ax.set_yticks([])
plt.ylabel('V4h', rotation='horizontal', horizontalalignment='right')

ax = plt.subplot(11,2,9)
ax.plot(ev4c)
ax.set_xticks([])
ax.set_yticks([])
plt.ylabel('V4c', rotation='horizontal', horizontalalignment='right')

ax = plt.subplot(11,2,11)
ax.plot(ev4v)
ax.set_xticks([])
ax.set_yticks([])
plt.ylabel('V4v', rotation='horizontal', horizontalalignment='right')

# Plot IT module
ax = plt.subplot(11,2,13)
ax.plot(exss)
ax.set_xticks([])
ax.set_yticks([])
plt.ylabel('IT', rotation='horizontal', horizontalalignment='right')

# Plot PFC modules FS, FD1, and FD2
ax = plt.subplot(11,2,15)
ax.plot(exfs)
ax.set_xticks([])
ax.set_yticks([])
plt.ylabel('FS', rotation='horizontal', horizontalalignment='right')

ax = plt.subplot(11,2,17)
ax.plot(efd1)
ax.set_xticks([])
ax.set_yticks([])
plt.ylabel('D1', rotation='horizontal', horizontalalignment='right')

ax = plt.subplot(11,2,19)
ax.plot(efd2)
ax.set_xticks([])
ax.set_yticks([])
plt.ylabel('D2', rotation='horizontal', horizontalalignment='right')

# Plot FR (Response module)
ax = plt.subplot(11,2,21)
ax.plot(exfr)
ax.set_yticks([])
plt.ylabel('R', rotation='horizontal', horizontalalignment='right')
plt.xlabel('Timesteps')

# Now display animation

#t,n = lgns.shape
#lgns = lgns.reshape(t, 9, 9)
#print lgns.shape

# Render LGN array in a colormap
ax = plt.subplot(11,2,2)
lgns = lgns[75]
lgns = lgns.reshape(9, 9)
img = plt.imshow(lgns)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render EV1h array in a colormap
ax=plt.subplot(11,2,4)
ev1h = ev1h[75]
ev1h = ev1h.reshape(9, 9)
img = plt.imshow(ev1h)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render EV1v array in a colormap
ax=plt.subplot(11,2,6)
ev1v = ev1v[75]
ev1v = ev1v.reshape(9, 9)
img = plt.imshow(ev1v)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(11,2,8)
ev4h = ev4h[75]
ev4h = ev4h.reshape(9, 9)
img = plt.imshow(ev4h)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(11,2,10)
ev4c = ev4c[75]
ev4c = ev4c.reshape(9, 9)
img = plt.imshow(ev4c)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(11,2,12)
ev4v = ev4v[75]
ev4v = ev4v.reshape(9, 9)
img = plt.imshow(ev4v)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(11,2,14)
exss = exss[75]
exss = exss.reshape(9, 9)
img = plt.imshow(exss)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(11,2,16)
exfs = exfs[75]
exfs = exfs.reshape(9, 9)
img = plt.imshow(exfs)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(11,2,18)
efd1 = efd1[75]
efd1 = efd1.reshape(9, 9)
img = plt.imshow(efd1)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(11,2,20)
efd2 = efd2[75]
efd2 = efd2.reshape(9, 9)
img = plt.imshow(efd2)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Render array in a colormap
ax=plt.subplot(11,2,22)
exfr = exfr[75]
exfr = exfr.reshape(9, 9)
img = plt.imshow(exfr)
img.set_cmap('hot')
ax.set_xticks([])
ax.set_yticks([])

# Display a reference color bar
#plt.colorbar()

# anim = animation.FuncAnimation(fig, plt.plot(lgns[9,9]))

# Show the plot on the screen
plt.show()

